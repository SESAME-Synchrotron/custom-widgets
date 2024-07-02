#include "widgets/protected_button.h"

QEProtectedButton::QEProtectedButton(QWidget *parent) :
    QEPushButton(parent)
{
    m_machineStatus = new QEpicsPV("Test:PV");
    QObject::connect(m_machineStatus, SIGNAL(valueChanged(QVariant)), this, SLOT(onMachineStatusChanged(QVariant)));
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    m_values.push_back(3);
    m_values.push_back(6);
    m_values.push_back(7);

    this->setStyleSheet("background-color: #eed5b7");
}

void QEProtectedButton::paintEvent(QPaintEvent *event)
{
    QEPushButton::paintEvent(event);
}

void QEProtectedButton::onMachineStatusChanged(QVariant &value)
{
    int status = value.toInt();
    if (std::find(m_values.begin(), m_values.end(), status) != m_values.end()) {
        this->setDisabled(true);
    }
    else
        this->setDisabled(false);

    this->setStyleSheet("background-color: #eed5b7");
}

void QEProtectedButton::onButtonClicked()
{
    QMessageBox::information(this, "Warning", "You are about to execute an action that might affect machine operation, BE CAREFUL!", QMessageBox::Ok);
}
