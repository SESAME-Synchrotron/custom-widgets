#ifndef QEPROTECTEDBUTTON_H
#define QEPROTECTEDBUTTON_H

#include <QEPushButton.h>
#include "qepicspv.h"
#include <QMessageBox>
#include <QMouseEvent>

#include <algorithm>
using std::find;

class QEProtectedButton : public QEPushButton
{
    Q_OBJECT

public:
    QEProtectedButton(QWidget *parent = 0);

public slots:
    void onMachineStatusChanged(QVariant& value);

    void onButtonClicked();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QEpicsPV* m_machineStatus;

    QList<int> m_values;
};

#endif // QEPROTECTEDBUTTON_H
