cmake_minimum_required(VERSION 3.16)
project(plasma-legion-vantage VERSION 1.0.0)

# Import KDE Plasma 6 build tools
find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

# --- FIX: We must import Plasma to use the 'plasma_install_package' macro ---
find_package(Plasma REQUIRED)

# 1. Install the QML Frontend (the 'package' folder)
plasma_install_package(package org.kde.legionvantage)

# 2. Tell CMake to look inside the 'helper' folder for C++ code
add_subdirectory(helper)