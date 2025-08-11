#ifndef NORMALORDERVERIFYFORM_H
#define NORMALORDERVERIFYFORM_H

#include <QWidget>
#include <QTableWidgetItem>
#include "raspiconnector.h"
namespace Ui {
class NormalOrderVerifyForm;
}

class NormalOrderVerifyForm : public QWidget
{
    Q_OBJECT

public:
    explicit NormalOrderVerifyForm(QWidget *parent = nullptr);
    ~NormalOrderVerifyForm();

    int getOrderCount();
    void increaseOrderCount();
    void decreaseOrderCount();


public slots:
    void updateOrderList();
    void appendLog(const QString& msg);
    void updateQrProductData();

private slots:
    void on_toolBox_currentChanged(int index);



    void on_disconnect_clicked();
    void on_connect_clicked();

private:
    Ui::NormalOrderVerifyForm *ui;


    // 사용자가 orderWidget에 아이템을 추가/삭제 할 때마다 변경될 예정
    // 최초는 1개의 행만 가짐
    int orderCount = 0;
};

#endif // NORMALORDERVERIFYFORM_H
