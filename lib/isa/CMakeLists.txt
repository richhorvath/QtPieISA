# set variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_EXTRA_CXX_FLAGS} -Wall -Wextra -Wpedantic -fmessage-length=0 -m64 -std=c++14-fPIC")
set(APP_QT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE STRING "Isa Qt Include Directory")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTORCC_OPTIONS "-root ${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(CMAKE_AUTOUIC ON)

# find packages
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# get source, headers, resources
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/rfdu/qt/*.hpp")
file(GLOB RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.qrc")
file(GLOB_RECURSE FORMS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui")

# add target
add_library(IsaQt STATIC ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})

# linker
target_link_libraries(IsaQt
  Qt5::Core
  Qt5::Widgets
  )

# includes
target_include_directories(IsaQt SYSTEM PUBLIC
  ${Qt5Core_INCLUDE_DIRS}
  )

target_include_directories(IsaQt PUBLIC
  ${APP_QT_INCLUDE_DIR}
  ${APP_INCLUDE_DIR}
  )

# definitions
target_compile_definitions(IsaQt PRIVATE
  ${QT_DEFINITIONS}
  )