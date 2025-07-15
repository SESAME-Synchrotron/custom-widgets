#include "widgets/protected_button.h"
#include "plugins/protected_button_plugin.h"

QEProtectedButtonPlugin::QEProtectedButtonPlugin(QObject *parent)
{
    Q_UNUSED(parent)
    m_initialized = false;
}

void QEProtectedButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QEProtectedButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QEProtectedButtonPlugin::createWidget(QWidget *parent)
{
    return new QEProtectedButton(parent);
}

QString QEProtectedButtonPlugin::name() const
{
    return QLatin1String("QEProtectedButton");
}

QString QEProtectedButtonPlugin::group() const
{
    return QLatin1String("Custom Widgets");
}

QIcon QEProtectedButtonPlugin::icon() const
{
    return QIcon();
}

QString QEProtectedButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QEProtectedButtonPlugin::whatsThis() const
{
    return QLatin1String("A Custom QEPushButton implementation where it becomes protected from user click events when the machine is user mode.");
}

bool QEProtectedButtonPlugin::isContainer() const
{
    return false;
}

QString QEProtectedButtonPlugin::domXml() const
{
    return R"(
            <ui language="c++" displayname="Protected Button">
              <widget class="QEProtectedButton" name="protectedButton">
                <property name="geometry">
                  <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>20</width>
                    <height>80</height>
                  </rect>
                </property>
              </widget>
            </ui>
           )";
}

QString QEProtectedButtonPlugin::includeFile() const
{
    return QLatin1String("protected_button.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qeprotectedbuttonplugin, QEProtectedButtonPlugin)
#endif // QT_VERSION < 0x050000
