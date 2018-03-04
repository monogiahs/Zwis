TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.c \
    map.c \
    command_line_utils.c \
    doc_utils.c

DISTFILES += \
    docfile \
    documents.txt \
    docfile1.txt

HEADERS += \
    command_line_utils.h \
    doc_utils.h \
    map.h

