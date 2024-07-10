#include "temperature_transmitter.h"
#include "ui_temperature_transmitter.h"

TemperatureTransmitter::TemperatureTransmitter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemperatureTransmitter)
{
    ui->setupUi(this);
    color = Qt::gray;
}

TemperatureTransmitter::~TemperatureTransmitter()
{
    delete ui;
}

void TemperatureTransmitter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int _width = width();
    int _height = height();

    QPainter painter(this);
    QPolygonF p;

    p << QPointF(_width / 2.0 - 6,  0)  <<
         QPointF(_width / 2.0 + 6,  0)  <<
         QPointF(_width / 2.0 + 14, 15) <<
         QPointF(_width / 2.0 + 6,  30) <<
         QPointF(_width / 2.0 - 6,  30) <<
         QPointF(_width / 2.0 - 15, 15) <<
         QPointF(_width / 2.0 - 6,  0);

    painter.setBrush(color);
    painter.drawPolygon(p, Qt::OddEvenFill);

    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRectF(_width / 2 - 1.5, 30, 3, _height - 30 - 1));
    painter.drawLine(_width / 2, 3, _width / 2, 21);
    painter.drawEllipse(QPointF(_width / 2, 24), 3, 3);
}

QString TemperatureTransmitter::pvName() const
{
    return m_variableName;
}

void TemperatureTransmitter::setPVName(const QString name)
{
    this->m_variableName = name;
    if (!this->pv) {
        QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &TemperatureTransmitter::onChanged);
        QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &TemperatureTransmitter::onConnectionChanged);
    }
    this->pv = new QEpicsPV(this->m_variableName);
    QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &TemperatureTransmitter::onChanged);
    QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &TemperatureTransmitter::onConnectionChanged);
}

void TemperatureTransmitter::setThreshold(const double threshold)
{
    this->m_threshold = threshold;
}

double TemperatureTransmitter::getThreshold() const
{
    return m_threshold;
}

void TemperatureTransmitter::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}

void TemperatureTransmitter::onChanged(const QVariant &value)
{
    if (value.toDouble() > m_threshold)
        color = Qt::green;
    else
        color = Qt::red;

    update();
    setToolTip(pvName() + " - " + QString::number(value.toDouble()));
}
