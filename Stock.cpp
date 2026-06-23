#include "Stock.h"
#include "ui_Stock.h"

#include <QString>

Stock::Stock(QWidget *parent)
    : ui(new Ui::Stock)
{
}

Stock::~Stock()
{
    delete ui;
}

QWidget *Stock::Init(Bus *parent)
{
    m_pBus = parent;

    // create UI
    auto wgt = new QWidget(nullptr);
    wgt->setStyleSheet("background-color: transparent;");
    ui->setupUi(wgt);

    // init BUS connect
    connect(m_pBus, &Bus::SignalPing, this, &Stock::_slotPing);
    connect(m_pBus,
            &Bus::SignalLanguageSwitch,
            this,
            &Stock::_slotLanguageSwitch);

    return wgt;
}

void Stock::_slotPing()
{
    qDebug() << "Stock received Ping signal from Bus.";
    emit m_pBus->SignalPong();
}

void Stock::_slotLanguageSwitch(const QString &lang)
{
    qDebug() << "Stock received LanguageSwitch signal from Bus. lang: " << lang;
}
