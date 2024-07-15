#include "widgets/pressure_transmitter.h"
#include "ui_pressure_transmitter.h"

PressureTransmitter::PressureTransmitter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PressureTransmitter)
{
    ui->setupUi(this);
    color = Qt::gray;
    m_threshold = 0;
    pv = nullptr;
    m_rotation = Rotation::NoRotation;
}

PressureTransmitter::~PressureTransmitter()
{
    delete ui;
}

void PressureTransmitter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    int width = this->width();
    int height = this->height();
    int radius = 15;

    Q_IMPLEMENT_FLIP
    Q_IMPLEMENT_ROTATION

    painter.setBrush(color);
    painter.drawEllipse(QPoint(width / 2, 15), radius - 1, radius - 1);
    painter.drawLine(width / 2 - 10, 5, width / 2 + 10, 25);
    painter.drawLine(width / 2 - 10, 25, width / 2 + 10, 5);
    painter.drawLine(width / 2, 30, width / 2, width);
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

     if (this->pv) {
         QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &PressureTransmitter::onChanged);
         QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &PressureTransmitter::onConnectionChanged);
     }
     this->pv = new QEpicsPV(this->m_variableName);
     QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &PressureTransmitter::onChanged);
     QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &PressureTransmitter::onConnectionChanged);
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
    setToolTip(pvName() + " - " + QString::number(value.toDouble()));
}

void PressureTransmitter::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}
