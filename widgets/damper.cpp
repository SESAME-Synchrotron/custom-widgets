#include "damper.h"
#include "ui_damper.h"

Damper::Damper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Damper)
{
    ui->setupUi(this);
    color = Qt::gray;

    this->pv = nullptr;
}

Damper::~Damper()
{
    delete ui;
}

void Damper::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QBrush currentBrush = painter.brush();

    int width = this->width();
    int height = this->height();

    if (m_layout == Layout::Horizontal) {
        painter.translate(width / 2, height / 2);
        painter.rotate(90);
        painter.translate(-width / 2, -height / 2);
    }
    else {
        painter.translate(width / 2, height / 2);
        painter.rotate(0);
        painter.translate(-width / 2, -height / 2);
    }

    painter.setBrush(color);
    painter.drawRect(width / 2 - 20, 0, 40, 5);
    painter.drawRect(width / 2 - 20, height - 6, 40, 5);
    painter.drawRect(width / 2 - 10, 5, 20, height - 11);

    painter.drawLine(width / 2 - 10, 5, width / 2 + 10, ((height - 10) / 5) + 5);
    painter.drawLine(width / 2 + 10, 1 * ((height - 10) / 5) + 5, width / 2 - 10, 2 * ((height - 10) / 5) + 5);
    painter.drawLine(width / 2 - 10, 2 * ((height - 10) / 5) + 5, width / 2 + 10, 3 * ((height - 10) / 5) + 5);
    painter.drawLine(width / 2 + 10, 3 * ((height - 10) / 5) + 5, width / 2 - 10, 4 * ((height - 10) / 5) + 5);
    painter.drawLine(width / 2 - 10, 4 * ((height - 10) / 5) + 5, width / 2 + 10, 5 * ((height - 10) / 5) + 5);
}

QString Damper::pvName() const
{
    return m_variableName;
}

void Damper::setPVName(const QString name)
{
    this->m_variableName = name;

     if (this->pv) {
         QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &Damper::onChanged);
         QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &Damper::onConnectionChanged);
     }
     this->pv = new QEpicsPV(this->m_variableName);
     QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &Damper::onChanged);
     QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &Damper::onConnectionChanged);
}

void Damper::onChanged(const QVariant &value)
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

void Damper::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}

Damper::Layout Damper::layout() const
{
    return m_layout;
}

void Damper::setLayout(const Layout direction)
{
    m_layout = direction;
    update();
}
