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

    painter.setBrush(color);
    painter.drawEllipse(QPoint(15, 15), 14, 14);
    painter.drawLine(5, 5, 25, 25);
    painter.drawLine(5, 25, 25, 5);
    painter.drawLine(15, 30, 15, 60);
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
