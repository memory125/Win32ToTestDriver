/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name: 

    spbtestioctl.h

Abstract:

    This module contains the public device path names and
    IOCTL definitions for the SpbTestTool.

Environment:

Revision History:

--*/

#ifndef _SPBFPTEST_H_
#define _SPBFPTEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#include <winioctl.h>
#include <Cfgmgr32.h>

#define countof(x) (sizeof(x) / sizeof(x[0]))


static const GUID QC_SENSOR1_INTERFACE_GUID =
{ 0xa2f9134, 0xea8, 0x4c1e,{ 0xa4, 0x7e, 0x18, 0xb5, 0x3b, 0x65, 0xa8, 0xf6 } };


#endif _SPBFPTEST_H_