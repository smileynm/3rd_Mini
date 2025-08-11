#include "qrproduct.h"

QrProduct::QrProduct(QString productID,
                     QString productName,
                     int productPrice,
                     QString productCategory,
                     int productQuantity) :
    m_productID(productID),
    m_productName(productName),
    m_productPrice(productPrice),
    m_productCategory(productCategory),
    m_productQuantity(productQuantity){}


QString QrProduct::getProductId() {
    return m_productID;
}

QString QrProduct::getProductName() {
    return m_productName;
}

int QrProduct::getProductPrice() {
    return m_productPrice;
}

QString QrProduct::getProductCategory() {
    return m_productCategory;
}

int QrProduct::getProductQuantity() {
    return m_productQuantity;
}

void QrProduct::setProductQuantity(int qty){
    m_productQuantity = qty;
}
