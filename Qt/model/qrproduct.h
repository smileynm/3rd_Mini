#ifndef QRPRODUCT_H
#define QRPRODUCT_H
#include <QString>


class QrProduct
{
public:
    QrProduct(QString productID,
              QString productName,
              int productPrice,
              QString productCategory,
              int quantity);
    ~QrProduct();

    void setProductQuantity(int qty);

    QString getProductName();
    QString getProductId();
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

#endif // QRPRODUCT_H
