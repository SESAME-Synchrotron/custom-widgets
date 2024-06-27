#include "widgets_collection_plugin.h"
#include "pressure_transmitter_plugin.h"
#include "protected_button_plugin.h"
#include "butterfly_valve_plugin.h"

WidgetsCollectionPlugin::WidgetsCollectionPlugin(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new PressureTransmitterPlugin(this));
    m_widgets.append(new QEProtectedButtonPlugin(this));
    m_widgets.append(new ButterflyValvePlugin(this));
}

QList<QDesignerCustomWidgetInterface*> WidgetsCollectionPlugin::customWidgets() const
{
    return m_widgets;
}
