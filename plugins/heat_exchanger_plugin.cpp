#include "plugins/heat_exchanger_plugin.h"
#include "widgets/heat_exchanger.h"

HeatExchangerPlugin::HeatExchangerPlugin(QObject* parent)
{
    Q_UNUSED(parent)
    m_initialized = false;
}

void HeatExchangerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool HeatExchangerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *HeatExchangerPlugin::createWidget(QWidget *parent)
{
    return new HeatExchanger(parent);
}

QString HeatExchangerPlugin::name() const
{
    return QLatin1String("HeatExchanger");
}

QString HeatExchangerPlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon HeatExchangerPlugin::icon() const
{
    return QIcon();
}

QString HeatExchangerPlugin::toolTip() const
{
    return QLatin1String("Heat Exchanger");
}

QString HeatExchangerPlugin::whatsThis() const
{
    return QLatin1String("A Heat Exchanger Widget.");
}

bool HeatExchangerPlugin::isContainer() const
{
    return false;
}

QString HeatExchangerPlugin::domXml() const
{
    return R"(
            <ui language="c++" displayname="Heat Exchanger">
              <widget class="HeatExchanger" name="heatExchanger">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>30</width>
                    <height>120</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString HeatExchangerPlugin::includeFile() const
{
    return QLatin1String("heat_exchanger.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qeprotectedbuttonplugin, QEProtectedButtonPlugin)
#endif // QT_VERSION < 0x050000
