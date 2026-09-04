cmake_minimum_required(VERSION 3.19)

find_package(Qt6 REQUIRED COMPONENTS Core Qml)
find_package(Plasma REQUIRED)
qt_standard_project_setup(REQUIRES 6.5)

# QML module exposing LegionBackend to Plasma 6.
# Sources are listed directly so qmltyperegistrations can see the C++ types.
qt_add_qml_module(legionvantage
    URI org.kde.legionvantage
    VERSION 1.0
    QML_FILES
        qml/Placeholder.qml
    SOURCES
        src/legionbackend.h
        src/legionbackend.cpp
)

target_include_directories(legionvantage PRIVATE src)

# Install the QML module plugin alongside the applet package
install(TARGETS legionvantageplugin
    LIBRARY DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/legionvantage
    RUNTIME DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/legionvantage
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qmldir
    DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/legionvantage
)
