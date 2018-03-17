TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.c \
    map.c \
    command_line_utils.c \
    doc_utils.c \
    posting_list.c \
    retrie.c \
    cli.c \
    score_calculator.c

DISTFILES += \
    docfile \
    documents.txt \
    docfile1.txt

HEADERS += \
    command_line_utils.h \
    doc_utils.h \
    map.h \
    posting_list.h \
    retrie.h \
    cli.h \
    score_calculator.h

