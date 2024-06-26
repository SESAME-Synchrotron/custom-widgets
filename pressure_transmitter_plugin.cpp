#include "pressure_transmitter_plugin.h"
#include "pressure_transmitter.h"

#include <QtPlugin>

PressureTransmitterPlugin::PressureTransmitterPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void PressureTransmitterPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool PressureTransmitterPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PressureTransmitterPlugin::createWidget(QWidget *parent)
{
    return new PressureTransmitter(parent);
}

QString PressureTransmitterPlugin::name() const
{
    return QLatin1String("PressureTransmitter");
}

QString PressureTransmitterPlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon PressureTransmitterPlugin::icon() const
{
    return QIcon();
}

QString PressureTransmitterPlugin::toolTip() const
{
    return QLatin1String("Pressure Transmitter");
}

QString PressureTransmitterPlugin::whatsThis() const
{
    return QLatin1String("A Pressure Transmitter Widget.");
}

bool PressureTransmitterPlugin::isContainer() const
{
    return false;
}

QString PressureTransmitterPlugin::domXml() const
{
    return R"(
            <ui language="c++">
              <widget class="PressureTransmitter" name="pressureTransmitter">
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

QString PressureTransmitterPlugin::includeFile() const
{
    return QLatin1String("pressure_transmitter.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qeprotectedbuttonplugin, QEProtectedButtonPlugin)
#endif // QT_VERSION < 0x050000
