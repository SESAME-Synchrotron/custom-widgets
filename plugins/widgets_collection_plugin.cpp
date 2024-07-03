#include "plugins/widgets_collection_plugin.h"
#include "plugins/pressure_transmitter_plugin.h"
#include "plugins/protected_button_plugin.h"
#include "plugins/butterfly_valve_plugin.h"
#include "plugins/heat_exchanger_plugin.h"
#include "plugins/flow_transmitter_plugin.h"
#include "plugins/pump_plugin.h"
#include "plugins/ahu_fan_plugin.h"

WidgetsCollectionPlugin::WidgetsCollectionPlugin(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new PressureTransmitterPlugin(this));
    m_widgets.append(new QEProtectedButtonPlugin(this));
    m_widgets.append(new ButterflyValvePlugin(this));
    m_widgets.append(new HeatExchangerPlugin(this));
    m_widgets.append(new FlowTransmitterPlugin(this));
    m_widgets.append(new PumpPlugin(this));
    m_widgets.append(new AHUFanPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> WidgetsCollectionPlugin::customWidgets() const
{
    return m_widgets;
}
