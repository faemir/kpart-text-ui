include_directories(${CMAKE_SOURCE_DIR}/lib)

set(ktp-log-viewer_SRCS
        main.cpp
        log-viewer.cpp
        logs-import-dialog.cpp
        entity-model.cpp
        entity-model-item.cpp
        message-view.cpp
        entity-view.cpp
        entity-proxy-model.cpp
        conversation-date-picker.cpp
)

kde4_add_ui_files(ktp-log-viewer_SRCS log-viewer.ui)

kde4_add_executable(ktp-log-viewer ${ktp-log-viewer_SRCS})

target_link_libraries(ktp-log-viewer
            ${KDE4_KDECORE_LIBS}
            ${KDE4_KDEUI_LIBS}
            ${KDE4_KIO_LIBS}
            ${TELEPATHY_QT4_LIBRARIES}
            ${KDE4_KEMOTICONS_LIBS}
            ${KDE4_KCMUTILS_LIBS}
            ${KDE4_KDEWEBKIT_LIBRARY}
            ${KTP_LIBRARIES}
            ${KTP_LOGGER_LIBRARIES}
            ktpchat)

install(TARGETS ktp-log-viewer DESTINATION ${BIN_INSTALL_DIR})
install(FILES ktp-log-viewer.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES log-viewer.rc DESTINATION  ${DATA_INSTALL_DIR}/ktp-log-viewer/)
