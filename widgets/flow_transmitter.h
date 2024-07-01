#ifndef FLOW_TRANSMITTER_H
#define FLOW_TRANSMITTER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>

#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class FlowTransmitter;
}

class FlowTransmitter : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString PVName    READ pvName       WRITE setPVName);
    Q_PROPERTY(double  threshold READ getThreshold WRITE setThreshold);

public:
    explicit FlowTransmitter(QWidget *parent = nullptr);
    ~FlowTransmitter();

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
    Ui::FlowTransmitter *ui;

    QColor color;
    QString m_variableName;
    double m_threshold;

    QEpicsPV* pv;
};

#endif // FLOW_TRANSMITTER_H
