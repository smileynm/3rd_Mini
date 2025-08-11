#include "normalorderverifyform.h"
#include "ui_normalorderverifyform.h"
#include "productmanager.h"
#include "raspiconnector.h"
NormalOrderVerifyForm::NormalOrderVerifyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NormalOrderVerifyForm) {
    ui->setupUi(this);

    // 프로그램 시작 시, 전체 카테고리를 default(6번째 툴바/위젯)로 표시할 것.
    ui->toolBox->setCurrentIndex(6);
    ui->stackedWidget->setCurrentIndex(6);


    // 상품 관리자 인스턴스 호출 및 상품 카탈로그 QMap 형태의 상품 리스트 호출
    ProductManager& productManager = ProductManager::getInstance();
    QMap<QString, OrderedProduct*> productCatalog = productManager.getOrderedProductMap();

    connect(RaspiConnector::getInstance(), &RaspiConnector::QRcodeData, &ProductManager::getInstance(), &ProductManager::receiveQrData);    // QTableWidget 설정
    connect(&productManager, &ProductManager::updateQrMap, this, &NormalOrderVerifyForm::updateQrProductData);

    QStringList headers;
    headers << "상품명" << "상품ID" << "가격" << "카테고리" << "개수";
    // 전체 위젯
    ui->allWidget->setColumnCount(headers.size());
    ui->allWidget->setHorizontalHeaderLabels(headers);
    // 음료 위젯
    ui->beverageWidget->setColumnCount(headers.size());
    ui->beverageWidget->setHorizontalHeaderLabels(headers);
    // 스낵 위젯
    ui->snackWidget->setColumnCount(headers.size());
    ui->snackWidget->setHorizontalHeaderLabels(headers);
    // 즉석식품 위젯
    ui->instantWidget->setColumnCount(headers.size());
    ui->instantWidget->setHorizontalHeaderLabels(headers);
    // 유제품/아이스크림 위젯
    ui->milkiceWidget->setColumnCount(headers.size());
    ui->milkiceWidget->setHorizontalHeaderLabels(headers);
    // 주류 위젯
    ui->drinkWidget->setColumnCount(headers.size());
    ui->drinkWidget->setHorizontalHeaderLabels(headers);
    // 생필품 위젯
    ui->neceWidget->setColumnCount(headers.size());
    ui->neceWidget->setHorizontalHeaderLabels(headers);

    // 사용자 장바구니 위젯
    QStringList qrHeaders;
    qrHeaders << "상품명" << "상품ID" << "가격" << "카테고리" << "개수";
    ui->qrWidget->setColumnCount(qrHeaders.size());
    ui->qrWidget->setHorizontalHeaderLabels(qrHeaders);

    // 호출된 상품 리스트의 개수에 맞게 각 카테고리별 위젯의 행 개수 설정
    ui->allWidget->setRowCount(productCatalog.size());
    ui->beverageWidget->setRowCount(productCatalog.size());
    ui->snackWidget->setRowCount(productCatalog.size());
    ui->instantWidget->setRowCount(productCatalog.size());
    ui->milkiceWidget->setRowCount(productCatalog.size());
    ui->drinkWidget->setRowCount(productCatalog.size());
    ui->neceWidget->setRowCount(productCatalog.size());

    // 제목에 해당하는 각 위젯 열 크기 조절
    ui->allWidget->setColumnWidth(0, 200);
    ui->beverageWidget->setColumnWidth(0, 200);
    ui->snackWidget->setColumnWidth(0, 200);
    ui->instantWidget->setColumnWidth(0, 200);
    ui->milkiceWidget->setColumnWidth(0, 200);
    ui->drinkWidget->setColumnWidth(0, 200);
    ui->neceWidget->setColumnWidth(0, 200);
    ui->orderWidget->setColumnWidth(0, 200);
}

void NormalOrderVerifyForm::updateOrderList() {
    // qDebug() << "hello";
    ui->qrWidget->setColumnWidth(0, 200);
    // 점주 입장에서는 상품 카테고리의 수정권이 없다.
    // 본사에서 제공하는 내용이기 때문.
    // 각 테이블 위젯 사용자가 직접 수정 방지용
    ui->allWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->beverageWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->snackWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->instantWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->milkiceWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->drinkWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->neceWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->qrWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void NormalOrderVerifyForm::updateOrderList(){
    ui->toolBox->setCurrentIndex(6);
    ui->stackedWidget->setCurrentIndex(6);

    // 상품 목록을 담은 QMap 호출
    // increaseOrderCount();
    ProductManager& productManager = ProductManager::getInstance();
    QMap<QString, OrderedProduct*> productCatalog = productManager.getOrderedProductMap();

    ui->allWidget->setRowCount(productCatalog.size());
    //orderCount = productCatalog.size();
    auto it = productCatalog.constBegin();
    for (int row = 0; it!=productCatalog.constEnd(); ++row, ++it) {
        QTableWidgetItem *nameItem = new QTableWidgetItem(it.value()->getProductName());
        QTableWidgetItem *idItem = new QTableWidgetItem(it.value()->getProductID());
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(it.value()->getProductPrice()));
        QTableWidgetItem *categoryItem = new QTableWidgetItem(it.value()->getProductCategory());
        QTableWidgetItem *quantityItem = new QTableWidgetItem(QString::number(it.value()->getProductQauntity()));

        ui->allWidget->setItem(row, 0, nameItem);
        ui->allWidget->setItem(row, 1, idItem);
        ui->allWidget->setItem(row, 2, priceItem);
        ui->allWidget->setItem(row, 3, categoryItem);
        ui->allWidget->setItem(row, 4, quantityItem);
    }
    qDebug() << productCatalog.constBegin().key();
    qDebug() << productCatalog.constBegin().value()->getProductQuantity();


    // increaseOrderCount();
    // ui->allWidget->setRowCount(getOrderCount()+1);
    // qDebug() << getOrderCount() << "개";


    // // 호출된 상품 리스트의 개수에 맞게 각 카테고리별 위젯의 행 개수 설정
    ui->allWidget->setRowCount(productCatalog.size());
    ui->beverageWidget->setRowCount(productCatalog.size());
    ui->snackWidget->setRowCount(productCatalog.size());
    ui->instantWidget->setRowCount(productCatalog.size());
    ui->milkiceWidget->setRowCount(productCatalog.size());
    ui->drinkWidget->setRowCount(productCatalog.size());
    ui->neceWidget->setRowCount(productCatalog.size());

   // 호출된 상품 리스트의 개수에 맞게 각 카테고리별 위젯의 행 개수 설정
    ui->allWidget->setRowCount(productCatalog.size());
    //스텍위젯을 위해 선언
    auto it = productCatalog.constBegin();
    int beverageRow = 0;
    int snackRow = 0;
    int instantRow = 0;
    int milkRow = 0;
    int drinkRow = 0;
    int neceRow = 0;

    // 일단 모든 상품 목록을 전체 카테고리 위젯에 출력
    for (int row=0; row<productCatalog.size(); ++row, ++it) {
        //QMap<Key, T>::const_iterator QMap::constEnd() const
        //Returns a const STL-style iterator pointing to the imaginary item after the last item in the map.

        QTableWidgetItem *nameItem = new QTableWidgetItem(it.value()->getProductName());
        QTableWidgetItem *idItem = new QTableWidgetItem(it.value()->getProductID());
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(it.value()->getProductPrice()));
        QTableWidgetItem *categoryItem = new QTableWidgetItem(it.value()->getProductCategory());
        QTableWidgetItem *Quantity = new QTableWidgetItem(QString::number(it.value()->getProductQuantity()));
        ui->allWidget->setItem(row, 0, nameItem);
        ui->allWidget->setItem(row, 1, idItem);
        ui->allWidget->setItem(row, 2, priceItem);
        ui->allWidget->setItem(row, 3, categoryItem);
        ui->allWidget->setItem(row, 4, Quantity);
    }

    // 카테고리가 "음료" 인 경우
    // 음료 테이블 위젯에 음료만 출력
    for (it = productCatalog.constBegin(); it!=productCatalog.constEnd(); ++it) {
        if (it.value()->getProductCategory() == "음료") {
            QTableWidgetItem *beverageName = new QTableWidgetItem(it.value()->getProductName());
            QTableWidgetItem *beverageID = new QTableWidgetItem(it.value()->getProductID());
            QTableWidgetItem *beveragePrice = new QTableWidgetItem(QString::number(it.value()->getProductPrice()));
            QTableWidgetItem *beverageCategory = new QTableWidgetItem(it.value()->getProductCategory());
            QTableWidgetItem *beverageQuantity = new QTableWidgetItem(QString::number(it.value()->getProductQuantity()));

            ui->beverageWidget->setItem(beverageRow, 0, beverageName);
            ui->beverageWidget->setItem(beverageRow, 1, beverageID);
            ui->beverageWidget->setItem(beverageRow, 2, beveragePrice);
            ui->beverageWidget->setItem(beverageRow, 3, beverageCategory);
            ui->beverageWidget->setItem(beverageRow, 4, beverageQuantity);
            beverageRow++;
        }
    }

    // 카테고리가 "스낵" 인 경우
    // 스낵 테이블 위젯에 스낵만 출력
    for (it = productCatalog.constBegin(); it!=productCatalog.constEnd(); ++it) {
        if (it.value()->getProductCategory() == "스낵") {
            QTableWidgetItem *snackName = new QTableWidgetItem(it.value()->getProductName());
            QTableWidgetItem *snackID = new QTableWidgetItem(it.value()->getProductID());
            QTableWidgetItem *snackPrice = new QTableWidgetItem(QString::number(it.value()->getProductPrice()));
            QTableWidgetItem *snackCategory = new QTableWidgetItem(it.value()->getProductCategory());
            QTableWidgetItem *snackQuantity = new QTableWidgetItem(QString::number(it.value()->getProductQuantity()));
            ui->snackWidget->setItem(snackRow, 0, snackName);
            ui->snackWidget->setItem(snackRow, 1, snackID);
            ui->snackWidget->setItem(snackRow, 2, snackPrice);
            ui->snackWidget->setItem(snackRow, 3, snackCategory);
            ui->snackWidget->setItem(snackRow, 4, snackQuantity);
            snackRow++;
        }
    }

    // 카테고리가 "즉석식품" 인 경우
    // 즉석식품 테이블 위젯에 즉석식품만 출력
    for (it = productCatalog.constBegin(); it!=productCatalog.constEnd(); ++it) {
        if (it.value()->getProductCategory() == "즉석식품") {
            QTableWidgetItem *nameItem = new QTableWidgetItem(it.value()->getProductName());
            QTableWidgetItem *idItem = new QTableWidgetItem(it.value()->getProductID());
            QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(it.value()->getProductPrice()));
            QTableWidgetItem *categoryItem = new QTableWidgetItem(it.value()->getProductCategory());
            QTableWidgetItem *Quantity = new QTableWidgetItem(QString::number(it.value()->getProductQuantity()));
            ui->instantWidget->setItem(instantRow, 0, nameItem);
            ui->instantWidget->setItem(instantRow, 1, idItem);
            ui->instantWidget->setItem(instantRow, 2, priceItem);
            ui->instantWidget->setItem(instantRow, 3, categoryItem);
            ui->instantWidget->setItem(instantRow, 4, Quantity);
            instantRow++;
        }
    }

    // 유제품/아이스크림
    for (it = productCatalog.constBegin(); it != productCatalog.constEnd(); ++it) {
        if (it.value()->getProductCategory() == "유제품/아이스크림") {
            QTableWidgetItem *nameItem = new QTableWidgetItem(it.value()->getProductName());
            QTableWidgetItem *idItem = new QTableWidgetItem(it.value()->getProductID());
            QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(it.value()->getProductPrice()));
            QTableWidgetItem *categoryItem = new QTableWidgetItem(it.value()->getProductCategory());
            QTableWidgetItem *quantityItem = new QTableWidgetItem(QString::number(it.value()->getProductQuantity()));
            ui->milkiceWidget->setItem(milkRow, 0, nameItem);
            ui->milkiceWidget->setItem(milkRow, 1, idItem);
            ui->milkiceWidget->setItem(milkRow, 2, priceItem);
            ui->milkiceWidget->setItem(milkRow, 3, categoryItem);
            ui->milkiceWidget->setItem(milkRow, 4, quantityItem);
            milkRow++;
        }
    }

    // 주류
    for (it = productCatalog.constBegin(); it != productCatalog.constEnd(); ++it) {
        if (it.value()->getProductCategory() == "주류") {
            QTableWidgetItem *nameItem = new QTableWidgetItem(it.value()->getProductName());
            QTableWidgetItem *idItem = new QTableWidgetItem(it.value()->getProductID());
            QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(it.value()->getProductPrice()));
            QTableWidgetItem *categoryItem = new QTableWidgetItem(it.value()->getProductCategory());
            QTableWidgetItem *quantityItem = new QTableWidgetItem(QString::number(it.value()->getProductQuantity()));
            ui->drinkWidget->setItem(drinkRow, 0, nameItem);
            ui->drinkWidget->setItem(drinkRow, 1, idItem);
            ui->drinkWidget->setItem(drinkRow, 2, priceItem);
            ui->drinkWidget->setItem(drinkRow, 3, categoryItem);
            ui->drinkWidget->setItem(drinkRow, 4, quantityItem);
            drinkRow++;
        }
    }

    // 생활용품
    for (it = productCatalog.constBegin(); it != productCatalog.constEnd(); ++it) {
        if (it.value()->getProductCategory() == "생활용품") {
            QTableWidgetItem *nameItem = new QTableWidgetItem(it.value()->getProductName());
            QTableWidgetItem *idItem = new QTableWidgetItem(it.value()->getProductID());
            QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(it.value()->getProductPrice()));
            QTableWidgetItem *categoryItem = new QTableWidgetItem(it.value()->getProductCategory());
            QTableWidgetItem *quantityItem = new QTableWidgetItem(QString::number(it.value()->getProductQuantity()));
            ui->neceWidget->setItem(neceRow, 0, nameItem);
            ui->neceWidget->setItem(neceRow, 1, idItem);
            ui->neceWidget->setItem(neceRow, 2, priceItem);
            ui->neceWidget->setItem(neceRow, 3, categoryItem);
            ui->neceWidget->setItem(neceRow, 4, quantityItem);
            neceRow++;
        }
    }

    // 출력된 각 카테고리별 행 수에 맞게 행 개수 재조정
    ui->beverageWidget->setRowCount(beverageRow);
    ui->snackWidget->setRowCount(snackRow);
    ui->instantWidget->setRowCount(instantRow);
    ui->milkiceWidget->setRowCount(milkRow);
    ui->drinkWidget->setRowCount(drinkRow);
    ui->neceWidget->setRowCount(neceRow);

    productManager.saveProductsToDatabase(productCatalog);
}

NormalOrderVerifyForm::~NormalOrderVerifyForm() {
    delete ui;
}

int NormalOrderVerifyForm::getOrderCount() {
    return orderCount;
}

void NormalOrderVerifyForm::increaseOrderCount() {
    orderCount++;
}

void NormalOrderVerifyForm::decreaseOrderCount() {
    orderCount--;
}

void NormalOrderVerifyForm::on_toolBox_currentChanged(int index) {
    ui->stackedWidget->setCurrentIndex(index);
    //qDebug() << tr("QToolBox 페이지 변경됨 -> 인덱스:") << index << tr(", QStackedWidget 페이지 변경됨.");
}

void NormalOrderVerifyForm::on_connect_clicked() {
    RaspiConnector::getInstance()->startConnect(12345);
}

void NormalOrderVerifyForm::on_disconnect_clicked() {
    RaspiConnector::getInstance()->disconnect();
}

void NormalOrderVerifyForm::appendLog(const QString& msg) {
    ui->log->append(msg);
}


void NormalOrderVerifyForm::updateQrProductData() {
    qDebug() << "[DEBUG] updateQrProductData 호출됨";
    ProductManager& productManager = ProductManager::getInstance();
    QMap<QString, QrProduct*> productCatalog = productManager.getQrProductMap();

    qDebug() << "QR Map Size:" << productCatalog.size();
    qDebug() << productCatalog.constBegin().key();
    qDebug() << productCatalog.constBegin().value()->getProductQuantity();

    ui->qrWidget->clearContents();
    ui->qrWidget->setRowCount(productCatalog.size());
    ui->qrWidget->setColumnCount(5);
    ui->qrWidget->setHorizontalHeaderLabels(QStringList{"상품명", "상품ID", "가격", "카테고리", "개수"});

    int row = 0;
    for (auto it = productCatalog.constBegin(); it != productCatalog.constEnd(); ++it, ++row) {
        QrProduct* product = it.value();
        ui->qrWidget->setItem(row, 0, new QTableWidgetItem(product->getProductName()));
        ui->qrWidget->setItem(row, 1, new QTableWidgetItem(product->getProductId()));
        ui->qrWidget->setItem(row, 2, new QTableWidgetItem(QString::number(product->getProductPrice())));
        ui->qrWidget->setItem(row, 3, new QTableWidgetItem(product->getProductCategory()));
        ui->qrWidget->setItem(row, 4, new QTableWidgetItem(QString::number(product->getProductQuantity())));
    }
}
