find_package(Qt6 REQUIRED COMPONENTS Core DBus)

# Compile main.cpp and legionhelper.cpp into an executable
add_executable(legion-vantage-helper main.cpp legionhelper.cpp)

# Link the Qt6 DBus libraries
target_link_libraries(legion-vantage-helper Qt6::Core Qt6::DBus)

# FIX: Install the compiled helper to the KDE background service folder
install(TARGETS legion-vantage-helper DESTINATION ${KDE_INSTALL_LIBEXECDIR})

# FIX: Install the Polkit permission rule so your widget doesn't ask for a password
install(FILES org.kde.legionvantage.policy DESTINATION /usr/share/polkit-1/actions/)