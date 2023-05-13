######################################################################
# Automatically generated by qmake (2.01a) Thu Mar 13 16:12:55 2014
######################################################################

GITREV = $$system(git rev-list --count HEAD)
GITREVSTR = '\\"$${GITREV}\\"'
GITHASH = $$system(git rev-parse --short HEAD)
GITHASHSTR = '\\"$${GITHASH}\\"'
DEFINES += GIT_REV=\"$${GITREVSTR}\"
DEFINES += GIT_HASH=\"$${GITHASHSTR}\"

CONFIG += qt resources warn_on
CONFIG -= console

QT += core gui network widgets multimedia websockets xml

#QMAKE_CXXFLAGS_DEBUG += -Werror

TEMPLATE = app
TARGET = flist-messenger

DEPENDPATH += . \
INCLUDEPATH += . \

# Input
HEADERS += \
    api/flist_socket.h \
           flist_account.h \
           flist_avatar.h \
           flist_channeltab.h \
           flist_character.h \
           flist_common.h \
           flist_global.h \
    flist_jsonhelper.h \
           flist_messenger.h \
           flist_parser.h \
           flist_session.h \
           flist_sound.h \
    flist_server.h \
    flist_characterprofile.h \
    flist_iuserinterface.h \
    flist_channelpanel.h \
    flist_channel.h \
    flist_channelsummary.h \
    flist_enums.h \
    flist_message.h \
    flist_logtextbrowser.h \
    flist_settings.h \
    flist_attentionsettingswidget.h \
    flist_loginwindow.h \
    usereturn.h \
    flist_logincontroller.h \
    flist_api.h \
    api/endpoint_v1.h \
	api/data.h \
    ui/helpdialog.h \
    ui/characterinfodialog.h \
    ui/channellistdialog.h \
    ui/aboutdialog.h \
    ui/makeroomdialog.h \
    ui/statusdialog.h \
    ui/friendsdialog.h \
    ui/addremovelistview.h \
    notifylist.h \
    ui/stringcharacterlistmodel.h
SOURCES += \
    api/flist_socket.cpp \
           flist_account.cpp \
           flist_avatar.cpp \
           flist_channeltab.cpp \
           flist_character.cpp \
           flist_global.cpp \
    flist_jsonhelper.cpp \
           flist_messenger.cpp \
           flist_parser.cpp \
           flist_session.cpp \
           flist_sound.cpp \
           main.cpp \
    flist_characterprofile.cpp \
    flist_server.cpp \
    flist_channelpanel.cpp \
    flist_channel.cpp \
    flist_message.cpp \
    flist_logtextbrowser.cpp \
	flist_loginwindow.cpp \
    usereturn.cpp \
    flist_logincontroller.cpp \
    api/endpoint_v1.cpp \
	api/apihelpers.cpp \
    flist_settings.cpp \
    flist_enums.cpp \
    flist_attentionsettingswidget.cpp \
    ui/helpdialog.cpp \
    ui/characterinfodialog.cpp \
    ui/channellistdialog.cpp \
    ui/aboutdialog.cpp \
    ui/makeroomdialog.cpp \
    ui/statusdialog.cpp \
    ui/friendsdialog.cpp \
    ui/addremovelistview.cpp \
    notifylist.cpp \
    ui/stringcharacterlistmodel.cpp
RESOURCES += resources.qrc
FORMS += \
    flist_loginwindow.ui \
    ui/channellistdialog.ui \
    ui/aboutdialog.ui \
    ui/makeroomdialog.ui \
    ui/statusdialog.ui \
    ui/friendsdialog.ui \
    ui/addremovelistview.ui

DISTFILES += \
    ../../_clang-format
