# UNCLASSIFIED//FOR OFFICIAL USE ONLY

# set variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_EXTRA_CXX_FLAGS} -Wall -Wextra -Wpedantic -fmessage-length=0 -m64 -std=c++14 -fPIC")

# packages
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# add target
add_executable(QtPie main.cpp)

# linker
target_link_libraries(QtPie
  IsaQt
  Qt5::Widgets
  )

# include
target_include_directories(QtPie SYSTEM PUBLIC
  ${Qt5Core_INCLUDE_DIRS}
  )

# definitions
target_compile_definitions(QtPie PRIVATE
  ${QT_DEFINITIONS}
  )