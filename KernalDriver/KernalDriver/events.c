#pragma warning (disable : 4047 4311)

#include "events.h"
#include "Message.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{

	if (wcsstr(FullImageName->Buffer, L"\\Steam\\steamapps\\common\\Counter-Strike Global Offensive\\game\\csgo\\bin\\win64\\client.dll"))
	{
		DebugMessage("CSGO2 Client Dll found\n");

		CSGOCliendDllAddress = ImageInfo->ImageBase;
		ProcessID = (ULONG) ProcessId;

		DebugMessage("ProcessID: %d \n", ProcessId);
	}
	return STATUS_SUCCESS;
}