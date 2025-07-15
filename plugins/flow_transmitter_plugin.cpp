#include "plugins/flow_transmitter_plugin.h"
#include "widgets/flow_transmitter.h"

FlowTransmitterPlugin::FlowTransmitterPlugin(QObject *parent)
{
    Q_UNUSED(parent)
    m_initialized = false;
}

void FlowTransmitterPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FlowTransmitterPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FlowTransmitterPlugin::createWidget(QWidget *parent)
{
    return new FlowTransmitter(parent);
}

QString FlowTransmitterPlugin::name() const
{
    return QLatin1String("FlowTransmitter");
}

QString FlowTransmitterPlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon FlowTransmitterPlugin::icon() const
{
    return QIcon();
}

QString FlowTransmitterPlugin::toolTip() const
{
    return QLatin1String("Flow Transmitter");
}

QString FlowTransmitterPlugin::whatsThis() const
{
    return QLatin1String("A Flow Transmitter Widget.");
}

bool FlowTransmitterPlugin::isContainer() const
{
    return false;
}

QString FlowTransmitterPlugin::domXml() const
{
    return R"(
            <ui language="c++" displayname="Flow Transmitter">
              <widget class="FlowTransmitter" name="flowTransmitter">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>30</width>
                    <height>60</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString FlowTransmitterPlugin::includeFile() const
{
    return QLatin1String("flow_transmitter.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qeprotectedbuttonplugin, QEProtectedButtonPlugin)
#endif // QT_VERSION < 0x050000
