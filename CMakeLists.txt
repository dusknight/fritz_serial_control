cmake_minimum_required(VERSION 2.8)
project(fritz_control)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(include)

if(APPLE)
    include(Packages/FindIOKit.cmake)
    include(Packages/FindFoundation.cmake)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(FOUNDATION_LIBRARY Foundation)
    INCLUDE_DIRECTORIES(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Foundation.framework)
    INCLUDE_DIRECTORIES(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Foundation.framework/Versions/A/Headers)
    INCLUDE_DIRECTORIES(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/IOKit.framework)
    INCLUDE_DIRECTORIES(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/IOKit.framework/Headers)

elseif(UNIX)
    # If Linux, add rt and pthread
    catkin_package(
            LIBRARIES ${PROJECT_NAME}
            INCLUDE_DIRS include
            DEPENDS rt pthread
    )
else()
    # Otherwise normal call
    catkin_package(
            LIBRARIES ${PROJECT_NAME}
            INCLUDE_DIRS include
    )
endif()

## Sources
set(serial_SRCS
        src/serial/serial.cc
        include/serial/serial.h
        include/serial/v8stdint.h
        )
if(APPLE)
    # If OSX
    list(APPEND serial_SRCS src/serial/impl/unix.cc)
    list(APPEND serial_SRCS src/serial/impl/list_ports/list_ports_osx.cc)
elseif(UNIX)
    # If unix
    list(APPEND serial_SRCS src/serial/impl/unix.cc)
    list(APPEND serial_SRCS src/serial/impl/list_ports/list_ports_linux.cc)
else()
    # If windows
    list(APPEND serial_SRCS src/serial/impl/win.cc)
    list(APPEND serial_SRCS src/serial/impl/list_ports/list_ports_win.cc)
endif()

### Add serial library
#add_library(${PROJECT_NAME} ${serial_SRCS})


set(SOURCE_FILES src/main.cpp src/serial.cpp src/Serial.cpp src/Serial.h)
set(ALL_SOURCE_FILES ${SOURCE_FILES} ${serial_SRCS})
add_executable(fritz_control ${ALL_SOURCE_FILES})

if(APPLE)
    target_link_libraries(fritz_control ${FOUNDATION_LIBRARY} ${IOKIT_LIBRARY})
elseif(UNIX)
    target_link_libraries(fritz_control rt pthread)
else()
    target_link_libraries(fritz_control setupapi)
endif()