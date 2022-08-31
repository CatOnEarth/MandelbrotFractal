QT += widgets

HEADERS       = mandelbrotwidget.h \
                Complex.h \
                dialoginformation.h \
                notifymessagebox.h \
                renderthread.h \
                rubberband.h \
                typesavescale.h
SOURCES       = main.cpp \
                Complex.cpp \
                dialoginformation.cpp \
                mandelbrotwidget.cpp \
                notifymessagebox.cpp \
                renderthread.cpp \
                rubberband.cpp \
                typesavescale.cpp

unix:!mac:!vxworks:!integrity:!haiku:LIBS += -lm

# install
target.path = $$[QT_INSTALL_EXAMPLES]/corelib/threads/mandelbrot
INSTALLS += target

FORMS += \
    dialoginformation.ui
