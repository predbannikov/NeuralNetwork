QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


CONFIG += console
CONFIG += c+11





unix: !macx {
    LIBS += -lX11   -lopencv_core
    QMAKE_CXXFLAGS_DEBUG += -O0
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    -lopencv_imgproc
    -lopencv_highgui
    -lopencv_ml
    -lopencv_video
    -lopencv_features2d
    -lopencv_calib3d
    -lopencv_objdetect
    -lopencv_contrib
    -lopencv_legacy
    -lopencv_flann
}


win32-msvc* {

    VERSION_BUILD = 320
    PATH_VERSION = uild2017-64      # 64 version path
#    PATH_VERSION = opencv-build      # 32 version path

    CONFIG += no_keywords

    INCLUDEPATH += "C:\Users\user\AppData\Local\Programs\Python\Python38\include"
    INCLUDEPATH += "C:\Users\user\AppData\Local\Programs\Python\Python38\Lib\site-packages\numpy\core\include"
    LIBS += "C:\Users\user\AppData\Local\Programs\Python\Python38\libs\python38.lib"
    LIBS += "C:\Users\user\AppData\Local\Programs\Python\Python38\libs\python38_d.lib"


    INCLUDEPATH += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\include"

    CONFIG(debug, debug|release) {

            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_core$${VERSION_BUILD}d.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_highgui$${VERSION_BUILD}d.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_imgcodecs$${VERSION_BUILD}d.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_imgproc$${VERSION_BUILD}d.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_features2d$${VERSION_BUILD}d.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_calib3d$${VERSION_BUILD}d.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_videoio$${VERSION_BUILD}d.lib"
    }
    CONFIG(release, debug|release) {

            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_core$${VERSION_BUILD}.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_highgui$${VERSION_BUILD}.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_imgcodecs$${VERSION_BUILD}.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_imgproc$${VERSION_BUILD}.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_features2d$${VERSION_BUILD}.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_calib3d$${VERSION_BUILD}.lib"
            LIBS += "F:\projects\opencv\opencv\b$${PATH_VERSION}\install\lib\opencv_videoio$${VERSION_BUILD}.lib"
    }

}





SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
