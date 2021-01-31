cmake_minimum_required(VERSION 3.16.3)

project(QtPie)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  )


# add extra compile flags for clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CLANG_EXTRA_CXX_FLAGS "-Weverything -Wno-covered-switch-default -Wno-padded -Wno-documentation -Wno-system-headers -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-global-constructors -Wno-exit-time-destructors -Weffc++")
endif()


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/apps")