#include "widgets/butterfly_valve.h"
#include "ui_butterfly_valve.h"

ButterflyValve::ButterflyValve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButterflyValve)
{
    ui->setupUi(this);

    this->pv = nullptr;
    color = Qt::green;
    m_rotation = NoRotation;
}

ButterflyValve::~ButterflyValve()
{
    delete ui;
}

void ButterflyValve::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPolygon p;
    QTransform t;
    QPainter painter(this);

    m_width = width();
    m_height = height();

    if (m_flip == FlipDirection::Vertical) {
        t.translate(m_width, 0);
        t.scale(-1, 1);
        painter.setTransform(t);
    }
    else if (m_flip == FlipDirection::Horizontal) {
        t.translate(0, m_height);
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
        painter.translate(m_width / 2, m_height / 2);
        painter.rotate(angle);
        painter.translate(-m_width / 2, -m_height / 2);
        rotated = true;
    }
    else {
        if (rotated) {
            painter.translate(m_width / 2, m_height / 2);
            painter.rotate(-1 * angle);
            painter.translate(-m_width / 2, -m_height / 2);
            rotated = false;
        }
    }

    p << QPoint(0, m_height / 2) <<
         QPoint(0, m_height - 1) <<
         QPoint(m_width - 1, m_height / 2) <<
         QPoint(m_width - 1, m_height - 1);

    painter.setBrush(color);
    painter.drawPolygon(p);
    painter.drawRect(m_width / 2, 0, m_height * 0.4, m_height * 0.4);
    painter.drawLine(m_width / 2, m_height * 0.75, m_width / 2, 0);
}

QString ButterflyValve::pvName() const
{
    return m_variableName;
}

void ButterflyValve::setPVName(const QString name)
{
    this->m_variableName = name;
    if (this->pv) {
        QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &ButterflyValve::onChanged);
        QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &ButterflyValve::onConnectionChanged);
    }
    this->pv = new QEpicsPV(this->m_variableName);
    QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &ButterflyValve::onChanged);
    QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &ButterflyValve::onConnectionChanged);
}

void ButterflyValve::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}

void ButterflyValve::onChanged(const QVariant &value)
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


void ButterflyValve::setRotation(const Rotation angle)
{
    m_rotation = angle;
    update();
}

ButterflyValve::Rotation ButterflyValve::rotation() const
{
    return m_rotation;
}

void ButterflyValve::setFlipDirection(const FlipDirection direction)
{
    m_flip = direction;
    update();
}

ButterflyValve::FlipDirection ButterflyValve::flipDirection() const
{
    return m_flip;
}
