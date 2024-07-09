#include "humidity_transmitter.h"
#include "ui_humidity_transmitter.h"

HumidityTransmitter::HumidityTransmitter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HumidityTransmitter)
{
    ui->setupUi(this);
}

HumidityTransmitter::~HumidityTransmitter()
{
    delete ui;
}

void HumidityTransmitter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int _width = width();
    int _height = height();

    QPainter painter(this);
    QPolygonF p;

    p << QPointF(_width / 2.0 - 10,  0)  <<
         QPointF(_width / 2.0 + 10,  0)  <<
         QPointF(_width / 2.0 + 21.5, 20) <<
         QPointF(_width / 2.0 + 10,  40) <<
         QPointF(_width / 2.0 - 10,  40) <<
         QPointF(_width / 2.0 - 22.5, 20) <<
         QPointF(_width / 2.0 - 10,  0);

    painter.setBrush(color);
    painter.drawPolygon(p, Qt::OddEvenFill);

    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRectF(_width / 2 - 2.5, 40, 5, _height - 40 - 1));
    painter.drawEllipse(QPointF(_width / 2 - 7, 12), 3, 3);
    painter.drawEllipse(QPointF(_width / 2 + 7, 12), 3, 3);
    painter.drawEllipse(QPointF(_width / 2 - 7, 27), 3, 3);
    painter.drawEllipse(QPointF(_width / 2 + 7, 27), 3, 3);
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

