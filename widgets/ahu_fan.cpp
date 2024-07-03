#include "ahu_fan.h"
#include "ui_ahu_fan.h"

AHUFan::AHUFan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AHUFan)
{
    ui->setupUi(this);
}

AHUFan::~AHUFan()
{
    delete ui;
}

void AHUFan::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int _width = width();
    int _height = height();
    double center = (_width - 30) / 2;


    QPainter painter(this);
    painter.drawEllipse(QPoint(center, center), (int) center / 2, (int) center / 2);
    painter.drawEllipse(QPoint(center, center), (int) center - 1, (int) center - 1);
    painter.drawLine(center, 1, _width - 1, 1);
    painter.drawLine(_width - 1, 1, _width - 1, _height / 4);
    painter.drawLine(_width - 1, _height / 4, (qSqrt(3) * (center) / 2) + center + 1, _height / 4);
}

QString AHUFan::pvName() const
{
    return m_variableName;
}

void AHUFan::setPVName(const QString name)
{
    this->m_variableName = name;
    if (!this->pv) {
        QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &AHUFan::onChanged);
        QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &AHUFan::onConnectionChanged);
    }
    this->pv = new QEpicsPV(this->m_variableName);
    QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &AHUFan::onChanged);
    QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &AHUFan::onConnectionChanged);
}

void AHUFan::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}

void AHUFan::onChanged(const QVariant &value)
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
