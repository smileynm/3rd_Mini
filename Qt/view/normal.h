#ifndef NORMAL_H
#define NORMAL_H

#include "normalchatform.h"
#include "normalorderform.h"
#include "normalorderverifyform.h"

#include <QMainWindow>
class NormalController;

namespace Ui {
class Normal;
}

class Normal : public QMainWindow {
    Q_OBJECT

public:
    explicit Normal(QWidget *parent = nullptr);
    ~Normal();

    void setController(NormalController *normalController);

    NormalChatForm *m_normalChatForm;
    NormalOrderForm *m_normalOrderForm;
    NormalOrderVerifyForm *m_normalOrderVerifyForm;

private:
    Ui::Normal *ui;
    NormalController *m_normalController;
};

#endif // NORMAL_H
