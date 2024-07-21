#include "chiller.h"
#include "ui_chiller.h"

Chiller::Chiller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chiller)
{
    ui->setupUi(this);
    this->pv = nullptr;
    m_color = Qt::gray;
}

Chiller::~Chiller()
{
    delete ui;
}

void Chiller::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int width = this->width();
    int height = this->height();
    QPainter painter(this);

    QLinearGradient gradient(0, 0, 0, height);
    gradient.setColorAt(0, m_color);
    gradient.setColorAt(0.5, Qt::white);
    gradient.setColorAt(1, m_color);

    painter.setBrush(gradient);
    painter.drawRect(0, 0, width - 1, height / 2 - 5);
    painter.drawRect(20, height / 2 - 5, width - 40, 10);
    painter.drawRect(0, height / 2 + 5, width - 1, height / 2 - 5 - 1);
}

QString Chiller::pvName() const
{
    return m_variableName;
}

void Chiller::setPVName(const QString name)
{
    this->m_variableName = name;
    if (this->pv) {
        QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &Chiller::onChanged);
        QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &Chiller::onConnectionChanged);
    }
    this->pv = new QEpicsPV(this->m_variableName);
    QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &Chiller::onChanged);
    QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &Chiller::onConnectionChanged);
}

void Chiller::onConnectionChanged(bool state)
{
    if (!state)
        m_color = Qt::gray;
    update();
}

void Chiller::onChanged(const QVariant &value)
{
    int state = value.toInt();
    switch (state) {
    case STATE_OFF:
        m_color = Qt::yellow;
        break;

    case STATE_ON:
        m_color = Qt::green;
        break;

    case STATE_FAULT:
        m_color = Qt::red;
        break;

    default:
        m_color = Qt::gray;
        break;
    }

    update();
    setToolTip(pvName() + " - " + QString::number(value.toDouble()));
}

