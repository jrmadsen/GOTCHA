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

set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_C_VISIBILITY_PRESET "${DEFAULT_SYMBOL_VISIBILITY}")

add_library(gotcha SHARED ${GOTCHA_SOURCES})

set_target_properties(gotcha PROPERTIES SOVERSION ${LIBTOOL_INTERFACE})
set_target_properties(gotcha PROPERTIES VERSION "${LIBTOOL_INTERFACE}.${LIBTOOL_REVISION}.${LIBTOOL_AGE}")
target_compile_definitions(gotcha PRIVATE GOTCHA_DLOPEN_DLSYM=$<BOOL:${GOTCHA_DLOPEN_DLSYM}>)
target_include_directories(gotcha PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
if(GOTCHA_ENABLE_TESTS)
    add_library(gotcha_no_libc SHARED ${GOTCHA_SOURCES})
    set_target_properties(gotcha_no_libc PROPERTIES SOVERSION ${LIBTOOL_INTERFACE})
    set_target_properties(gotcha_no_libc PROPERTIES VERSION "${LIBTOOL_INTERFACE}.${LIBTOOL_REVISION}.${LIBTOOL_AGE}")
    target_compile_definitions(gotcha_no_libc PRIVATE FORCE_NO_LIBC=1)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS gotcha EXPORT gotcha-targets DESTINATION ${CMAKE_INSTALL_LIBDIR})
if(GOTCHA_INSTALL_CONFIG)
    install(EXPORT gotcha-targets DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/gotcha)
endif()

if(GOTCHA_ENABLE_EXAMPLES)
  add_subdirectory(example)
endif()
