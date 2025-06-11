# Install script for directory: /home/guest/Downloads/PopLib/external/curl/docs/libcurl

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man3" TYPE FILE FILES
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_cleanup.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_duphandle.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_escape.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_getinfo.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_header.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_init.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_nextheader.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_option_by_id.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_option_by_name.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_option_next.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_pause.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_perform.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_recv.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_reset.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_send.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_setopt.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_ssls_export.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_ssls_import.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_strerror.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_unescape.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_easy_upkeep.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_escape.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_formadd.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_formfree.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_formget.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_free.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_getdate.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_getenv.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_global_cleanup.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_global_init.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_global_init_mem.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_global_sslset.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_global_trace.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_addpart.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_data.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_data_cb.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_encoder.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_filedata.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_filename.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_free.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_headers.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_init.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_name.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_subparts.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mime_type.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_mprintf.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_add_handle.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_assign.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_cleanup.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_fdset.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_get_handles.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_info_read.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_init.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_perform.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_poll.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_remove_handle.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_setopt.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_socket.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_socket_action.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_socket_all.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_strerror.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_timeout.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_wait.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_waitfds.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_multi_wakeup.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_pushheader_byname.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_pushheader_bynum.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_share_cleanup.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_share_init.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_share_setopt.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_share_strerror.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_slist_append.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_slist_free_all.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_strequal.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_strnequal.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_unescape.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_url.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_url_cleanup.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_url_dup.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_url_get.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_url_set.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_url_strerror.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_version.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_version_info.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_ws_meta.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_ws_recv.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/curl_ws_send.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-easy.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-env-dbg.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-env.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-errors.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-multi.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-security.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-share.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-symbols.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-thread.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-tutorial.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-url.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl-ws.3"
    "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/libcurl.3"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/opts/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/guest/Downloads/PopLib/build/external/curl/docs/libcurl/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
