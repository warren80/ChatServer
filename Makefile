#############################################################################
# Makefile for building: ChatServer
# Generated by qmake (2.01a) (Qt 4.6.3) on: Thu Mar 10 08:00:38 2011
# Project:  ChatServer.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/lib64/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile ChatServer.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/lib64/qt4/mkspecs/linux-g++ -I. -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)   -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = 
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		textClient.cpp \
		textServer.cpp \
		socket.cpp \
		settings.cpp \
		thread.cpp \
		component.cpp moc_mainwindow.cpp \
		moc_textClient.cpp \
		moc_textServer.cpp \
		moc_socket.cpp \
		moc_settings.cpp \
		moc_component.cpp
OBJECTS       = main.o \
		mainwindow.o \
		textClient.o \
		textServer.o \
		socket.o \
		settings.o \
		thread.o \
		component.o \
		moc_mainwindow.o \
		moc_textClient.o \
		moc_textServer.o \
		moc_socket.o \
		moc_settings.o \
		moc_component.o
DIST          = /usr/lib64/qt4/mkspecs/common/g++-multilib.conf \
		/usr/lib64/qt4/mkspecs/common/unix.conf \
		/usr/lib64/qt4/mkspecs/common/linux.conf \
		/usr/lib64/qt4/mkspecs/qconfig.pri \
		/usr/lib64/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib64/qt4/mkspecs/features/qt_config.prf \
		/usr/lib64/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib64/qt4/mkspecs/features/default_pre.prf \
		/usr/lib64/qt4/mkspecs/features/debug.prf \
		/usr/lib64/qt4/mkspecs/features/default_post.prf \
		/usr/lib64/qt4/mkspecs/features/warn_on.prf \
		/usr/lib64/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/lib64/qt4/mkspecs/features/qt.prf \
		/usr/lib64/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib64/qt4/mkspecs/features/moc.prf \
		/usr/lib64/qt4/mkspecs/features/resources.prf \
		/usr/lib64/qt4/mkspecs/features/uic.prf \
		/usr/lib64/qt4/mkspecs/features/yacc.prf \
		/usr/lib64/qt4/mkspecs/features/lex.prf \
		/usr/lib64/qt4/mkspecs/features/include_source_dir.prf \
		ChatServer.pro
QMAKE_TARGET  = ChatServer
DESTDIR       = 
TARGET        = ChatServer

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_settings.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ChatServer.pro  /usr/lib64/qt4/mkspecs/linux-g++/qmake.conf /usr/lib64/qt4/mkspecs/common/g++-multilib.conf \
		/usr/lib64/qt4/mkspecs/common/unix.conf \
		/usr/lib64/qt4/mkspecs/common/linux.conf \
		/usr/lib64/qt4/mkspecs/qconfig.pri \
		/usr/lib64/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib64/qt4/mkspecs/features/qt_config.prf \
		/usr/lib64/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib64/qt4/mkspecs/features/default_pre.prf \
		/usr/lib64/qt4/mkspecs/features/debug.prf \
		/usr/lib64/qt4/mkspecs/features/default_post.prf \
		/usr/lib64/qt4/mkspecs/features/warn_on.prf \
		/usr/lib64/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/lib64/qt4/mkspecs/features/qt.prf \
		/usr/lib64/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib64/qt4/mkspecs/features/moc.prf \
		/usr/lib64/qt4/mkspecs/features/resources.prf \
		/usr/lib64/qt4/mkspecs/features/uic.prf \
		/usr/lib64/qt4/mkspecs/features/yacc.prf \
		/usr/lib64/qt4/mkspecs/features/lex.prf \
		/usr/lib64/qt4/mkspecs/features/include_source_dir.prf
	$(QMAKE) -spec /usr/lib64/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile ChatServer.pro
/usr/lib64/qt4/mkspecs/common/g++-multilib.conf:
/usr/lib64/qt4/mkspecs/common/unix.conf:
/usr/lib64/qt4/mkspecs/common/linux.conf:
/usr/lib64/qt4/mkspecs/qconfig.pri:
/usr/lib64/qt4/mkspecs/features/qt_functions.prf:
/usr/lib64/qt4/mkspecs/features/qt_config.prf:
/usr/lib64/qt4/mkspecs/features/exclusive_builds.prf:
/usr/lib64/qt4/mkspecs/features/default_pre.prf:
/usr/lib64/qt4/mkspecs/features/debug.prf:
/usr/lib64/qt4/mkspecs/features/default_post.prf:
/usr/lib64/qt4/mkspecs/features/warn_on.prf:
/usr/lib64/qt4/mkspecs/modules/qt_phonon.pri:
/usr/lib64/qt4/mkspecs/features/qt.prf:
/usr/lib64/qt4/mkspecs/features/unix/thread.prf:
/usr/lib64/qt4/mkspecs/features/moc.prf:
/usr/lib64/qt4/mkspecs/features/resources.prf:
/usr/lib64/qt4/mkspecs/features/uic.prf:
/usr/lib64/qt4/mkspecs/features/yacc.prf:
/usr/lib64/qt4/mkspecs/features/lex.prf:
/usr/lib64/qt4/mkspecs/features/include_source_dir.prf:
qmake:  FORCE
	@$(QMAKE) -spec /usr/lib64/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile ChatServer.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/ChatServer1.0.0 || $(MKDIR) .tmp/ChatServer1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/ChatServer1.0.0/ && $(COPY_FILE) --parents mainwindow.h textClient.h textServer.h socket.h settings.h thread.h component.h .tmp/ChatServer1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp textClient.cpp textServer.cpp socket.cpp settings.cpp thread.cpp component.cpp .tmp/ChatServer1.0.0/ && $(COPY_FILE) --parents mainwindow.ui settings.ui .tmp/ChatServer1.0.0/ && (cd `dirname .tmp/ChatServer1.0.0` && $(TAR) ChatServer1.0.0.tar ChatServer1.0.0 && $(COMPRESS) ChatServer1.0.0.tar) && $(MOVE) `dirname .tmp/ChatServer1.0.0`/ChatServer1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/ChatServer1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_textClient.cpp moc_textServer.cpp moc_socket.cpp moc_settings.cpp moc_component.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_textClient.cpp moc_textServer.cpp moc_socket.cpp moc_settings.cpp moc_component.cpp
moc_mainwindow.cpp: textClient.h \
		socket.h \
		component.h \
		textServer.h \
		settings.h \
		thread.h \
		mainwindow.h
	/usr/lib64/qt4/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_textClient.cpp: socket.h \
		component.h \
		textClient.h
	/usr/lib64/qt4/bin/moc $(DEFINES) $(INCPATH) textClient.h -o moc_textClient.cpp

moc_textServer.cpp: socket.h \
		component.h \
		textServer.h
	/usr/lib64/qt4/bin/moc $(DEFINES) $(INCPATH) textServer.h -o moc_textServer.cpp

moc_socket.cpp: socket.h
	/usr/lib64/qt4/bin/moc $(DEFINES) $(INCPATH) socket.h -o moc_socket.cpp

moc_settings.cpp: settings.h
	/usr/lib64/qt4/bin/moc $(DEFINES) $(INCPATH) settings.h -o moc_settings.cpp

moc_component.cpp: component.h
	/usr/lib64/qt4/bin/moc $(DEFINES) $(INCPATH) component.h -o moc_component.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_settings.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_settings.h
ui_mainwindow.h: mainwindow.ui
	/usr/lib64/qt4/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_settings.h: settings.ui
	/usr/lib64/qt4/bin/uic settings.ui -o ui_settings.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		textClient.h \
		socket.h \
		component.h \
		textServer.h \
		settings.h \
		thread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		textClient.h \
		socket.h \
		component.h \
		textServer.h \
		settings.h \
		thread.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

textClient.o: textClient.cpp textClient.h \
		socket.h \
		component.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o textClient.o textClient.cpp

textServer.o: textServer.cpp textServer.h \
		socket.h \
		component.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o textServer.o textServer.cpp

socket.o: socket.cpp socket.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o socket.o socket.cpp

settings.o: settings.cpp settings.h \
		ui_settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o settings.o settings.cpp

thread.o: thread.cpp thread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o thread.o thread.cpp

component.o: component.cpp component.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o component.o component.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_textClient.o: moc_textClient.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_textClient.o moc_textClient.cpp

moc_textServer.o: moc_textServer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_textServer.o moc_textServer.cpp

moc_socket.o: moc_socket.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_socket.o moc_socket.cpp

moc_settings.o: moc_settings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_settings.o moc_settings.cpp

moc_component.o: moc_component.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_component.o moc_component.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

