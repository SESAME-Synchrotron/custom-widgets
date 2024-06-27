TEMPLATE  = lib
CONFIG   += plugin
QT       += designer widgets uiplugin
TARGET = customwidgets

FORMS += \
    widgets/butterfly_valve.ui \
    widgets/pressure_transmitter.ui

HEADERS += \
    widgets/butterfly_valve.h \
    plugins/butterfly_valve_plugin.h \
    constants.h \
    widgets/pressure_transmitter.h \
    plugins/pressure_transmitter_plugin.h \
    widgets/protected_button.h \
    plugins/protected_button_plugin.h \
    plugins/widgets_collection_plugin.h

SOURCES += \
    widgets/butterfly_valve.cpp \
    plugins/butterfly_valve_plugin.cpp \
    widgets/pressure_transmitter.cpp \
    plugins/pressure_transmitter_plugin.cpp \
    widgets/protected_button.cpp \
    plugins/protected_button_plugin.cpp \
    plugins/widgets_collection_plugin.cpp

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
