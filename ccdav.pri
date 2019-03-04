VERSION = $$cat($$PWD/VERSION)

!android: TEMPLATE = lib

QT += \
  core \ 
  xml \
  network \
  testlib

CONFIG += c++11

HEADERS += \
  $$PWD/lib/CardDAV.hpp \
  $$PWD/lib/CalDAV.hpp \
  $$PWD/lib/dto/Contact.hpp \
  $$PWD/lib/dto/CardDAVResponseItem.hpp \
  # $$PWD/lib/dto/CalDAVItem.hpp \
  $$PWD/lib/utils/NetworkHelper.hpp \
  $$PWD/lib/utils/CardDAVReply.hpp \
  $$PWD/lib/utils/XMLHelper.hpp \
  $$PWD/lib/utils/Environment.hpp

SOURCES += \
  $$PWD/lib/CardDAV.cpp \
  $$PWD/lib/CalDAV.cpp \
  $$PWD/lib/dto/Contact.cpp \
  $$PWD/lib/dto/CardDAVResponseItem.cpp \
  # $$PWD/lib/dto/CalDAVItem.cpp \
  $$PWD/lib/utils/NetworkHelper.cpp \
  $$PWD/lib/utils/CardDAVReply.cpp \
  $$PWD/lib/utils/XMLHelper.cpp \
  $$PWD/lib/utils/Environment.cpp
  
INCLUDEPATH += \
  $$PWD/lib \
  $$PWD/lib/utils \
  $$PWD/lib/dto

DEFINES += \
  LIBCCDAV
