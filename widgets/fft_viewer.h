#ifndef FFT_VIEWER_H
#define FFT_VIEWER_H

#include <QWidget>
#include <QtCharts>
#include <QTimer>
#include <cadef.h>
#include <opencv2/core/core.hpp>
#include <iostream>

#define MAX_SOURCES 4

namespace Ui {
class QEFastFourierTransform;
}

class QEFastFourierTransform : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString dataSourceA READ dataSourceA WRITE setDataSourceA NOTIFY dataSourceAChanged)
    Q_PROPERTY(QString dataSourceB READ dataSourceB WRITE setDataSourceB NOTIFY dataSourceBChanged)
    Q_PROPERTY(QString dataSourceC READ dataSourceC WRITE setDataSourceC NOTIFY dataSourceCChanged)
    Q_PROPERTY(QString dataSourceD READ dataSourceD WRITE setDataSourceD NOTIFY dataSourceDChanged)
    Q_PROPERTY(int numberOfPoints READ numberOfPoints WRITE setNumberOfPoints NOTIFY numberOfPointsChanged)
    Q_PROPERTY(QString title READ titleText WRITE setTitle)

public:
    explicit QEFastFourierTransform(QWidget *parent = nullptr);
    ~QEFastFourierTransform();

    QString dataSourceA();
    QString dataSourceB();
    QString dataSourceC();
    QString dataSourceD();
    void setDataSourceA(QString name);
    void setDataSourceB(QString name);
    void setDataSourceC(QString name);
    void setDataSourceD(QString name);

    int numberOfPoints();
    void setNumberOfPoints(int n);

    QString titleText();
    void setTitle(QString title);

    void calculateFFT();

signals:
    void dataSourceAChanged(QString& name);
    void dataSourceBChanged(QString& name);
    void dataSourceCChanged(QString& name);
    void dataSourceDChanged(QString& name);
    void numberOfPointsChanged(int n);

private:
    Ui::QEFastFourierTransform *ui;

    void modifySeries(int index);

    QTimer* timer;
    QChart* chart;
    QValueAxis* xAxis;
    QValueAxis* yAxis;

    // QVector<QLineSeries*> series;
    std::array<QLineSeries*, MAX_SOURCES> series;

    // QVector<std::array<double, 200>> rawData;
    std::array<double, 200> rawData[MAX_SOURCES];

    QStringList   pvs;
    QVector<chid> ids;
    int points;
    QString text;

    QPen colors[MAX_SOURCES] = {QPen(Qt::red), QPen(Qt::blue), QPen(Qt::green), QPen(Qt::yellow)};
};

#endif // FFT_VIEWER_H
