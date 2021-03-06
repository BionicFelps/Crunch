######################################################################
# Automatically generated by qmake (3.0) Mon Feb 22 00:58:51 2016
######################################################################

TEMPLATE = app
TARGET = Crunch
INCLUDEPATH += . \
               src \
               AngelScriptAddons/scriptstdstring \
               AngelScriptAddons/scriptbuilder \
               AngelScriptAddons/scriptarray \
               AngelScriptAddons/contextmgr \
               AngelScriptAddons/debugger \
               AngelScriptAddons/scriptany \
               AngelScriptAddons/scriptdictionary \
               AngelScriptAddons/scriptfile \
               AngelScriptAddons/scriptgrid \
               AngelScriptAddons/scripthandle \
               AngelScriptAddons/scripthelper \
               AngelScriptAddons/scriptmath \
               AngelScriptAddons/serializer \
               AngelScriptAddons/weakref

# Input
HEADERS += src/ASManager.hpp \
           src/CrunchyBoxDraw.hpp \
           src/Filesystem.h \
           src/GlobalIndexManager.hpp \
           src/IndexManager.hpp \
           src/indexType.hpp \
           src/Layer.hpp \
           src/LayerManager.hpp \
           src/Sprite.hpp \
           src/VectIndexMap.hpp \
           src/virtualIndexType.hpp \
           AngelScriptAddons/contextmgr/contextmgr.h \
           AngelScriptAddons/debugger/debugger.h \
           AngelScriptAddons/scriptany/scriptany.h \
           AngelScriptAddons/scriptarray/scriptarray.h \
           AngelScriptAddons/scriptbuilder/scriptbuilder.h \
           AngelScriptAddons/scriptdictionary/scriptdictionary.h \
           AngelScriptAddons/scriptfile/scriptfile.h \
           AngelScriptAddons/scriptfile/scriptfilesystem.h \
           AngelScriptAddons/scriptgrid/scriptgrid.h \
           AngelScriptAddons/scripthandle/scripthandle.h \
           AngelScriptAddons/scripthelper/scripthelper.h \
           AngelScriptAddons/scriptmath/scriptmath.h \
           AngelScriptAddons/scriptmath/scriptmathcomplex.h \
           AngelScriptAddons/scriptstdstring/scriptstdstring.h \
           AngelScriptAddons/serializer/serializer.h \
           AngelScriptAddons/weakref/weakref.h \
    src/DrawManager.hpp \
    src/AudioInterface.hpp \
    src/AudioSystem.hpp \
    src/AudioAsset.hpp \
    src/MusicManager.hpp \
    src/SoundManager.hpp \
    src/AudioController.hpp
SOURCES += src/ASManager.cpp \
           src/CrunchyBoxDraw.cpp \
           src/Filesystem.cpp \
           src/GlobalIndexManager.cpp \
           src/Layer.cpp \
           src/LayerManager.cpp \
           src/main.cpp \
           src/Sprite.cpp \
           AngelScriptAddons/contextmgr/contextmgr.cpp \
           AngelScriptAddons/debugger/debugger.cpp \
           AngelScriptAddons/scriptany/scriptany.cpp \
           AngelScriptAddons/scriptarray/scriptarray.cpp \
           AngelScriptAddons/scriptbuilder/scriptbuilder.cpp \
           AngelScriptAddons/scriptdictionary/scriptdictionary.cpp \
           AngelScriptAddons/scriptfile/scriptfile.cpp \
           AngelScriptAddons/scriptfile/scriptfilesystem.cpp \
           AngelScriptAddons/scriptgrid/scriptgrid.cpp \
           AngelScriptAddons/scripthandle/scripthandle.cpp \
           AngelScriptAddons/scripthelper/scripthelper.cpp \
           AngelScriptAddons/scriptmath/scriptmath.cpp \
           AngelScriptAddons/scriptmath/scriptmathcomplex.cpp \
           AngelScriptAddons/scriptstdstring/scriptstdstring.cpp \
           AngelScriptAddons/scriptstdstring/scriptstdstring_utils.cpp \
           AngelScriptAddons/serializer/serializer.cpp \
           AngelScriptAddons/weakref/weakref.cpp \
    src/DrawManager.cpp \
    src/AudioSystem.cpp \
    src/AudioAsset.cpp \
    src/MusicManager.cpp \
    src/SoundManager.cpp \
    src/AudioController.cpp

CONFIG += C++11

unix|win32: LIBS += -langelscript
unix|win32: LIBS += -lsfml-graphics
unix|win32: LIBS += -lsfml-window
unix|win32: LIBS += -lsfml-system
unix|win32: LIBS += -lsfml-audio
unix|win32: LIBS += -lBox2D
unix|win32: LIBS += -lpthread
