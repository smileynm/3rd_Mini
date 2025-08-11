#ifndef ORDEREDPRODUCT_H
#define ORDEREDPRODUCT_H

#include <QString>
#include <QJsonObject>

class OrderedProduct {
public:
    OrderedProduct(QString productID, QString productName, int productPrice, QString productCategory, int quantity);
    ~OrderedProduct();
    QString getProductName();
    QString getProductID();
    int getProductPrice();
    QString getProductCategory();
    int getProductQuantity();

private:
    QString m_productName;
    QString m_productID;
    int m_productPrice;
    QString m_productCategory;
    int m_productQuantity;
};

#endif // ORDEREDPRODUCT_H
