/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name: 

    main.cpp

Abstract:

    This module contains the main entry point for the SpbTestTool
    app.  It facilitates accepting input, building commands, and
    printing output.

Environment:

    user-mode

Revision History:

--*/

#include "TestApp.h"

HANDLE g_FPHandle = NULL;

void __cdecl  PrintUsage()
{
	wprintf(L"****************************************************************************************\n");
	wprintf(L"                              Driver Test Function.                                     \n");
	wprintf(L"                              Selections:                                               \n");
	wprintf(L"                               -o: Open Device.                                         \n");
	wprintf(L"                               -c: Close Session.                                       \n");
	wprintf(L"                               -d: Display Log Information.                             \n");
	wprintf(L"****************************************************************************************\n");

	OutputDebugString(L"****************************************************************************************\n");
	OutputDebugString(L"                              Driver Test Function.                                     \n");
	OutputDebugString(L"                              Selections:                                               \n");
	OutputDebugString(L"                               -o: Create Device.                                       \n");
	OutputDebugString(L"                               -c: Open Session.                                        \n");
	OutputDebugString(L"                               -d: Display Log Information.                             \n");
	OutputDebugString(L"****************************************************************************************\n");
}

void __cdecl  OpenDevice()
{
	CONFIGRET Cr = CR_FAILURE;
	ULONG InterfaceListSize = 0;
	PWCHAR pInterfaceList = NULL;
	PWCHAR pCompleteDeviceName = NULL;
	char str[128] = { 0 };

	//
	// Get the interface list
	//
	Cr = CM_Get_Device_Interface_List_Size(&InterfaceListSize,
		(GUID *)&QC_SENSOR1_INTERFACE_GUID,
		NULL,
		CM_GET_DEVICE_INTERFACE_LIST_PRESENT);
	if ((CR_SUCCESS != Cr) || (1 == InterfaceListSize))
	{
		sprintf_s(str, "CM_Get_Device_Interface_List_Size failed with 0x%08x.\n", Cr);
		wprintf(L"CM_Get_Device_Interface_List_Size failed with 0x%x.", Cr);
		OutputDebugStringA(str);
	}

	pInterfaceList = (PWCHAR)malloc(InterfaceListSize * sizeof(WCHAR));
	if (NULL == pInterfaceList)
	{
		wprintf(L"Cannot allocate memory for symbolic links.");
		OutputDebugString(L"Cannot allocate memory for symbolic links.");
	}

	Cr = CM_Get_Device_Interface_List((GUID *)&QC_SENSOR1_INTERFACE_GUID,
		NULL,
		pInterfaceList,
		InterfaceListSize,
		CM_GET_DEVICE_INTERFACE_LIST_PRESENT);
	if (CR_SUCCESS != Cr)
	{
		sprintf_s(str, "CM_Get_Device_Interface_List failed with 0x%08x.\n", Cr);
		wprintf(L"CM_Get_Device_Interface_List failed with 0x%x.", Cr);
		OutputDebugStringA(str);
	}

	pCompleteDeviceName = pInterfaceList;

	wprintf(L"DeviceName = (%s)\n", pCompleteDeviceName);

	OutputDebugString(pCompleteDeviceName);

	g_FPHandle = CreateFile(pCompleteDeviceName,
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (g_FPHandle == INVALID_HANDLE_VALUE)
	{
		sprintf_s(str, "Failed to open the device. ErrorCode = 0x%08x.\n", GetLastError());
		wprintf(L"Failed to open the device, error - %d", GetLastError());
		OutputDebugStringA(str);
	}
	else
	{
		OutputDebugString(L"Open Device Success.\n");	
	}
}

void __cdecl  CloseDevice()
{
	if (g_FPHandle != NULL)
	{
		CloseHandle(g_FPHandle);
	}
}

void __cdecl  DisplayLog()
{
	wprintf(L"How to Display Log.\n");
	wprintf(L"Tshell: Use standord c function \"printf() or wprintf()\".\n");
	wprintf(L"Tshell: Use standord win32 function \"OutputDebugString()\".\n");
}

#if 0

void __cdecl 
main(
	_In_                    ULONG ArgumentsCe,
	_In_reads_(ArgumentsCe) PCSTR Arguments[]
	)
#endif
void __cdecl main(int argc, CHAR* argv[])
{
	OutputDebugString(L"Driver Test App.\n");

	PrintUsage();

	ULONG arg = 1;

    if (argc <= 2)
    {
        if ((argv[arg][0] != '/') &&
            (argv[arg][0] != '-'))
        {
			PrintUsage();           
        }		
        else
        {
            if (tolower(argv[arg][1]) == 'o')
            {
				OpenDevice();
            }
            else if (tolower(argv[arg][1]) == 'c')
            {
				CloseDevice();
            }
			else if (tolower(argv[arg][1]) == 'd')
			{
				DisplayLog();
			}		
			else
			{
				wprintf(L"Invalid Parameters.\n");
				PrintUsage();
			}
        }       
    }
	else
	{
		wprintf(L"No Valid Parameters.\n");
		PrintUsage();
	}

    return;
}