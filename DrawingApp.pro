QT += core gui widgets

TARGET = DrawingApp
TEMPLATE = app

FORMS += \
    mainwindow.ui

HEADERS += \
    drawingcanvas.h \
    mainwindow.h

SOURCES += \
    drawingcanvas.cpp \
    main.cpp \
    mainwindow.cpp

# # Include paths for Tesseract
# INCLUDEPATH += "C:/Program Files/Tesseract-OCR/include" \
#                "C:/Program Files/Tesseract-OCR/include/tesseract"

# # Link Tesseract library
# LIBS += -L"C:/Program Files/Tesseract-OCR" -ltesseract
