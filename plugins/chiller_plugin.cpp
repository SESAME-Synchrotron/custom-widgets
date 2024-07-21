#include "chiller_plugin.h"
#include "chiller.h"


ChillerPlugin::ChillerPlugin(QObject *parent)
{
    Q_UNUSED(parent)
    m_initialized = false;
}

void ChillerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ChillerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ChillerPlugin::createWidget(QWidget *parent)
{
    return new Chiller(parent);
}

QString ChillerPlugin::name() const
{
    return QLatin1String("Chiller");
}

QString ChillerPlugin::group() const
{
    return QLatin1String("Cooling System");
}

QIcon ChillerPlugin::icon() const
{
    return QIcon();
}

QString ChillerPlugin::toolTip() const
{
    return QLatin1String("Chiller");
}

QString ChillerPlugin::whatsThis() const
{
    return QLatin1String("Chiller");
}

bool ChillerPlugin::isContainer() const
{
    return false;
}

QString ChillerPlugin::domXml() const
{
    return R"(
            <ui language="c++">
              <widget class="Chiller" name="chiller">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>150</width>
                    <height>120</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString ChillerPlugin::includeFile() const
{
    return QLatin1String("chiller.h");
}
