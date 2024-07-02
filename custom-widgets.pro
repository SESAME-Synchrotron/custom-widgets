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
    widgets/butterfly_valve.ui \
    widgets/flow_transmitter.ui \
    widgets/heat_exchanger.ui \
    widgets/pressure_transmitter.ui \
    widgets/pump.ui

HEADERS += \
    plugins/flow_transmitter_plugin.h \
    plugins/heat_exchanger_plugin.h \
    plugins/pump_plugin.h \
    widgets/butterfly_valve.h \
    plugins/butterfly_valve_plugin.h \
    constants.h \
    widgets/flow_transmitter.h \
    widgets/heat_exchanger.h \
    widgets/pressure_transmitter.h \
    plugins/pressure_transmitter_plugin.h \
    widgets/protected_button.h \
    plugins/protected_button_plugin.h \
    plugins/widgets_collection_plugin.h \
    widgets/pump.h

SOURCES += \
    plugins/flow_transmitter_plugin.cpp \
    plugins/heat_exchanger_plugin.cpp \
    plugins/pump_plugin.cpp \
    widgets/butterfly_valve.cpp \
    plugins/butterfly_valve_plugin.cpp \
    widgets/flow_transmitter.cpp \
    widgets/heat_exchanger.cpp \
    widgets/pressure_transmitter.cpp \
    plugins/pressure_transmitter_plugin.cpp \
    widgets/protected_button.cpp \
    plugins/protected_button_plugin.cpp \
    plugins/widgets_collection_plugin.cpp \
    widgets/pump.cpp

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

INCLUDEPATH += $$(EPICS_BASE)/include \
               $$(QWT_ROOT)/include \
               $$(QE_TARGET_DIR)/include \
               $$(EPICS_BASE)/include/os/Linux \
               $$(EPICS_BASE)/include/compiler/gcc
