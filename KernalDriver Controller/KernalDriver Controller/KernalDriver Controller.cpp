#include <iostream>
#include "KernalInterface.hpp"
#include "Offsets.hpp"
#include <sstream>

int main()
{
	KernelInterface Driver = KernelInterface("\\\\.\\KernalDriver");
    
    ULONG64 Address = Driver.GetClientAddress();
    int ProcessId = Driver.GetProcessId();

    std::cout << std::hex << "CSGO Client Address \n" << Address << std::endl;
    std::cout << std::hex << "CSGO Process ID \n" << ProcessId << std::endl;

    while (true)
    {
        uintptr_t LocalPlayerAddress = Driver.ReadVirtualMem<uintptr_t>(ProcessId, Address + Offsets::dwLocalPlayerController, sizeof(uintptr_t));

        int Health = Driver.ReadVirtualMem<int>(ProcessId, LocalPlayerAddress + 0x32C, sizeof(int));

        std::cout << std::dec << Health << std::endl;

        Sleep(800);
    }
}

