#ifndef STOCK_H
#define STOCK_H

#include <QObject>
#include <QtPlugin>
#include <QWidget>

#include "Bus.h"
#include "PluginInterface.h"

namespace Ui
{
class Stock;
}

class Stock : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "rag-qt.PluginInterface" FILE "stockplugin.json")
    Q_INTERFACES(PluginInterface)

  public:
    explicit Stock(QWidget *parent = nullptr);
    ~Stock();

    QString  Id() override { return "stock-v0.0.1"; }
    QString  Name() override { return "stock"; }
    QString  Icon() override { return "StockIcon.png"; }
    QString  Version() override { return "0.0.1"; }
    QWidget *Init(Bus *parent = nullptr) override;

  private slots:
    // bus signal
    void _slotPing();
    void _slotLanguageSwitch(const QString &lang);

  private:
    Ui::Stock *ui;
    Bus       *m_pBus;
};

#endif