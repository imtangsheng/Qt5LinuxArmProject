# CMakeList.txt: CodeTest 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.12)
set (TARGET_NAME "CodeTest") 
# 如果支持，请为 MSVC 编译器启用热重载。

# 定义此项目的名称。如果是顶级项目，则此名称将用于项目生成的文件夹。
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  project (${TARGET_NAME} VERSION 2.0.0 LANGUAGES CXX)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建版本头文件
# 对于 MSVC 编译器
if(MSVC)
    # MSVC 版本号对应关系：
    # 1910-1919 = VS 2017 (15.0-15.9)
    # 1920-1929 = VS 2019 (16.0-16.11)
    # 1930+     = VS 2022 (17.0+)
    message(STATUS "MSVC 版本: ${MSVC_VERSION}")
    # 如果支持，请为 MSVC 编译器启用热重载。
    if (POLICY CMP0141)
        message("PROJECT_NAME: ${PROJECT_NAME}")
      cmake_policy(SET CMP0141 NEW)
      set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
      message("MSVC 编译器启用热重载")
    endif()
    message("MSVC 启动utf-8编码")
    add_compile_options(/utf-8)
endif()
# 设置源文件编码
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Qt5 COMPONENTS Core Widgets Xml Network WebSockets REQUIRED)

# 检测 Qt 版本
message(STATUS "=====================================")
message(STATUS "Qt5 版本信息:")
message(STATUS "Qt5Core_VERSION: ${Qt5Core_VERSION}")
message(STATUS "=====================================")
# 检查是否是特定版本
if(${Qt5Core_VERSION} VERSION_GREATER_EQUAL "5.15.0")
    message(STATUS "Qt 版本 >= 5.15.0")
    # 5.15+ 特有的功能
    add_definitions(-DQT_VERSION_5_15)
elseif(${Qt5Core_VERSION} VERSION_GREATER_EQUAL "5.9.0")
    message(STATUS "Qt 版本 >= 5.9.0")
    add_definitions(-DQT_NO_KEYWORDS)
    add_definitions(-DQT_VERSION_5_9)
endif()

# 将源代码添加到此项目的可执行文件。
set(HEADERS
  )
set(SOURCES
    ui/mainwindow.cpp
    ui/mainwindow.h
    ui/mainwindow.ui
    src/main.cpp
)
# 配置版本文件
configure_file(
    src/version.h.in
    ${CMAKE_BINARY_DIR}/version.h
)

add_executable (${TARGET_NAME}
    ${SOURCES}
    ${HEADERS}
)


target_link_libraries(${TARGET_NAME} 
  Qt5::Core
  Qt5::Widgets
  Qt5::Xml
  Qt5::Network
  Qt5::WebSockets
)
