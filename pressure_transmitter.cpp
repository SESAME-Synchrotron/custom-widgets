#include "pressure_transmitter.h"
#include "ui_pressure_transmitter.h"

PressureTransmitter::PressureTransmitter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PressureTransmitter)
{
    ui->setupUi(this);
    color = Qt::gray;
    m_threshold = 0;
}

PressureTransmitter::~PressureTransmitter()
{
    delete ui;
}

void PressureTransmitter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    int _width = width();
    int _height = height();
    int radius = _width / 2;

    painter.setBrush(color);
    painter.drawEllipse(QPoint(radius, 15), 14, 14);
    painter.drawLine(radius - 10, 5, radius + 10, 25);
    painter.drawLine(radius - 10, 25, radius + 10, 5);
    painter.drawLine(radius, 30, radius, _height);
    update();
}

QString PressureTransmitter::pvName() const
{
    return m_variableName;
}

double PressureTransmitter::getThreshold() const
{
    return m_threshold;
}

void PressureTransmitter::setPVName(const QString name)
{
    this->m_variableName = name;

     if (!this->pv) {
         QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &PressureTransmitter::onChanged);
     }
     this->pv = new QEpicsPV(this->m_variableName);
     QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &PressureTransmitter::onChanged);
}

void PressureTransmitter::setThreshold(const double threshold)
{
    this->m_threshold = threshold;
}

void PressureTransmitter::onChanged(const QVariant &value)
{
    if (value.toDouble() > m_threshold)
        color = Qt::green;
    else
        color = Qt::red;
    update();
}
