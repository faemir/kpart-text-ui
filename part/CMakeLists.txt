project(textui)
find_package (KDE4 REQUIRED)
INCLUDE_DIRECTORIES( ${KDE4_INCLUDES} . )

# ok, now this looks better. Save the file and try to build it (use "Save a local copy")
# yay it worked

set(textui_shared_SRCS
        textuipart.cpp
 )


set(textuipart_PART_SRCS textuipart.cpp)

kde4_add_plugin(textuipart ${textuipart_PART_SRCS})

target_link_libraries(textuipart ${KDE4_KPARTS_LIBS})

install(TARGETS textuipart  DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES textuipart.desktop  DESTINATION ${SERVICES_INSTALL_DIR})