#include "humidity_transmitter.h"
#include "ui_humidity_transmitter.h"

HumidityTransmitter::HumidityTransmitter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HumidityTransmitter)
{
    ui->setupUi(this);
    color = Qt::gray;
    m_rotation = NoRotation;
}

HumidityTransmitter::~HumidityTransmitter()
{
    delete ui;
}

void HumidityTransmitter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int width = this->width();
    int height = this->height();

    QPainter painter(this);
    QPolygonF p;

    Q_IMPLEMENT_ROTATION

    p << QPointF(width / 2.0 - 4,  0)  <<
         QPointF(width / 2.0 + 4,  0)  <<
         QPointF(width / 2.0 + 12, 15) <<
         QPointF(width / 2.0 + 4,  30) <<
         QPointF(width / 2.0 - 4,  30) <<
         QPointF(width / 2.0 - 12, 15) <<
         QPointF(width / 2.0 - 4,  0);

    painter.setBrush(color);
    painter.drawPolygon(p, Qt::OddEvenFill);

    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRectF(width / 2 - 1.5, 30, 3, height - 30 - 1));
    painter.drawEllipse(QPointF(width / 2 - 5, 10), 3, 3);
    painter.drawEllipse(QPointF(width / 2 + 5, 10), 3, 3);
    painter.drawEllipse(QPointF(width / 2 - 5, 20), 3, 3);
    painter.drawEllipse(QPointF(width / 2 + 5, 20), 3, 3);
}

QString HumidityTransmitter::pvName() const
{
    return m_variableName;
}

void HumidityTransmitter::setPVName(const QString name)
{
    this->m_variableName = name;
    if (!this->pv) {
        QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &HumidityTransmitter::onChanged);
        QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &HumidityTransmitter::onConnectionChanged);
    }
    this->pv = new QEpicsPV(this->m_variableName);
    QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &HumidityTransmitter::onChanged);
    QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &HumidityTransmitter::onConnectionChanged);
}

void HumidityTransmitter::setThreshold(const double threshold)
{
    this->m_threshold = threshold;
}

double HumidityTransmitter::getThreshold() const
{
    return m_threshold;
}

void HumidityTransmitter::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}

void HumidityTransmitter::onChanged(const QVariant &value)
{
    if (value.toDouble() > m_threshold)
        color = Qt::green;
    else
        color = Qt::red;

    update();
    setToolTip(pvName() + " - " + QString::number(value.toDouble()));
}

