#***************************************************************************
#                                  _   _ ____  _
#  Project                     ___| | | |  _ \| |
#                             / __| | | | |_) | |
#                            | (__| |_| |  _ <| |___
#                             \___|\___/|_| \_\_____|
#
# Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
#
# This software is licensed as described in the file COPYING, which
# you should have received as part of this distribution. The terms
# are also available at https://curl.se/docs/copyright.html.
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the COPYING file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
# SPDX-License-Identifier: curl
#
###########################################################################

set(SERVERPROGS resolve rtspd sockfilt sws tftpd socksd mqttd dnsd)

set(MEMDEBUG 
  ../../lib/memdebug.c 
  ../../lib/memdebug.h)

set(CURLX_SRCS 
  ../../lib/curlx/base64.c 
  ../../lib/curlx/multibyte.c 
  ../../lib/curlx/nonblock.c 
  ../../lib/curlx/strparse.c 
  ../../lib/curlx/timediff.c 
  ../../lib/curlx/timeval.c 
  ../../lib/curlx/version_win32.c 
  ../../lib/curlx/warnless.c 
  ../../lib/curlx/winapi.c)

set(CURLX_HDRS 
  ../../lib/curlx/base64.h 
  ../../lib/curlx/curlx.h 
  ../../lib/curlx/multibyte.h 
  ../../lib/curlx/nonblock.h 
  ../../lib/curlx/timediff.h 
  ../../lib/curlx/timeval.h 
  ../../lib/curlx/version_win32.h 
  ../../lib/curlx/warnless.h 
  ../../lib/curlx/winapi.h)

set(UTIL 
  getpart.c 
  getpart.h 
  util.c 
  util.h 
  server_setup.h)

set(FIRSTFILES 
  first.c 
  first.h)

set(INET_PTON 
  ../../lib/curlx/inet_pton.c)

set(resolve_SOURCES ${MEMDEBUG} ${CURLX_SRCS} ${CURLX_HDRS} ${UTIL} 
  resolve.c)
set(resolve_LDADD ${CURL_NETWORK_AND_TIME_LIBS})
set(resolve_CFLAGS ${AM_CFLAGS})

set(rtspd_SOURCES ${MEMDEBUG} ${CURLX_SRCS} ${CURLX_HDRS} ${UTIL} 
  server_sockaddr.h 
  rtspd.c)
set(rtspd_LDADD ${CURL_NETWORK_AND_TIME_LIBS})
set(rtspd_CFLAGS ${AM_CFLAGS})

set(sockfilt_SOURCES ${MEMDEBUG} ${CURLX_SRCS} ${CURLX_HDRS} ${UTIL} ${INET_PTON} 
  server_sockaddr.h 
  sockfilt.c)
set(sockfilt_LDADD ${CURL_NETWORK_AND_TIME_LIBS})
set(sockfilt_CFLAGS ${AM_CFLAGS})

set(socksd_SOURCES ${MEMDEBUG} ${CURLX_SRCS} ${CURLX_HDRS} ${UTIL} ${INET_PTON} 
  server_sockaddr.h 
  socksd.c)
set(socksd_LDADD ${CURL_NETWORK_AND_TIME_LIBS})
set(socksd_CFLAGS ${AM_CFLAGS})

set(mqttd_SOURCES ${MEMDEBUG} ${CURLX_SRCS} ${CURLX_HDRS} ${UTIL} 
  server_sockaddr.h 
  mqttd.c)
set(mqttd_LDADD ${CURL_NETWORK_AND_TIME_LIBS})
set(mqttd_CFLAGS ${AM_CFLAGS})

set(sws_SOURCES ${MEMDEBUG} ${CURLX_SRCS} ${CURLX_HDRS} ${UTIL} ${INET_PTON} 
  server_sockaddr.h 
  sws.c)
set(sws_LDADD ${CURL_NETWORK_AND_TIME_LIBS})
set(sws_CFLAGS ${AM_CFLAGS})

set(tftpd_SOURCES ${MEMDEBUG} ${CURLX_SRCS} ${CURLX_HDRS} ${UTIL} 
  server_sockaddr.h 
  tftpd.c 
  tftp.h)
set(tftpd_LDADD ${CURL_NETWORK_AND_TIME_LIBS})
set(tftpd_CFLAGS ${AM_CFLAGS})

set(dnsd_SOURCES ${MEMDEBUG} ${CURLX_SRCS} ${CURLX_HDRS} ${UTIL} 
  dnsd.c)
set(dnsd_LDADD ${CURL_NETWORK_AND_TIME_LIBS})
set(dnsd_CFLAGS ${AM_CFLAGS})
