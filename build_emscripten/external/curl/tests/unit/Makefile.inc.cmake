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

# these files are used in every single unit test program

set(FIRSTFILES 
 ../libtest/first.c 
 ../libtest/first.h)

set(UNITFILES curlcheck.h ${FIRSTFILES})

# These are all unit test programs
set(UNITPROGS unit1300          unit1302 unit1303 unit1304 unit1305 unit1307 
          unit1309 unit1323 
 unit1330          unit1395 unit1396 unit1397 unit1398 
 unit1399 
 unit1600 unit1601 unit1602 unit1603          unit1605 unit1606 unit1607 
 unit1608 unit1609 unit1610 unit1611 unit1612 unit1614 unit1615 unit1616 
 unit1620 
 unit1650 unit1651 unit1652 unit1653 unit1654 unit1655 unit1656 unit1657 
 unit1658 
 unit1660 unit1661 unit1663 unit1664 
 unit1979 unit1980 
 unit2600 unit2601 unit2602 unit2603 unit2604 
 unit3200 
 unit3205 
 unit3211 unit3212 unit3213)

set(unit1300_SOURCES unit1300.c ${UNITFILES})

set(unit1302_SOURCES unit1302.c ${UNITFILES})

set(unit1303_SOURCES unit1303.c ${UNITFILES})

set(unit1304_SOURCES unit1304.c ${UNITFILES})

set(unit1305_SOURCES unit1305.c ${UNITFILES})

set(unit1307_SOURCES unit1307.c ${UNITFILES})

set(unit1309_SOURCES unit1309.c ${UNITFILES})

set(unit1323_SOURCES unit1323.c ${UNITFILES})

set(unit1330_SOURCES unit1330.c ${UNITFILES})

set(unit1395_SOURCES unit1395.c ${UNITFILES})

set(unit1396_SOURCES unit1396.c ${UNITFILES})

set(unit1397_SOURCES unit1397.c ${UNITFILES})

set(unit1398_SOURCES unit1398.c ${UNITFILES})

set(unit1399_SOURCES unit1399.c ${UNITFILES})

set(unit1600_SOURCES unit1600.c ${UNITFILES})

set(unit1601_SOURCES unit1601.c ${UNITFILES})

set(unit1602_SOURCES unit1602.c ${UNITFILES})

set(unit1603_SOURCES unit1603.c ${UNITFILES})

set(unit1605_SOURCES unit1605.c ${UNITFILES})

set(unit1606_SOURCES unit1606.c ${UNITFILES})

set(unit1607_SOURCES unit1607.c ${UNITFILES})

set(unit1608_SOURCES unit1608.c ${UNITFILES})

set(unit1609_SOURCES unit1609.c ${UNITFILES})

set(unit1610_SOURCES unit1610.c ${UNITFILES})

set(unit1611_SOURCES unit1611.c ${UNITFILES})

set(unit1612_SOURCES unit1612.c ${UNITFILES})

set(unit1614_SOURCES unit1614.c ${UNITFILES})

set(unit1615_SOURCES unit1615.c ${UNITFILES})

set(unit1616_SOURCES unit1616.c ${UNITFILES})

set(unit1620_SOURCES unit1620.c ${UNITFILES})

set(unit1650_SOURCES unit1650.c ${UNITFILES})

set(unit1651_SOURCES unit1651.c ${UNITFILES})

set(unit1652_SOURCES unit1652.c ${UNITFILES})

set(unit1653_SOURCES unit1653.c ${UNITFILES})

set(unit1654_SOURCES unit1654.c ${UNITFILES})

set(unit1655_SOURCES unit1655.c ${UNITFILES})

set(unit1656_SOURCES unit1656.c ${UNITFILES})

set(unit1657_SOURCES unit1657.c ${UNITFILES})

set(unit1658_SOURCES unit1658.c ${UNITFILES})

set(unit1660_SOURCES unit1660.c ${UNITFILES})

set(unit1661_SOURCES unit1661.c ${UNITFILES})

set(unit1663_SOURCES unit1663.c ${UNITFILES})

set(unit1664_SOURCES unit1664.c ${UNITFILES})

set(unit1979_SOURCES unit1979.c ${UNITFILES})

set(unit1980_SOURCES unit1980.c ${UNITFILES})

set(unit2600_SOURCES unit2600.c ${UNITFILES})

set(unit2601_SOURCES unit2601.c ${UNITFILES})

set(unit2602_SOURCES unit2602.c ${UNITFILES})

set(unit2603_SOURCES unit2603.c ${UNITFILES})

set(unit2604_SOURCES unit2604.c ${UNITFILES})

set(unit3200_SOURCES unit3200.c ${UNITFILES})

set(unit3205_SOURCES unit3205.c ${UNITFILES})

set(unit3211_SOURCES unit3211.c ${UNITFILES})

set(unit3212_SOURCES unit3212.c ${UNITFILES})

set(unit3213_SOURCES unit3213.c ${UNITFILES})
