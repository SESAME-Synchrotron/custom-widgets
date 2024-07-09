TEMPLATE  = lib
CONFIG   += plugin
QT       += designer widgets uiplugin
TARGET    = customwidgets

DESTDIR          = build-
OBJECTS_DIR      = $$DESTDIR
MOC_DIR          = $$DESTDIR
RCC_DIR          = $$DESTDIR
UI_DIR           = $$DESTDIR
QMAKE_DISTCLEAN += -r $$DESTDIR

FORMS += \
    widgets/ahu_fan.ui \
    widgets/butterfly_valve.ui \
    widgets/flow_transmitter.ui \
    widgets/heat_exchanger.ui \
    widgets/humidity_transmitter.ui \
    widgets/pressure_transmitter.ui \
    widgets/pump.ui \
    widgets/three_way_valve.ui

HEADERS += \
    plugins/ahu_fan_plugin.h \
    plugins/flow_transmitter_plugin.h \
    plugins/heat_exchanger_plugin.h \
    plugins/humidity_transmitter_plugin.h \
    plugins/pump_plugin.h \
    plugins/three_way_valve_plugin.h \
    widgets/ahu_fan.h \
    widgets/butterfly_valve.h \
    plugins/butterfly_valve_plugin.h \
    constants.h \
    widgets/flow_transmitter.h \
    widgets/heat_exchanger.h \
    widgets/humidity_transmitter.h \
    widgets/pressure_transmitter.h \
    plugins/pressure_transmitter_plugin.h \
    widgets/protected_button.h \
    plugins/protected_button_plugin.h \
    plugins/widgets_collection_plugin.h \
    widgets/pump.h \
    widgets/three_way_valve.h

SOURCES += \
    plugins/ahu_fan_plugin.cpp \
    plugins/flow_transmitter_plugin.cpp \
    plugins/heat_exchanger_plugin.cpp \
    plugins/humidity_transmitter_plugin.cpp \
    plugins/pump_plugin.cpp \
    plugins/three_way_valve_plugin.cpp \
    widgets/ahu_fan.cpp \
    widgets/butterfly_valve.cpp \
    plugins/butterfly_valve_plugin.cpp \
    widgets/flow_transmitter.cpp \
    widgets/heat_exchanger.cpp \
    widgets/humidity_transmitter.cpp \
    widgets/pressure_transmitter.cpp \
    plugins/pressure_transmitter_plugin.cpp \
    widgets/protected_button.cpp \
    plugins/protected_button_plugin.cpp \
    plugins/widgets_collection_plugin.cpp \
    widgets/pump.cpp \
    widgets/three_way_valve.cpp

headers.path  = $$[QT_INSTALL_HEADERS]/
headers.files = $$HEADERS
target.path   = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS     += headers target

unix:!macx: LIBS += -L$$(QE_TARGET_DIR)/lib/linux-x86_64/ -lQEFramework \
                    -L$$(QE_TARGET_DIR)/lib/linux-x86_64/designer -lQEPlugin \
                    -L$$(QWT_ROOT)/lib/ -lqwt \
                    -L$$(EPICS_BASE)/lib/linux-x86_64/ -lca \
                    -L$$(EPICS_BASE)/lib/linux-x86_64/ -lCom

DEPENDPATH += $$(EPICS_BASE)/include \
              $$(QWT_ROOT)/include \
              $$(QE_TARGET_DIR)/include \
              $$(EPICS_BASE)/include/os/Linux

INCLUDEPATH += widgets/ plugins/ \
               $$(EPICS_BASE)/include \
               $$(QWT_ROOT)/include \
               $$(QE_TARGET_DIR)/include \
               $$(EPICS_BASE)/include/os/Linux \
               $$(EPICS_BASE)/include/compiler/gcc
