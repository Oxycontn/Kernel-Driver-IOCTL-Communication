#pragma warning (disable : 4047 4311)

#include "events.h"
#include "Message.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	if (wcsstr(FullImageName->Buffer, L"\\csgo\\bin\\win64\\client.dll"))
	{
		CSGOClientDllAddress = ImageInfo->ImageBase;

		DebugMessage("CSGO2 Client.dll Found: %#010x \n", CSGOClientDllAddress);

		ProcessID = ProcessId;

		DebugMessage("ProcessID: %#010x \n", ProcessID);
	}
	return STATUS_SUCCESS;
}