// productmanager.h

#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <QString>
#include <QObject>
#include <QMap>
#include "product.h"
#include "orderedproduct.h"
#include "qrproduct.h"
class ProductManager :public QObject {
    Q_OBJECT
signals:
    void updateQrMap();
public:
    static ProductManager& getInstance();


    // 상품 카탈로그에 상품 추가 메서드
    bool removeProduct(const QString& productID);
    bool registerProduct(Product* product, const QString& productID);

    // 자신의 발주 데이터 작성 (normal 입장)
    bool registerOrderedProducts(OrderedProduct* product, const QString& productID);
  
    // orderedItemMap에 저장하는 메서드 (admin 입장)
    bool registerOrderedItems(OrderedProduct* product, const QString& productID);
    Product* findProductByCategory(const QString& productCategory);
    Product* findProductByName(const QString& productName);
    
    // normal 유저의 발주 데이터를 db에 저장하는 메서드
    bool saveProductsToDatabase(const QMap<QString, OrderedProduct*>& orderedProducts);
    bool registerQrProducts(QrProduct* product, const QString& productID);

    Product* findProductByID(const QString& productId);

    const QMap<QString, Product*>& getProductMap() const;
    const QMap<QString, OrderedProduct*>& getOrderedProductMap() const;
    const QMap<QString, QrProduct*>& getQrProductMap() const;

    void receiveQrData(const QByteArray& Qrdata);


private:
    // 싱글턴 구현을 위한 생성자/소멸자의 private 접근제한
    ProductManager();
    ~ProductManager();

    // 싱글턴 구현을 위한 복사 생성자 및 대입 연산자 삭제
    ProductManager(const ProductManager&) = delete;
    ProductManager& operator=(const ProductManager&) = delete;


    QMap<QString, Product*> productsByID;
    QMap<QString, OrderedProduct*> orderedProducts; // normal 입장 (로컬에서 갖고 있는 맵)
    QMap<QString, OrderedProduct*> orderedItemMap;  // admin 입장 (데이터베이스에서 불러온 맵)

    QMap<QString, QrProduct*> qrProduct;
};

#endif // PRODUCTMANAGER_H
