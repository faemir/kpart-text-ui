set (ktptextui_message_filter_tts_SRCS
     tts-filter.cpp
)

kde4_add_ui_files (ktptextui_message_filter_tts_SRCS
)

qt4_add_dbus_interfaces(ktptextui_message_filter_tts_SRCS ${KDE4_DBUS_INTERFACES_DIR}/org.kde.KSpeech.xml)

kde4_add_plugin (ktptextui_message_filter_tts
                 ${ktptextui_message_filter_tts_SRCS}
)

target_link_libraries (ktptextui_message_filter_tts
    ${QT_LIBRARIES}
    ${KDE4_KDEUI_LIBS}
    ${TELEPATHY_QT4_LIBRARIES}
    ${KTP_LIBRARIES}
)

# Install:
install (TARGETS ktptextui_message_filter_tts
         DESTINATION ${PLUGIN_INSTALL_DIR}
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ktptextui_message_filter_tts.desktop.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/ktptextui_message_filter_tts.desktop
               @ONLY)

install (FILES ${CMAKE_CURRENT_BINARY_DIR}/ktptextui_message_filter_tts.desktop
         DESTINATION ${SERVICES_INSTALL_DIR}
)
