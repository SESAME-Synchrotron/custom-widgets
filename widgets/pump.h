#ifndef PUMP_H
#define PUMP_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QtMath>
#include <QTimer>

#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class Pump;
}

class Pump : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString       PVName   READ pvName        WRITE setPVName);
    Q_PROPERTY(Rotation      rotation READ rotation      WRITE setRotation);
    Q_PROPERTY(FlipDirection flip     READ flipDirection WRITE setFlipDirection);

public:

    enum Rotation {
        NoRotation = 0,
        Rotate90 = 90,
        Rotate180 = 180,
        Rotate270 = 270
    };

    enum FlipDirection {
        NoFlip,
        Horizontal,
        Vertical
    };

    Q_ENUM(Rotation);
    Q_ENUM(FlipDirection);

    explicit Pump(QWidget *parent = nullptr);
    ~Pump();

    QString pvName() const;
    void setPVName(const QString name);

    Rotation rotation() const;
    void setRotation(const Rotation angle);

    FlipDirection flipDirection() const;
    void setFlipDirection(const FlipDirection direction);

public slots:
    void onChanged(const QVariant& value);
    void onConnectionChanged(bool state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::Pump *ui;

    double   m_rotationAngle;
    QColor   color;
    QString  m_variableName;
    QTimer*  m_timer;

    Rotation m_rotation;
    FlipDirection m_flip;

    QEpicsPV* pv;
};

#endif // PUMP_H
