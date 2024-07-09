#include "three_way_valve_plugin.h"
#include "three_way_valve.h"

ThreeWayValvePlugin::ThreeWayValvePlugin(QObject *parent)
{
    Q_UNUSED(parent)
    m_initialized = false;
}

void ThreeWayValvePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ThreeWayValvePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ThreeWayValvePlugin::createWidget(QWidget *parent)
{
    return new ThreeWayValve(parent);
}

QString ThreeWayValvePlugin::name() const
{
    return QLatin1String("ThreeWayValve");
}

QString ThreeWayValvePlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon ThreeWayValvePlugin::icon() const
{
    return QIcon();
}

QString ThreeWayValvePlugin::toolTip() const
{
    return QLatin1String("Three way valve");
}

QString ThreeWayValvePlugin::whatsThis() const
{
    return QLatin1String("A Three-way valve Widget.");
}

bool ThreeWayValvePlugin::isContainer() const
{
    return false;
}

QString ThreeWayValvePlugin::domXml() const
{
    return R"(
            <ui language="c++">
              <widget class="ThreeWayValve" name="threeWayValve">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>75</width>
                    <height>50</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString ThreeWayValvePlugin::includeFile() const
{
    return QLatin1String("three_way_valve.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qeprotectedbuttonplugin, QEProtectedButtonPlugin)
#endif // QT_VERSION < 0x050000
