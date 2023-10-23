#pragma once

#include "Communication.hpp"

class KernelInterface
{
public:
	HANDLE hDriver;

	KernelInterface(LPCSTR RegistryPath)
	{
		hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	}

	ULONG64 GetClientAddress()
	{
		ULONG64 Address;
		DWORD Bytes;

		if (DeviceIoControl(hDriver, IO_GET_CLIENTADDRESS, &Address, sizeof(Address), &Address, sizeof(Address), &Bytes, NULL))
		{
			return Address;
		}

		return false;
	}

	int GetProcessId()
	{
		int ProcessID;
		DWORD Bytes;

		if (DeviceIoControl(hDriver, IO_REQUEST_PROCESSID, &ProcessID, sizeof(ProcessID), &ProcessID, sizeof(ProcessID), &Bytes, NULL))
		{
			return ProcessID;
		}

		return 0;
	}

	template <typename type>
	type ReadVirtualMem(int ProcessID, uintptr_t ReadAddress, SIZE_T Size)
	{
		type Buffer;

		KERNAL_READ_REQUEST Readrequest;

		Readrequest.ProcessId = ProcessID;
		Readrequest.Address = ReadAddress;
		Readrequest.pBuff = &Buffer;
		Readrequest.Size = Size;

		if (DeviceIoControl(hDriver, IO_READ_REQUEST, &Readrequest, sizeof(Readrequest), &Readrequest, sizeof(Readrequest), 0, 0))
		{
			return Buffer;
		}

		return Buffer;
	}

	template <typename type>
	bool WriteVirtualMem(int ProcessID, uintptr_t WriteAddress, type WriteValue, SIZE_T Size)
	{

		DWORD Bytes;

		KERNAL_WRITE_REQUEST Writerequest;

		Writerequest.ProcessId = ProcessID;
		Writerequest.Address = WriteAddress;
		Writerequest.pBuff = &WriteValue;
		Writerequest.Size = Size;

		if (DeviceIoControl(hDriver, IO_WRITE_REQUEST, &Writerequest, sizeof(Writerequest), 0, 0, &Bytes, NULL))
		{
			return true;
		}

		return false;
	}

};