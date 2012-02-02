
QT       += core xml sql network

#CONFIG += console

SOURCES += \
    main.cpp \
    hellosarkar.cpp \
    history.cpp

HEADERS += \
    hellosarkar.h \
    history.h

RESOURCES += \
    xmlData.qrc

unix:!symbian {
    maemo5 {
        icon.files = hellosarkar.png
        icon.path = /usr/share/icons/hicolor/64x64/apps
        desktopfile.files = hellosarkar.desktop
        desktopfile.path = /usr/share/applications/hildon
        dbfile.files = HelloSarkar.db
        dbfile.path = /home/user/.hellosarkar
        target.path = /opt/usr/bin
    } else {
        target.path = /usr/local/bin
    }
    INSTALLS += target desktopfile icon dbfile
}
 symbian {
    TARGET.UID3 = 0xE4DE5D11
    DEPLOYMENT.installer_header=0xA000D7CE

    vendorinfo = \
    "%{\"MobileNepal-EN\"}" \
    ":\"KrishnaShrestha\""

    my_deployment.pkg_prerules = vendorinfo
    DEPLOYMENT += my_deployment
}

OTHER_FILES += \
    hellosarkar.desktop \
    HelloSarkar.db \
    hellosarkar.png \
    Readme.txt


