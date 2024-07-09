#include "three_way_valve.h"
#include "ui_three_way_valve.h"

ThreeWayValve::ThreeWayValve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThreeWayValve)
{
    ui->setupUi(this);
    m_flipped = false;
    color = Qt::gray;
}

ThreeWayValve::~ThreeWayValve()
{
    delete ui;
}

void ThreeWayValve::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPolygon p;
    QPainter painter(this);

    int _width = width();
    int _height = height();
    double radius = _width / 4;

    bool checkFlipped = false;

    painter.setBrush(color);
    if (m_flipped) {
        painter.translate(_width / 2, _height / 2);
        painter.rotate(180);
        painter.translate(-_width / 2, -_height / 2);
        checkFlipped = true;
    }
    else {
        if (checkFlipped) {
            painter.translate(_width / 2, _height / 2);
            painter.rotate(-180);
            painter.translate(-_width / 2, -_height / 2);
            checkFlipped = false;
        }
    }

    p << QPoint(0, 0) <<
         QPoint(_width / 2, radius) <<
         QPoint(3 * radius, _height - 1) <<
         QPoint(radius, _height - 1) <<
         QPoint(_width / 2, radius) <<
         QPoint(_width - 1, 0) <<
         QPoint(_width - 1, 2 * radius) <<
         QPoint(_width / 2, radius) <<
         QPoint(0, 2 * radius) <<
         QPoint(0, 0);
    painter.drawPolygon(p);
    painter.drawEllipse(QPointF(_width / 2.0, _width / 4.0), radius, radius);
}

QString ThreeWayValve::pvName() const
{
    return m_variableName;
}

void ThreeWayValve::setPVName(const QString name)
{
    this->m_variableName = name;

     if (!this->pv) {
         QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &ThreeWayValve::onChanged);
         QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &ThreeWayValve::onConnectionChanged);
     }
     this->pv = new QEpicsPV(this->m_variableName);
     QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &ThreeWayValve::onChanged);
     QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &ThreeWayValve::onConnectionChanged);
}

void ThreeWayValve::onChanged(const QVariant &value)
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

void ThreeWayValve::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}

bool ThreeWayValve::isFlipped() const
{
    return m_flipped;
}

void ThreeWayValve::setFlipped(const bool direction)
{
    m_flipped = direction;
    update();
}
