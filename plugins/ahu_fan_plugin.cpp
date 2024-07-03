#include "ahu_fan_plugin.h"
#include "widgets/ahu_fan.h"

AHUFanPlugin::AHUFanPlugin(QObject *parent)
{
    Q_UNUSED(parent)
}

void AHUFanPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool AHUFanPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *AHUFanPlugin::createWidget(QWidget *parent)
{
    return new AHUFan(parent);
}

QString AHUFanPlugin::name() const
{
    return QLatin1String("AHUFan");
}

QString AHUFanPlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon AHUFanPlugin::icon() const
{
    return QIcon();
}

QString AHUFanPlugin::toolTip() const
{
    return QLatin1String("AHU Fan");
}

QString AHUFanPlugin::whatsThis() const
{
    return QLatin1String("An AHU Fan.");
}

bool AHUFanPlugin::isContainer() const
{
    return false;
}

QString AHUFanPlugin::domXml() const
{
    return R"(
            <ui language="c++">
              <widget class="AHUFan" name="ahuFan">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>110</width>
                    <height>80</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString AHUFanPlugin::includeFile() const
{
    return QLatin1String("ahu_fan.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qeprotectedbuttonplugin, QEProtectedButtonPlugin)
#endif // QT_VERSION < 0x050000
