#include "butterfly_valve.h"
#include "ui_butterfly_valve.h"

ButterflyValve::ButterflyValve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButterflyValve)
{
    ui->setupUi(this);

    color = Qt::green;
}

ButterflyValve::~ButterflyValve()
{
    delete ui;
}

void ButterflyValve::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPolygon p;
    QPainter painter(this);

    m_width = width();
    m_height = height();

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
    if (!this->pv) {
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
}
