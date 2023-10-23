#pragma warning (disable : 4047 4024)
#pragma once

#include "ntifs.h"
#include "ntddk.h"

NTSTATUS NTAPI MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	PVOID SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviosMode,
	PSIZE_T ReturnSize
);

NTSTATUS KernalReadVirtualMem(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size);

NTSTATUS KernalWriteVirtualMem(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size);
