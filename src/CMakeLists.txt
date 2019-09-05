include(GNUInstallDirs)
set(GOTCHA_SOURCES
  gotcha_utils.c 
  gotcha.c 
  gotcha_auxv.c 
  libc_wrappers.c 
  elf_ops.c 
  hash.c 
  tool.c 
  library_filters.c
  gotcha_dl.c
  translations.c
)

set(CMAKE_C_EXTENSIONS ON)

file(GLOB INTERNAL_HEADERS ${CMAKE_CURRENT_LIST_DIR}/*.h)
add_library(Gotcha SHARED ${GOTCHA_SOURCES} ${GOTCHA_HEADERS} ${INTERNAL_HEADERS})
set_target_properties(Gotcha PROPERTIES OUTPUT_NAME gotcha)

set_target_properties(Gotcha PROPERTIES SOVERSION ${LIBTOOL_INTERFACE})
set_target_properties(Gotcha PROPERTIES VERSION "${LIBTOOL_INTERFACE}.${LIBTOOL_REVISION}.${LIBTOOL_AGE}")
set_target_properties(Gotcha PROPERTIES COMPILE_FLAGS "-fvisibility=${DEFAULT_SYMBOL_VISIBILITY}")
set_target_properties(Gotcha PROPERTIES LINK_FLAGS "-fvisibility=${DEFAULT_SYMBOL_VISIBILITY}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Gotcha PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)

install(TARGETS Gotcha EXPORT gotcha-targets DESTINATION ${CMAKE_INSTALL_LIBDIR}) 
install(EXPORT gotcha-targets DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake/gotcha)

if(BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
