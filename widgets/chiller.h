#ifndef CHILLER_H
#define CHILLER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class Chiller;
}

class Chiller : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString       PVName   READ pvName        WRITE setPVName);

public:
    explicit Chiller(QWidget *parent = nullptr);
    ~Chiller();

    QString pvName() const;
    void setPVName(const QString name);

public slots:
    void onChanged(const QVariant& value);
    void onConnectionChanged(bool state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::Chiller *ui;

    QColor  m_color;
    QString m_variableName;

    QEpicsPV* pv;
};

#endif // CHILLER_H
