find_package(Qt6 REQUIRED COMPONENTS Core DBus)

add_executable(legion-vantage-helper 
    main.cpp 
    legionhelper.cpp
)

target_link_libraries(legion-vantage-helper Qt6::Core Qt6::DBus)

# Install the binary and policy
install(TARGETS legion-vantage-helper DESTINATION ${KDE_INSTALL_TARGETSDIR})
install(FILES org.kde.legionvantage.policy DESTINATION /usr/share/polkit-1/actions/)