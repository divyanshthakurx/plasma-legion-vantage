cmake_minimum_required(VERSION 3.16)
project(plasma-legion-vantage VERSION 1.0.0)

# Import KDE Plasma 6 build tools
find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

# Required for the plasma_install_package() macro
find_package(Plasma REQUIRED)

# Install the Plasma 6 applet (QML-only; sysfs access via udev-granted permissions)
plasma_install_package(package org.kde.legionvantage)
