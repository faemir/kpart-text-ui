set (ktptextui_message_filter_highlight_SRCS
     highlight-filter.cpp
)

kde4_add_plugin (ktptextui_message_filter_highlight
                 ${ktptextui_message_filter_highlight_SRCS}
)

target_link_libraries (ktptextui_message_filter_highlight
    ktpchat
    ${QT_LIBRARIES}
    ${KDE4_KDECORE_LIBS}
    ${TELEPATHY_QT4_LIBRARIES}
    ${KTP_LIBRARIES}
)

# Install:
install (TARGETS ktptextui_message_filter_highlight
         DESTINATION ${PLUGIN_INSTALL_DIR}
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ktptextui_message_filter_highlight.desktop.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/ktptextui_message_filter_highlight.desktop
               @ONLY)

install (FILES ${CMAKE_CURRENT_BINARY_DIR}/ktptextui_message_filter_highlight.desktop
         DESTINATION ${SERVICES_INSTALL_DIR}
)

