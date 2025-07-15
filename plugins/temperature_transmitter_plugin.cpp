#include "temperature_transmitter_plugin.h"
#include "temperature_transmitter.h"

TemperatureTransmitterPlugin::TemperatureTransmitterPlugin(QObject *parent)
{
    Q_UNUSED(parent)
    m_initialized = false;
}

void TemperatureTransmitterPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TemperatureTransmitterPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TemperatureTransmitterPlugin::createWidget(QWidget *parent)
{
    return new TemperatureTransmitter(parent);
}

QString TemperatureTransmitterPlugin::name() const
{
    return QLatin1String("TemperatureTransmitter");
}

QString TemperatureTransmitterPlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon TemperatureTransmitterPlugin::icon() const
{
    return QIcon();
}

QString TemperatureTransmitterPlugin::toolTip() const
{
    return QLatin1String("Temperature Transmitter");
}

QString TemperatureTransmitterPlugin::whatsThis() const
{
    return QLatin1String("A Temperature Transmitter Widget.");
}

bool TemperatureTransmitterPlugin::isContainer() const
{
    return false;
}

QString TemperatureTransmitterPlugin::domXml() const
{
    return R"(
            <ui language="c++" displayname="Temperature Transmitter">
              <widget class="TemperatureTransmitter" name="temperatureTransmitter">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>30</width>
                    <height>70</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString TemperatureTransmitterPlugin::includeFile() const
{
    return QLatin1String("temperature_transmitter.h");
}
