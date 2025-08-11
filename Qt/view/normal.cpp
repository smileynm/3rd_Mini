#include "normal.h"
#include "ui_normal.h"

Normal::Normal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Normal) {
    ui->setupUi(this);

    // 제목 표시줄 설정 : 점주모드
    //setWindowTitle(tr("QT25 점주 시스템: %1").arg(member.begin().key()));
    setWindowTitle(tr("QT25 주문 시스템"));

    m_normalChatForm = new NormalChatForm(this);
    m_normalOrderForm = new NormalOrderForm(this);
    m_normalOrderVerifyForm = new NormalOrderVerifyForm(this);

    // tab에 객체 추가
    ui->tabWidget->addTab(m_normalChatForm, tr("채팅서버"));
    ui->tabWidget->addTab(m_normalOrderForm, tr("발주관리"));
    ui->tabWidget->addTab(m_normalOrderVerifyForm, tr("수량확인"));
}

Normal::~Normal() {
    delete ui;
}

void Normal::setController(NormalController *normalController) {
    m_normalController = normalController;

    //connect(m_normalOrderForm, &NormalOrderForm::orderUpdate, m_normalOrderVerifyForm, &NormalOrderVerifyForm::updateOrderList);
    // connect 함수 나열
    /***************************************************************/
    //
    //
    //
    /***************************************************************/
    qDebug() << "Connecting objects:";
    qDebug() << "Sender: " << m_normalOrderForm;
    qDebug() << "Receiver: " << m_normalOrderVerifyForm;

    bool connected = connect(m_normalOrderForm, &NormalOrderForm::orderUpdate,
                             m_normalOrderVerifyForm, &NormalOrderVerifyForm::updateOrderList);
    qDebug() << "Connection successful? " << connected;
}
