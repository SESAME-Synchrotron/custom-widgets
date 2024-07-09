#ifndef THREE_WAY_VALVE_H
#define THREE_WAY_VALVE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>

#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class ThreeWayValve;
}

class ThreeWayValve : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString PVName  READ pvName    WRITE setPVName);
    Q_PROPERTY(bool    flipped READ isFlipped WRITE setFlipped);

public:
    explicit ThreeWayValve(QWidget *parent = nullptr);
    ~ThreeWayValve();

    QString pvName() const;
    void setPVName(const QString name);

    bool isFlipped() const;
    void setFlipped(const bool direction);

public slots:
    void onChanged(const QVariant& value);
    void onConnectionChanged(bool state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::ThreeWayValve *ui;

    QColor  color;
    QString m_variableName;
    bool    m_flipped;

    QEpicsPV* pv;
};

#endif // THREE_WAY_VALVE_H
