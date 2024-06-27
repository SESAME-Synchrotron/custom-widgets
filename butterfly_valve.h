#ifndef BUTTERFLY_VALVE_H
#define BUTTERFLY_VALVE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>

#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class ButterflyValve;
}

class ButterflyValve : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString PVName    READ pvName       WRITE setPVName);

public:
    explicit ButterflyValve(QWidget *parent = nullptr);
    ~ButterflyValve();

    QString pvName() const;
    void setPVName(const QString name);

public slots:
    void onChanged(const QVariant& value);
    void onConnectionChanged(bool state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::ButterflyValve *ui;

    int m_width;
    int m_height;
    QColor color;
    QString m_variableName;

    QEpicsPV* pv;
};

#endif // BUTTERFLY_VALVE_H
