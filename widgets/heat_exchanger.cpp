#include "widgets/heat_exchanger.h"
#include "ui_heat_exchanger.h"

HeatExchanger::HeatExchanger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeatExchanger)
{
    ui->setupUi(this);
}

HeatExchanger::~HeatExchanger()
{
    delete ui;
}

void HeatExchanger::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int _width = width();
    int _height = height();
    QPainter painter(this);

    painter.drawRect(0, 0, _width - 1, _height * 0.1);
    painter.drawLine(0,             _height * 0.1, 0            , _height * 0.9);
    painter.drawLine(_width * 0.25, _height * 0.1, _width * 0.25, _height * 0.9);
    painter.drawLine(_width * 0.50, _height * 0.1, _width * 0.50, _height * 0.9);
    painter.drawLine(_width * 0.75, _height * 0.1, _width * 0.75, _height * 0.9);
    painter.drawLine(_width - 1,    _height * 0.1, _width - 1   , _height * 0.9);
    painter.drawRect(0, _height * 0.9, _width - 1, _height * 0.1 - 1);
}

QString HeatExchanger::pvName() const
{
    return m_variableName;
}

void HeatExchanger::setPVName(const QString name)
{
    this->m_variableName = name;
    if (!this->pv) {
        QObject::disconnect(this->pv, &QEpicsPV::valueChanged, this, &HeatExchanger::onChanged);
        QObject::disconnect(this->pv, &QEpicsPV::connectionChanged, this, &HeatExchanger::onConnectionChanged);
    }
    this->pv = new QEpicsPV(this->m_variableName);
    QObject::connect(this->pv, &QEpicsPV::valueChanged, this, &HeatExchanger::onChanged);
    QObject::connect(this->pv, &QEpicsPV::connectionChanged, this, &HeatExchanger::onConnectionChanged);
}

void HeatExchanger::onConnectionChanged(bool state)
{
    if (!state)
        color = Qt::gray;
    update();
}

void HeatExchanger::onChanged(const QVariant &value)
{
    Q_UNUSED(value)
    update();
}

