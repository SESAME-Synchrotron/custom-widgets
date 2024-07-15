#include "plugins/pump_plugin.h"
#include "widgets/pump.h"

PumpPlugin::PumpPlugin(QObject *parent)
{
    Q_UNUSED(parent)
    m_initialized = false;
}

void PumpPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool PumpPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PumpPlugin::createWidget(QWidget *parent)
{
    return new Pump(parent);
}

QString PumpPlugin::name() const
{
    return QLatin1String("Pump");
}

QString PumpPlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon PumpPlugin::icon() const
{
    return QIcon();
}

QString PumpPlugin::toolTip() const
{
    return QLatin1String("Pump");
}

QString PumpPlugin::whatsThis() const
{
    return QLatin1String("A Water Pump Widget.");
}

bool PumpPlugin::isContainer() const
{
    return false;
}

QString PumpPlugin::domXml() const
{
    return R"(
            <ui language="c++">
              <widget class="Pump" name="pump">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>50</width>
                    <height>50</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString PumpPlugin::includeFile() const
{
    return QLatin1String("pump.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qeprotectedbuttonplugin, QEProtectedButtonPlugin)
#endif // QT_VERSION < 0x050000
