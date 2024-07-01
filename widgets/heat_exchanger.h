#ifndef HEAT_EXCHANGER_H
#define HEAT_EXCHANGER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class HeatExchanger;
}

class HeatExchanger : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString PVName    READ pvName       WRITE setPVName);

public:
    explicit HeatExchanger(QWidget *parent = nullptr);
    ~HeatExchanger();

    QString pvName() const;
    void setPVName(const QString name);

public slots:
    void onChanged(const QVariant& value);
    void onConnectionChanged(bool state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::HeatExchanger *ui;

    QColor color;
    QString m_variableName;

    QEpicsPV* pv;
};

#endif // HEAT_EXCHANGER_H
