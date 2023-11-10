#pragma once

#include <iostream>
#include <stdlib.h>

namespace Offsets
{
    constexpr std::ptrdiff_t dwEntityList = 0x17ADAF0;
    constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x16B9398;
    constexpr std::ptrdiff_t dwViewMatrix = 0x180C0F0;
    constexpr std::ptrdiff_t m_iTeamNum = 0x3BF;
    constexpr std::ptrdiff_t m_iHealth = 0x32C;
    constexpr std::ptrdiff_t m_hPlayerPawn = 0x7BC;
    constexpr std::ptrdiff_t m_sSanitizedPlayerName = 0x720;
    constexpr std::ptrdiff_t m_clrRender = 0xA73;
    constexpr std::ptrdiff_t m_vecOrigin = 0x1224;
    constexpr std::ptrdiff_t m_pGameSceneNode = 0x310;
    constexpr std::ptrdiff_t m_ArmorValue = 0x1508;
}