#ifndef QEPROTECTEDBUTTON_H
#define QEPROTECTEDBUTTON_H

#include <QPushButton>
#include <QMessageBox>

#include "qepicspv.h"

#include <algorithm>
using std::find;

class QEProtectedButton : public QPushButton
{
    Q_OBJECT

public:
    QEProtectedButton(QWidget *parent = 0);

    Q_PROPERTY(QString protectionVariableName READ getProtectionVariableName WRITE setProtectionVariableName NOTIFY protectionVariableChanged)

    QString getProtectionVariableName() {
        return m_variableName;
    }

    void setProtectionVariableName(QString& name) {
        m_variableName = name;
        if (!m_variableName.isEmpty()) {
            if (!m_protectionPV)
                QObject::disconnect(m_protectionPV, SIGNAL(valueChanged(QVariant)), this, SLOT(onProtectionPVChanged(QVariant)));

            m_protectionPV = new QEpicsPV(m_variableName);
            QObject::connect(m_protectionPV, SIGNAL(valueChanged(QVariant)), this, SLOT(onProtectionPVChanged(QVariant)));
        }
        emit protectionVariableChanged(name);
    }

signals:
    void protectionVariableChanged(QString& name);

    void protectionClicked();

public slots:
    void onProtectionPVChanged(QVariant& value);

    void onButtonClicked();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QEpicsPV* m_protectionPV;

    QList<int> m_values;
    QString m_variableName;
};

#endif // QEPROTECTEDBUTTON_H
