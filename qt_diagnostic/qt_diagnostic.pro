QT       += core gui gui-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Node/node.cpp \
    activeMsg/activemsg.cpp \
    choicedialog.cpp \
    conditiondialog.cpp \
    diagTP/diagio.c \
    diagTP/vector.cpp \
    dialog.cpp \
    executionTask/cycle.c \
    flash/flash.cpp \
    hex/binstr_conv.c \
    hex/intelHex.c \
    httpsclient/httpsclient.cpp \
    inputdialog.cpp \
    json/src/ParseJson.c \
    json/src/cJSON.c \
    json/src/diagnosticConfig.c \
    libui.cpp \
    main.cpp \
    mainwindow.cpp \
    mqtt/mqttclient.cpp \
    odx/load_index.cpp \
    odx/load_odx_c.cpp \
    odx/load_odx_cs.cpp \
    odx/load_odx_d.cpp \
    odx/load_odx_f.cpp \
    odx/load_odx_v.cpp \
    odx/load_pdx.cpp \
    odx/odx_cmn.cpp \
    otx/class_Charts/chart_base.cpp \
    otx/class_Charts/chart_diamond.cpp \
    otx/class_Charts/chart_ellipse.cpp \
    otx/class_Charts/chart_label.cpp \
    otx/class_Charts/chart_line.cpp \
    otx/class_Charts/chart_plaintext.cpp \
    otx/class_Charts/chart_rect.cpp \
    otx/class_Charts/chart_roundrect.cpp \
    otx/class_Charts/chart_trapezoid.cpp \
    otx/flowchart.cpp \
    otx/otx.cpp \
    uds/can_iso_tp/can_iso_tp.c \
    uds/fifo/FIFOQUEUE.c \
    uds/iso_tp_config.c \
    uds/mcu_lock/mcu_lock.c \
    odx/pugixml/pugixml.cpp

HEADERS += \
    Node/node.h \
    activeMsg/activemsg.h \
    choicedialog.h \
    conditiondialog.h \
    diagTP/diagio.h \
    diagTP/PCANBasic.h \
    diagTP/vectorCan.h \
    diagTP/vxlapi.h \
    dialog.h \
    executionTask/cycle.h \
    flash/flash.h \
    hex/intelHex.h \
    httpsclient/httpsclient.h \
    httpsclient/curl/curl.h \
    httpsclient/curl/curlver.h \
    httpsclient/curl/easy.h \
    httpsclient/curl/header.h \
    httpsclient/curl/mprintf.h \
    httpsclient/curl/multi.h \
    httpsclient/curl/options.h \
    httpsclient/curl/stdcheaders.h \
    httpsclient/curl/system.h \
    httpsclient/curl/typecheck-gcc.h \
    httpsclient/curl/urlapi.h \
    httpsclient/curl/websockets.h \
    httpsclient/httpsclient.h \
    inputdialog.h \
    json/include/cJSON.h \
    json/include/diagnosticConfig.h \
    json/include/parseJson.h \
    libui.h \
    mainwindow.h \
    mqtt/mosquitto.h \
    mqtt/mosquitto_broker.h \
    mqtt/mosquitto_plugin.h \
    mqtt/mqtt_protocol.h \
    mqtt/mqttclient.h \
    odx/load_index.h \
    odx/load_odx_c.h \
    odx/load_odx_cs.h \
    odx/load_odx_d.h \
    odx/load_odx_f.h \
    odx/load_odx_v.h \
    odx/load_pdx.h \
    odx/odx_cmn.h \
    odx/pugixml/pugiconfig.h \
    odx/pugixml/pugixml.h \
    otx/class_Charts/chart_base.h \
    otx/class_Charts/chart_diamond.h \
    otx/class_Charts/chart_ellipse.h \
    otx/class_Charts/chart_label.h \
    otx/class_Charts/chart_line.h \
    otx/class_Charts/chart_plaintext.h \
    otx/class_Charts/chart_rect.h \
    otx/class_Charts/chart_roundrect.h \
    otx/class_Charts/chart_trapezoid.h \
    otx/comdef.h \
    otx/flowchart.h \
    otx/otx.h \
    uds/can_iso_tp/can_iso_tp.h \
    uds/can_iso_tp/can_iso_tp_private.h \
    uds/fifo/FIFOQUEUE.h \
    uds/iso_tp_config.h \
    uds/mcu_lock/mcu_lock.h

FORMS += \
    choicedialog.ui \
    conditiondialog.ui \
    dialog.ui \
    inputdialog.ui \
    mainwindow.ui


LIBS += -L$$PWD/../ReleaseDiagnostic/DLL -lvxlapi64
LIBS += -L$$PWD/../ReleaseDiagnostic/DLL -lPCANBasic
LIBS += -L$$PWD/../ReleaseDiagnostic/DLL -lmosquitto
LIBS += -L$$PWD/../ReleaseDiagnostic/DLL -llibcurl-x64
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/img/MainIco.png \
    images/img/Round.png \
    images/img/Rounded_Rectangle.png \
    images/img/arrow0.png \
    images/img/arrow1.png \
    images/img/arrow2.png \
    images/img/arrow3.png \
    images/img/diamond.png \
    images/img/file_add.png \
    images/img/file_delete.png \
    images/img/file_open.png \
    images/img/file_save.png \
    images/img/line.png \
    images/img/rectangle.png \
    images/img/settings.png \
    images/img/trapezoid.png \
    images/logo.ico \
    images/logo.rc \
    odx/pugixml-1.14/CMakeLists.txt \
    odx/pugixml-1.14/LICENSE.md \
    odx/pugixml-1.14/docs/images/dom_tree.png \
    odx/pugixml-1.14/docs/images/vs2005_link1.png \
    odx/pugixml-1.14/docs/images/vs2005_link2.png \
    odx/pugixml-1.14/docs/images/vs2005_pch1.png \
    odx/pugixml-1.14/docs/images/vs2005_pch2.png \
    odx/pugixml-1.14/docs/images/vs2005_pch3.png \
    odx/pugixml-1.14/docs/images/vs2005_pch4.png \
    odx/pugixml-1.14/docs/images/vs2010_link1.png \
    odx/pugixml-1.14/docs/images/vs2010_link2.png \
    odx/pugixml-1.14/docs/manual.html \
    odx/pugixml-1.14/docs/quickstart.html \
    odx/pugixml-1.14/docs/samples/character.xml \
    odx/pugixml-1.14/docs/samples/transitions.xml \
    odx/pugixml-1.14/docs/samples/tree.xml \
    odx/pugixml-1.14/docs/samples/weekly-shift_jis.xml \
    odx/pugixml-1.14/docs/samples/weekly-utf-16.xml \
    odx/pugixml-1.14/docs/samples/weekly-utf-8.xml \
    odx/pugixml-1.14/docs/samples/xgconsole.xml \
    odx/pugixml-1.14/readme.txt \
    odx/pugixml-1.14/scripts/cocoapods_push.sh \
    odx/pugixml-1.14/scripts/natvis/pugixml.natvis \
    odx/pugixml-1.14/scripts/natvis/pugixml_compact.natvis \
    odx/pugixml-1.14/scripts/nuget/build/native/pugixml-propertiesui.xml \
    odx/pugixml-1.14/scripts/nuget/build/native/pugixml.targets \
    odx/pugixml-1.14/scripts/nuget/pugixml.nuspec \
    odx/pugixml-1.14/scripts/nuget_build.ps1 \
    odx/pugixml-1.14/scripts/premake4.lua \
    odx/pugixml-1.14/scripts/pugixml-config.cmake.in \
    odx/pugixml-1.14/scripts/pugixml.pc.in \
    odx/pugixml-1.14/scripts/pugixml.podspec \
    odx/pugixml-1.14/scripts/pugixml.xcodeproj/project.pbxproj \
    odx/pugixml-1.14/scripts/pugixml_airplay.mkf \
    odx/pugixml-1.14/scripts/pugixml_codeblocks.cbp \
    odx/pugixml-1.14/scripts/pugixml_codelite.project \
    odx/pugixml-1.14/scripts/pugixml_vs2005.vcproj \
    odx/pugixml-1.14/scripts/pugixml_vs2005_static.vcproj \
    odx/pugixml-1.14/scripts/pugixml_vs2008.vcproj \
    odx/pugixml-1.14/scripts/pugixml_vs2008_static.vcproj \
    odx/pugixml-1.14/scripts/pugixml_vs2010.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2010_static.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2013.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2013_static.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2015.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2015_static.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2017.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2017_static.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2019.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2019_static.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2022.vcxproj \
    odx/pugixml-1.14/scripts/pugixml_vs2022_static.vcxproj

RESOURCES += \
    icon.qrc


