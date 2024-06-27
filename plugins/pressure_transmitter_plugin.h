#ifndef PRESSURETRANSMITTERPLUGIN_H
#define PRESSURETRANSMITTERPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class PressureTransmitterPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    // Q_PLUGIN_METADATA(IID "org.qt-project.Qt.PressureTransmitterPlugin")

public:
    PressureTransmitterPlugin(QObject* parent = 0);

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

#endif // PRESSURETRANSMITTERPLUGIN_H
