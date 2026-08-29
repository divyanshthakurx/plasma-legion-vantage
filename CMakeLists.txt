cmake_minimum_required(VERSION 3.16)

project(plasma-legion-vantage VERSION 1.0.0)

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

# Install Plasmoid UI Package
plasma_install_package(package org.kde.legionvantage)

# Build C++ Helper Subdirectory
add_subdirectory(helper)