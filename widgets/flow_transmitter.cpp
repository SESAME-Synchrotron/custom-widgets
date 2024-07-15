#include "flow_transmitter.h"
#include "ui_flow_transmitter.h"

FlowTransmitter::FlowTransmitter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlowTransmitter)
{
    ui->setupUi(this);
    color = Qt::gray;
    m_threshold = 0;
    m_rotation = NoRotation;
}

FlowTransmitter::~FlowTransmitter()
{
    delete ui;
}

void FlowTransmitter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    int width = this->width();
    int height = this->height();
    int radius = width / 2;

    Q_IMPLEMENT_ROTATION

    painter.setBrush(color);
    painter.drawEllipse(QPoint(radius, 15), 12, 12);
    painter.drawLine(radius - 10, 10, radius + 10, 10);
    painter.drawLine(radius, 27, radius, height);
    update();
}

QString FlowTransmitter::pvName() const
{
    return m_variableName;
}

double FlowTransmitter::getThreshold() const
{
    return m_threshold;
}

void FlowTransmitter::setPVName(const QString name)
{
    this->m_variableName = name;

     if (!this->pv) {
         QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &FlowTransmitter::onChanged);
         QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &FlowTransmitter::onConnectionChanged);
     }
     this->pv = new QEpicsPV(this->m_variableName);
     QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &FlowTransmitter::onChanged);
     QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &FlowTransmitter::onConnectionChanged);
}

void FlowTransmitter::setThreshold(const double threshold)
{
    this->m_threshold = threshold;
}

void FlowTransmitter::onChanged(const QVariant &value)
{
    if (value.toDouble() > m_threshold)
        color = Qt::green;
    else
        color = Qt::red;
    update();
    setToolTip(pvName() + " - " + QString::number(value.toDouble()));
}

void FlowTransmitter::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}
