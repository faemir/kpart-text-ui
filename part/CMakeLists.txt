INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib ${KDE4_INCLUDES} . )

set(textuipart_PART_SRCS textuipart.cpp)

kde4_add_plugin(textuipart ${textuipart_PART_SRCS})

target_link_libraries(textuipart ${KDE4_KPARTS_LIBS} ktpchat)

install(TARGETS textuipart  DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES textuipart.desktop  DESTINATION ${SERVICES_INSTALL_DIR})