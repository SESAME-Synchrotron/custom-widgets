#include "ahu_fan.h"
#include "ui_ahu_fan.h"

AHUFan::AHUFan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AHUFan)
{
    ui->setupUi(this);
    m_flipped = false;
    color = Qt::gray;

    pv = nullptr;
}

AHUFan::~AHUFan()
{
    delete ui;
}

void AHUFan::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    bool checkFlipped = false;
    QPolygon p;
    int _width = width();
    int _height = height();
    double center = (_width - 20) / 2;

    QPainterPath path;
    path.arcTo(QRect(0, 0, 2 * center, 2 * center), 30, -300);

    QPainter painter(this);
    if (m_flipped) {
        painter.translate(_width / 2, 0);
        painter.scale(-1, 1);
        painter.translate(-_width / 2, 0);
    }
    else {
        if (checkFlipped) {
            painter.translate(_width / 2, _height / 2);
            painter.rotate(-180);
            painter.translate(-_width / 2, -_height / 2);
            checkFlipped = false;
        }
    }
    painter.setBrush(color);

    painter.drawEllipse(QPoint(center, center), (int) center - 1, (int) center - 1);
    // painter.drawArc(QRect(0, 0, 2 * center, 2 * center), 30 * 16, -300 * 16);

    painter.drawEllipse(QPoint(center, center), (int) center / 2, (int) center / 2);

    painter.setRenderHint(QPainter::Antialiasing);

    // Define the path to fill the area between the lines
    QPainterPath fillPath;
    fillPath.moveTo(center, 0);
    fillPath.lineTo(_width - 1, 0);
    fillPath.lineTo(_width - 1, _height / 4);
    fillPath.lineTo((qSqrt(3) * (center) / 2) + center + 1, _height / 4);
    fillPath.lineTo(center, 0);
    fillPath.closeSubpath();

    // Fill the area between the lines
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawPath(fillPath);

    painter.setPen(Qt::black); // Reset pen for the remaining drawing
    painter.drawLine(center, 0, _width - 1, 0);
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
    if (this->pv) {
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
bool AHUFan::isFlipped() const
{
    return m_flipped;
}

void AHUFan::setFlipped(const bool direction)
{
    m_flipped = direction;
    update();
}
