######################################################################
# Automatically generated by qmake (2.01a) ?? ?? 23 19:27:34 2014
######################################################################

TEMPLATE = lib
TARGET = TaskLoop
CONFIG(x64){
TARGET = $$TARGET"64"
}
!LIB_ALL:!COM_LIB{
	RC_FILE += TaskLoop.rc
	CONFIG += dll
}
else{
	CONFIG += staticlib
}


DEPENDPATH += .
INCLUDEPATH += . \
			   ../../utilities/include \
			   ../../soui/include \

dir = ../..
include($$dir/common.pri)

CONFIG(debug,debug|release){
	LIBS += utilitiesd.lib
}
else{
	LIBS += utilities.lib
}

# Input
HEADERS += TaskLoop.h thread.h
SOURCES += TaskLoop.cpp  thread.cpp