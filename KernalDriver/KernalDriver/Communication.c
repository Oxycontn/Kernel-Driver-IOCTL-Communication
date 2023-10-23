#pragma warning (disable : 4022)

#include "Communication.h"
#include "Message.h"
#include "data.h"
#include "memory.h"

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("Connection Started\n");

	return STATUS_SUCCESS;
}

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	ULONG ByteIO = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	if (ControlCode == IO_GET_CLIENTADDRESS)
	{
		PULONG64 OutPut = (PULONG64)Irp->AssociatedIrp.SystemBuffer;
		*OutPut = CSGOClientDllAddress;

		DebugMessage("Client.dll Address Requested\n");

		Status = STATUS_SUCCESS;
		ByteIO = sizeof(*OutPut);
	}
	else if (ControlCode == IO_REQUEST_PROCESSID)
	{
		PULONG OutPut = (PULONG)Irp->AssociatedIrp.SystemBuffer;
		*OutPut = ProcessID;

		DebugMessage("Process ID Requested \n");

		Status = STATUS_SUCCESS;
		ByteIO = sizeof(*OutPut);
	}
	else if (ControlCode == IO_READ_REQUEST)
	{
		PKERNAL_READ_REQUEST ReadInput = (PKERNAL_READ_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		PEPROCESS Process;

		DebugMessage("Read Mem Requested \n");

		if (NT_SUCCESS(PsLookupProcessByProcessId(ReadInput->ProcessId, &Process)))
		{
			DebugMessage("Success (Read) \n");
			KernalReadVirtualMem(Process, ReadInput->Address, ReadInput->pBuff, ReadInput->Size);
			Status = STATUS_SUCCESS;
			ByteIO = sizeof(KERNAL_READ_REQUEST);
		}

	}
	else if (ControlCode == IO_WRITE_REQUEST)
	{
		PKERNAL_WRITE_REQUEST WriteInput = (PKERNAL_WRITE_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		PEPROCESS Process;

		DebugMessage("Write Mem Requested \n");

		if (NT_SUCCESS(PsLookupProcessByProcessId(WriteInput->ProcessId, &Process)))
		{
			DebugMessage("Success (Write) \n");
			KernalWriteVirtualMem(Process, WriteInput->pBuff, WriteInput->Address, WriteInput->Size);
			Status = STATUS_SUCCESS;
			ByteIO = sizeof(KERNAL_READ_REQUEST);
		}
	}
	else
	{
		ByteIO = 0;
	}

	Irp->IoStatus.Status = Status;
	Irp->IoStatus.Information = ByteIO;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return Status;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("Connection Ended\n");

	return STATUS_SUCCESS;
}