#ifndef DAMPER_H
#define DAMPER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

#include <qepicspv.h>

#include "constants.h"

namespace Ui {
class Damper;
}

class Damper : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString PVName READ pvName WRITE setPVName);
    Q_PROPERTY(Layout  layout READ layout WRITE setLayout);

public:

    enum Layout {
        Horizontal,
        Vertical
    };
    Q_ENUM(Layout);

    explicit Damper(QWidget *parent = nullptr);
    ~Damper();

    QString pvName() const;
    void setPVName(const QString name);

    Layout layout() const;
    void setLayout(const Layout direction);

public slots:
    void onChanged(const QVariant& value);
    void onConnectionChanged(bool state);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::Damper *ui;

    QColor   color;
    QString  m_variableName;

    QEpicsPV* pv;

    Layout m_layout;
};

#endif // DAMPER_H
