#include "widgets/pump.h"
#include "ui_pump.h"

Pump::Pump(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pump)
{
    ui->setupUi(this);
    color = Qt::gray;
    m_rotation = NoRotation;
}

Pump::~Pump()
{
    delete ui;
}

void Pump::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QTransform t;
    QPainter painter(this);

    int _width = width();
    int _height = height();
    int radius = _width / 2;

    if (m_flip == FlipDirection::Vertical) {
        t.translate(_width, 0);
        t.scale(-1, 1);
        painter.setTransform(t);
    }
    else if (m_flip == FlipDirection::Horizontal) {
        t.translate(0, _height);
        t.scale(1, -1);
        painter.setTransform(t);
    }
    else {
        t.scale(1, 1);
        painter.setTransform(t);
    }

    int angle = (int) m_rotation;
    bool rotated = false;

    if (angle != Rotation::NoRotation) {
        painter.translate(_width / 2, _height / 2);
        painter.rotate(angle);
        painter.translate(-_width / 2, -_height / 2);
        rotated = true;
    }
    else {
        if (rotated) {
            painter.translate(_width / 2, _height / 2);
            painter.rotate(-1 * angle);
            painter.translate(-_width / 2, -_height / 2);
            rotated = false;
        }
    }

    double offset = 15;
    int triangle_size = 4;
    double offset_x1 = radius - offset;
    double offset_x2 = radius + offset;
    double offset_y1 = qSqrt(2 * radius * offset_x1 - qPow(offset_x1, 2)) + radius;
    double offset_y2 = qSqrt(2 * radius * offset_x2 - qPow(offset_x2, 2)) + radius;

    painter.setBrush(color);
    painter.drawEllipse(QPoint(radius, radius), radius - triangle_size, radius - triangle_size);

    painter.drawLine(offset_x1, offset_y1 - triangle_size, 5, _height);
    painter.drawLine(offset_x2, offset_y2 - triangle_size, _width - 5, _height);
    painter.drawLine(5, _height, _width - 5, _height - 1);
    painter.drawLine(0, radius, radius, radius);
    painter.drawLine(radius, triangle_size, radius * 2, triangle_size);

    painter.setBrush(Qt::black);
    QPolygon p;
    p << QPoint(radius, radius - triangle_size) <<
         QPoint(radius, radius + triangle_size) <<
         QPoint(radius + triangle_size, radius);
    painter.drawPolygon(p);

    p.clear();
    p << QPoint(_width - triangle_size - 1, 0) <<
         QPoint(_width - triangle_size - 1, triangle_size * 2) <<
         QPoint(_width - 1, triangle_size);
    painter.drawPolygon(p);
}

QString Pump::pvName() const
{
    return m_variableName;
}

void Pump::setPVName(const QString name)
{
    this->m_variableName = name;

     if (!this->pv) {
         QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &Pump::onChanged);
         QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &Pump::onConnectionChanged);
     }
     this->pv = new QEpicsPV(this->m_variableName);
     QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &Pump::onChanged);
     QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &Pump::onConnectionChanged);
}

void Pump::onChanged(const QVariant &value)
{
    int state = value.toInt();
    switch (state) {
    case STATE_OFF:
        color = Qt::yellow;
        break;

    case STATE_ON:
        color = Qt::green;
        break;

    case STATE_FAULT:
        color = Qt::red;
        break;

    default:
        color = Qt::gray;
        break;
    }

    update();
    setToolTip(pvName() + " - " + QString::number(value.toDouble()));
}

void Pump::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}

void Pump::setRotation(const Rotation angle)
{
    m_rotation = angle;
    update();
}

Pump::Rotation Pump::rotation() const
{
    return m_rotation;
}

void Pump::setFlipDirection(const FlipDirection direction)
{
    m_flip = direction;
    update();
}

Pump::FlipDirection Pump::flipDirection() const
{
    return m_flip;
}
