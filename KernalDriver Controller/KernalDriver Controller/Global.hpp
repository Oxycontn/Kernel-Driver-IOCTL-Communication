#pragma once

//Driver Globals
KernelInterface Driver = KernelInterface("\\\\.\\KernalDriver");
ULONG64 Client;
ULONG64 Engine;
int ProcessId;

//Screen Globals
int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
bool mainloop = true;

//Menu Globals
bool espBoxT;
bool espBoxE;
bool espSkeltonT;
bool espSkeltonE;
bool espHeadT;
bool espHeadE;
bool espHealthBarT;
bool espHealthBarE;
bool menu;
float TeamFrameColor[3];
float EnemyFrameColor[3];
int TeamActiveCombo;
int EnemyActiveCombo;
const char* ComboSelections[3] = { "2D Box", "3D Box", "Corners" };