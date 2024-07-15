#ifndef TEMPERATURE_TRANSMITTER_H
#define TEMPERATURE_TRANSMITTER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class TemperatureTransmitter;
}

class TemperatureTransmitter : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString PVName    READ pvName       WRITE setPVName);
    Q_PROPERTY(double  threshold READ getThreshold WRITE setThreshold);

    Q_DECLARE_ROTATION

public:
    explicit TemperatureTransmitter(QWidget *parent = nullptr);
    ~TemperatureTransmitter();

    QString pvName() const;
    void setPVName(const QString name);

    double getThreshold() const;
    void setThreshold(const double threshold);

public slots:
    void onChanged(const QVariant& value);
    void onConnectionChanged(bool state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::TemperatureTransmitter *ui;

    QColor  color;
    QString m_variableName;
    double  m_threshold;

    QEpicsPV* pv;
};

#endif // TEMPERATURE_TRANSMITTER_H
