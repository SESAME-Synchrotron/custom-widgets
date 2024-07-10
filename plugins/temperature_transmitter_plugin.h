#ifndef TEMPERATURETRANSMITTERPLUGIN_H
#define TEMPERATURETRANSMITTERPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class TemperatureTransmitterPlugin : public QDesignerCustomWidgetInterface
{
public:
    TemperatureTransmitterPlugin(QObject* parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool m_initialized;
};

#endif // TEMPERATURETRANSMITTERPLUGIN_H
