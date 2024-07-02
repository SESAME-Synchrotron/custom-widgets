#include "widgets_collection_plugin.h"
#include "pressure_transmitter_plugin.h"
#include "protected_button_plugin.h"
#include "butterfly_valve_plugin.h"
#include "plugins/heat_exchanger_plugin.h"
#include "plugins/flow_transmitter_plugin.h"
#include "plugins/pump_plugin.h"

WidgetsCollectionPlugin::WidgetsCollectionPlugin(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new PressureTransmitterPlugin(this));
    m_widgets.append(new QEProtectedButtonPlugin(this));
    m_widgets.append(new ButterflyValvePlugin(this));
    m_widgets.append(new HeatExchangerPlugin(this));
    m_widgets.append(new FlowTransmitterPlugin(this));
    m_widgets.append(new PumpPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> WidgetsCollectionPlugin::customWidgets() const
{
    return m_widgets;
}
