# Install script for directory: /home/guest/Downloads/PopLib/external/ogg

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/guest/Downloads/PopLib/build/external/ogg/libogg.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ogg" TYPE FILE FILES
    "/home/guest/Downloads/PopLib/build/external/ogg/include/ogg/config_types.h"
    "/home/guest/Downloads/PopLib/external/ogg/include/ogg/ogg.h"
    "/home/guest/Downloads/PopLib/external/ogg/include/ogg/os_types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Ogg/OggTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Ogg/OggTargets.cmake"
         "/home/guest/Downloads/PopLib/build/external/ogg/CMakeFiles/Export/dee6fd410a50d06b294b496f57355584/OggTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Ogg/OggTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Ogg/OggTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Ogg" TYPE FILE FILES "/home/guest/Downloads/PopLib/build/external/ogg/CMakeFiles/Export/dee6fd410a50d06b294b496f57355584/OggTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Ogg" TYPE FILE FILES "/home/guest/Downloads/PopLib/build/external/ogg/CMakeFiles/Export/dee6fd410a50d06b294b496f57355584/OggTargets-relwithdebinfo.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Ogg" TYPE FILE FILES
    "/home/guest/Downloads/PopLib/build/external/ogg/OggConfig.cmake"
    "/home/guest/Downloads/PopLib/build/external/ogg/OggConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/guest/Downloads/PopLib/build/external/ogg/ogg.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/ogg/html" TYPE FILE FILES
    "/home/guest/Downloads/PopLib/external/ogg/doc/framing.html"
    "/home/guest/Downloads/PopLib/external/ogg/doc/index.html"
    "/home/guest/Downloads/PopLib/external/ogg/doc/oggstream.html"
    "/home/guest/Downloads/PopLib/external/ogg/doc/ogg-multiplex.html"
    "/home/guest/Downloads/PopLib/external/ogg/doc/fish_xiph_org.png"
    "/home/guest/Downloads/PopLib/external/ogg/doc/multiplex1.png"
    "/home/guest/Downloads/PopLib/external/ogg/doc/packets.png"
    "/home/guest/Downloads/PopLib/external/ogg/doc/pages.png"
    "/home/guest/Downloads/PopLib/external/ogg/doc/stream.png"
    "/home/guest/Downloads/PopLib/external/ogg/doc/vorbisword2.png"
    "/home/guest/Downloads/PopLib/external/ogg/doc/white-ogg.png"
    "/home/guest/Downloads/PopLib/external/ogg/doc/white-xifish.png"
    "/home/guest/Downloads/PopLib/external/ogg/doc/rfc3533.txt"
    "/home/guest/Downloads/PopLib/external/ogg/doc/rfc5334.txt"
    "/home/guest/Downloads/PopLib/external/ogg/doc/skeleton.html"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/ogg/html" TYPE DIRECTORY FILES "/home/guest/Downloads/PopLib/external/ogg/doc/libogg" REGEX "/[^/]*\\.am$" EXCLUDE)
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/guest/Downloads/PopLib/build/external/ogg/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
