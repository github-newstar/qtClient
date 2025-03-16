cmake_minimum_required(VERSION 3.5)

project(chatPro LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED Network)
file(GLOB CPP_SRC "./*.cpp")
file(GLOB H_SRC "./*.h")
file(GLOB UI_SRC "./*.ui")

  add_executable(chatPro
      ${CPP_SRC}
      ${H_SRC}
      ${CHARPRO_UIS}
      ${UI_SRC}  )

target_link_libraries(chatPro PRIVATE Qt5::Widgets Qt5::Network)
# set(TargetConfig "${CMAKE_SOURCE_DIR}/config.ii")
# # 指定目标配置文件
# # 将路径中的 / 转换为 Windows 风格的 \\
# #string(REPLACE "/" "\\" TargetConfig ${TargetConfig})

# # 设置输出目录
# set(OutputDir "${CMAKE_BINARY_DIR}")

# if(NOT UNIX)
#     # 将路径中的 / 转换为 Windows 风格的 \\
#     string(REPLACE "/" "\\" TargetConfig ${TargetConfig})
#     string(REPLACE "/" "\\" OutputDir ${OutputDir})

#     add_custom_command(TARGET chatPro POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         "${TargetConfig}" "${OutputDir}"
#     )
# endif()

if(NOT UNIX)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.ii DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/style DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/static DESTINATION ${CMAKE_BINARY_DIR})
endif()
