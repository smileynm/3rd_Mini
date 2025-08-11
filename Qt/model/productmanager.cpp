// productmanager.cpp
#include "membermanager.h"
#include "productmanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

ProductManager& ProductManager::getInstance() {
    static ProductManager instance;
    return instance;
}

ProductManager::ProductManager() {
    qDebug() << QObject::tr("ProductManager created.");

}

ProductManager::~ProductManager() {
    for (auto it = productsByID.begin(); it != productsByID.end(); ++it) {
        QString productID = it.key();
        Product* product = it.value();
        qDebug() << QObject::tr("Deleting product: %1 %2").arg(product->getProductName()).arg(product->getProductID());
        delete product; // Product 객체의 메모리 해제
    }
    productsByID.clear(); // 맵 비우기
    qDebug() << QObject::tr("ProductManager destroyed.");
}

bool ProductManager::registerProduct(Product* product, const QString& productID) {
    if (productsByID.count(productID)) {
        qDebug() << QObject::tr("Error: Already exist Product");
        return false;
    }
    productsByID[productID] = product;
    qDebug() << QObject::tr("Product registered: %1 %2").arg(product->getProductName()).arg(product->getProductID());
    return true;
}

bool ProductManager::registerOrderedProducts(OrderedProduct* product, const QString& productID) {
    if (orderedProducts.count(productID)) {
        qDebug() << QObject::tr("Error: Already exist Product");
        return false;
    }
    orderedProducts[productID] = product;
    qDebug() << QObject::tr("Product ordered: %1 %2").arg(product->getProductName()).arg(product->getProductID());
    return true;
}

bool ProductManager::registerOrderedItems(OrderedProduct* product, const QString& productID) {
    if (orderedItemMap.count(productID)) {
        qDebug() << QObject::tr("Error: Already exist Product");
        return false;
    }
    orderedItemMap[productID] = product;
    qDebug() << QObject::tr("Product ordered: %1 %2").arg(product->getProductName()).arg(product->getProductID());

    return true;
}

bool ProductManager::registerQrProducts(QrProduct* product, const QString& productID) {
    if (qrProduct.count(productID)) {
        qDebug() << QObject::tr("Error: Already exist Product");
        return false;
    }
    qrProduct[productID] = product;
    qDebug() << QObject::tr("Product ordered: %1 %2").arg(product->getProductName()).arg(product->getProductId());

    return true;
}

bool ProductManager::removeProduct(const QString& productID) {
    // 맵에서 이름으로 상품 찾기
    auto it = productsByID.find(productID);
    if (it == productsByID.end()) {
        qDebug() << QObject::tr("Error: Product with Name %1").arg(productID) << " not found for removal.";
        return false; // 해당 상품이 없으면 삭제 실패
    }

    // 찾은 Product 객체의 메모리 해제
    delete it.value();

    // 맵에서 해당 상품 제거
    productsByID.erase(it);
    qDebug() << QObject::tr("Product removed: %1").arg(productID);
    return true; // 탈퇴 성공
}

bool ProductManager::saveProductsToDatabase(const QMap<QString, OrderedProduct*>& orderedProducts) {
    // 데이터베이스 연결 확인
    QSqlDatabase db = QSqlDatabase::database();
    MemberManager& memberManager = MemberManager::getInstance();
    if (!db.isOpen()) {
        qDebug() << "데이터베이스 연결이 필요합니다.";
        return false;
    }

    bool success = true;

    // 트랜잭션 시작 - 모든 쿼리를 한 번에 처리하기 위함
    db.transaction();

    QMapIterator<QString, OrderedProduct*> iter(orderedProducts);
    while (iter.hasNext()) {
        iter.next();
        const QString& productID = iter.key();
        OrderedProduct* product = iter.value();

        QSqlQuery query;
        query.prepare("INSERT INTO orderedLists (memberId, productID, productName, productPrice, productCategory, productQuantity) "
                      "VALUES (:memberId, :productID, :productName, :productPrice, :productCategory, :productQuantity)");

        query.bindValue(":memberId", memberManager.getLoggedinMember().constBegin().key());
        query.bindValue(":productID", product->getProductID());
        query.bindValue(":productName", product->getProductName());
        query.bindValue(":productPrice", product->getProductPrice());
        query.bindValue(":productCategory", product->getProductCategory());
        query.bindValue(":productQuantity", product->getProductQauntity());

        if (!query.exec()) {
            qDebug() << "상품 저장 실패:" << productID << ", 오류:" << query.lastError().text();
            success = false;
            break;
        }
    }

    // 모든 쿼리가 성공했으면 커밋, 실패했으면 롤백
    if (success) {
        db.commit();
        qDebug() << "총" << orderedProducts.size() << "개의 상품이 데이터베이스에 저장되었습니다.";
    } else {
        db.rollback();
        qDebug() << "상품 저장 중 오류가 발생하여 롤백되었습니다.";
    }
    return success;
}

Product* ProductManager::findProductByCategory(const QString& productCategory) {
    auto it = productsByID.find(productCategory);
    if (it != productsByID.end()) {
        return it.value();
    }
    return nullptr;
}

Product* ProductManager::findProductByName(const QString& productName) {
    auto it = productsByID.find(productName);
    if (it != productsByID.end()) {
        return it.value();
    }
    return nullptr;
}


 Product* ProductManager::findProductByID(const QString& productId) {
    auto it = productsByID.find(productId);
    if (it != productsByID.end()) {
        return it.value();
    }
    return nullptr;
}

const QMap<QString, Product*>& ProductManager::getProductMap() const {
    return productsByID;
}

const QMap<QString, OrderedProduct*>& ProductManager::getOrderedProductMap() const {
    return orderedProducts;
}

const QMap<QString, QrProduct*>& ProductManager::getQrProductMap() const {
    return qrProduct;
}


void ProductManager::receiveQrData(const QByteArray& Qrdata)
{
    QString productId = QString::fromUtf8(Qrdata).trimmed();
    qDebug()<<"id 받아서 Qr map에 추가 로직 진행, 받은 Id: " <<productId;

    if(qrProduct.contains(productId)){
         QrProduct* qty = qrProduct.value(productId);
         int currentQty = qty->getProductQuantity();
         qty->setProductQuantity(currentQty+1);
         qDebug()<<"중복 id -> 개수증가" << qty->getProductQuantity();
         emit updateQrMap();

    } else if(!qrProduct.contains(productId) && productsByID.contains(productId)){
        Product* baseProduct = productsByID.value(productId);
        QrProduct* newProduct = new QrProduct(
            baseProduct->getProductID(),
            baseProduct->getProductName(),
            baseProduct->getProductPrice(),
            baseProduct->getProductCategory(),
            1 // 수량은 1로 시작
            );

        qrProduct.insert(productId, newProduct);
        qDebug() << " 기본 정보 복사하여 QR 상품 등록:" << productId;
        emit updateQrMap();
        return;

    } else {
        qDebug() <<"제품 정보 없음";
    }

}







