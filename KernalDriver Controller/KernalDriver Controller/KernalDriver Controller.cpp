#include <iostream>
#include "KernalInterface.hpp"
#include "Offsets.hpp"

int main()
{
    KernalInterface Driver = KernalInterface("\\\\.\\KernalDriver");

    ULONG address = Driver.GetClientAddress();
    ULONG ProcessId = Driver.GetProcessId();

    std::cout << "CSGO Client Address\n" << address << std::endl;
    std::cout << "CSGO Process ID\n" << ProcessId << std::endl;
    
    while (true)
    {
        intptr_t LocalPlayerAddress = Driver.ReadVirtualMem<intptr_t>(ProcessId, address + 0x17E7158, sizeof(intptr_t));
        int Health = Driver.ReadVirtualMem<int>(ProcessId, LocalPlayerAddress + 0x32C, sizeof(int));

        Sleep(60);

        std::cout << Health << std::endl;
    }
}

