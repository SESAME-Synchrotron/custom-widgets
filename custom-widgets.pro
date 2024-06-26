TEMPLATE  = lib
CONFIG   += plugin
QT       += designer widgets uiplugin
TARGET = customwidgets

FORMS += \
    pressure_transmitter.ui

HEADERS += \
    constants.h \
    pressure_transmitter.h \
    pressure_transmitter_plugin.h

SOURCES += \
    pressure_transmitter.cpp \
    pressure_transmitter_plugin.cpp

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
