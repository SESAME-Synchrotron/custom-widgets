#ifndef AHU_FAN_H
#define AHU_FAN_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>

#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class AHUFan;
}

class AHUFan : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString PVName    READ pvName       WRITE setPVName);

public:
    explicit AHUFan(QWidget *parent = nullptr);
    ~AHUFan();

    QString pvName() const;
    void setPVName(const QString name);

public slots:
    void onChanged(const QVariant& value);
    void onConnectionChanged(bool state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::AHUFan *ui;

    QColor color;
    QString m_variableName;

    QEpicsPV* pv;
};

#endif // AHU_FAN_H
