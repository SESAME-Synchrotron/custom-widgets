#ifndef PUMP_H
#define PUMP_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QtMath>

#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class Pump;
}

class Pump : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString PVName    READ pvName       WRITE setPVName);

public:
    explicit Pump(QWidget *parent = nullptr);
    ~Pump();

    QString pvName() const;
    void setPVName(const QString name);

public slots:
    void onChanged(const QVariant& value);
    void onConnectionChanged(bool state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::Pump *ui;

    QColor color;
    QString m_variableName;

    QEpicsPV* pv;
};

#endif // PUMP_H
