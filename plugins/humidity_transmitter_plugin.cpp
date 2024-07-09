#include "humidity_transmitter_plugin.h"
#include "humidity_transmitter.h"

HumidityTransmitterPlugin::HumidityTransmitterPlugin(QObject *parent)
{
    Q_UNUSED(parent)
    m_initialized = false;
}

void HumidityTransmitterPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool HumidityTransmitterPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *HumidityTransmitterPlugin::createWidget(QWidget *parent)
{
    return new HumidityTransmitter(parent);
}

QString HumidityTransmitterPlugin::name() const
{
    return QLatin1String("HumidityTransmitter");
}

QString HumidityTransmitterPlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon HumidityTransmitterPlugin::icon() const
{
    return QIcon();
}

QString HumidityTransmitterPlugin::toolTip() const
{
    return QLatin1String("Humidity Transmitter");
}

QString HumidityTransmitterPlugin::whatsThis() const
{
    return QLatin1String("A Humidity Transmitter Widget.");
}

bool HumidityTransmitterPlugin::isContainer() const
{
    return false;
}

QString HumidityTransmitterPlugin::domXml() const
{
    return R"(
            <ui language="c++">
              <widget class="HumidityTransmitter" name="humidityTransmitter">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>45</width>
                    <height>80</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString HumidityTransmitterPlugin::includeFile() const
{
    return QLatin1String("humidity_transmitter.h");
}
