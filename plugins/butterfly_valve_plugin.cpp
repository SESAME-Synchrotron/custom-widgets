#include "plugins/butterfly_valve_plugin.h"
#include "widgets/butterfly_valve.h"

ButterflyValvePlugin::ButterflyValvePlugin(QObject *parent)
{
    Q_UNUSED(parent)
    m_initialized = false;
}

void ButterflyValvePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ButterflyValvePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ButterflyValvePlugin::createWidget(QWidget *parent)
{
    return new ButterflyValve(parent);
}

QString ButterflyValvePlugin::name() const
{
    return QLatin1String("ButterflyValve");
}

QString ButterflyValvePlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon ButterflyValvePlugin::icon() const
{
    return QIcon(":/icons/butterfly_valve.png");
}

QString ButterflyValvePlugin::toolTip() const
{
    return QLatin1String("Butterfly Valve");
}

QString ButterflyValvePlugin::whatsThis() const
{
    return QLatin1String("A Butterfly Valve.");
}

bool ButterflyValvePlugin::isContainer() const
{
    return false;
}

QString ButterflyValvePlugin::domXml() const
{
    return R"(
            <ui language="c++">
              <widget class="ButterflyValve" name="butterflyValvePlugin">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>40</width>
                    <height>40</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString ButterflyValvePlugin::includeFile() const
{
    return QLatin1String("butterfly_valve.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qeprotectedbuttonplugin, QEProtectedButtonPlugin)
#endif // QT_VERSION < 0x050000
