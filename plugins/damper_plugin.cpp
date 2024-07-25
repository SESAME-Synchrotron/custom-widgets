#include "damper_plugin.h"
#include "damper.h"

DamperPlugin::DamperPlugin(QObject *parent)
{
    Q_UNUSED(parent)
}

void DamperPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool DamperPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *DamperPlugin::createWidget(QWidget *parent)
{
    return new Damper(parent);
}

QString DamperPlugin::name() const
{
    return QLatin1String("Damper");
}

QString DamperPlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon DamperPlugin::icon() const
{
    return QIcon();
}

QString DamperPlugin::toolTip() const
{
    return QLatin1String("Damper");
}

QString DamperPlugin::whatsThis() const
{
    return QLatin1String("Damper.");
}

bool DamperPlugin::isContainer() const
{
    return false;
}

QString DamperPlugin::domXml() const
{
    return R"(
            <ui language="c++">
              <widget class="Damper" name="damper">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>80</width>
                    <height>80</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString DamperPlugin::includeFile() const
{
    return QLatin1String("damper.h");
}
