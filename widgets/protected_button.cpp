#include "widgets/protected_button.h"

QEProtectedButton::QEProtectedButton(QWidget *parent) :
    QPushButton(parent)
{
    if (!m_variableName.isEmpty()) {
        m_protectionPV = new QEpicsPV(m_variableName);
        QObject::connect(m_protectionPV, SIGNAL(valueChanged(QVariant)), this, SLOT(onProtectionPVChanged(QVariant)));
    }
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    m_values.push_back(3);
    m_values.push_back(6);
    m_values.push_back(7);

    this->setStyleSheet("background-color: #eed5b7");
    this->setText("Protected Button");
}

void QEProtectedButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
}

void QEProtectedButton::onProtectionPVChanged(QVariant &value)
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
    QMessageBox::StandardButton button = QMessageBox::warning(this,
                                                              "Warning", "You are about to execute an action that might affect machine operation, BE CAREFUL!",
                                                              QMessageBox::Ok | QMessageBox::Abort);
    if (button != QMessageBox::Ok)
        return;

    emit protectionClicked();
}
