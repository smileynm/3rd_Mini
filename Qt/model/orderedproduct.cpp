#include "orderedproduct.h"

OrderedProduct::OrderedProduct(QString productID, QString productName, int productPrice, QString productCategory, int productQuantity) :
    m_productID(productID), m_productName(productName), m_productPrice(productPrice), m_productCategory(productCategory),
    m_productQuantity(productQuantity) {
}

OrderedProduct::~OrderedProduct() {
}

QString OrderedProduct::getProductID() {
    return m_productID;
}

QString OrderedProduct::getProductName() {
    return m_productName;
}

int OrderedProduct::getProductPrice() {
    return m_productPrice;
}

QString OrderedProduct::getProductCategory() {
    return m_productCategory;
}

int OrderedProduct::getProductQuantity() {
    return m_productQuantity;
}
