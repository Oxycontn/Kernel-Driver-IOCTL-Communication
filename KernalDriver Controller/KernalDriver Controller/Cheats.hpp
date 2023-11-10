#pragma once
#include "Vector.hpp"
#include "Render.hpp"
#include "Offsets.hpp"
#include "Global.hpp"

namespace Cheats 
{
    void espLoop()
    {
        Client = Driver.GetClientAddress();
        ProcessId = Driver.GetProcessId();
        Engine = Driver.GetEngineAddress();

        uintptr_t LocalPlayerPawn = Driver.ReadVirtualMem<uintptr_t>(ProcessId, Client + Offsets::dwLocalPlayerPawn, sizeof(uintptr_t));
        view_matrix_t viewMatrix = Driver.ReadVirtualMem<view_matrix_t>(ProcessId, Client + Offsets::dwViewMatrix, sizeof(view_matrix_t));

        int myHealth = Driver.ReadVirtualMem<int>(ProcessId, LocalPlayerPawn + Offsets::m_iHealth, sizeof(int));
        int myTeam = Driver.ReadVirtualMem<int>(ProcessId, LocalPlayerPawn + Offsets::m_iTeamNum, sizeof(int));

        uintptr_t Entity = Driver.ReadVirtualMem<uintptr_t>(ProcessId, Client + Offsets::dwEntityList, sizeof(uintptr_t));

        for (int i = 1; i < 64; i++)
        {
            uintptr_t listEntity = Driver.ReadVirtualMem<uintptr_t>(ProcessId, Entity + ((8 * (i & 0x7FFF) >> 9) + 16), sizeof(uintptr_t));
            if (listEntity == 0)
                continue;

            uintptr_t entityController = Driver.ReadVirtualMem<uintptr_t>(ProcessId, listEntity + (120) * (i & 0x1FF), sizeof(uintptr_t));
            if (entityController == 0)
                continue;

            uintptr_t entityControllerPawn = Driver.ReadVirtualMem<uintptr_t>(ProcessId, entityController + Offsets::m_hPlayerPawn, sizeof(uintptr_t));
            if (entityControllerPawn == 0)
                continue;

            listEntity = Driver.ReadVirtualMem<uintptr_t>(ProcessId, Entity + (0x8 * ((entityControllerPawn & 0x7FFF) >> 9) + 16), sizeof(uintptr_t));
            if (listEntity == 0)
                continue;

            uintptr_t entityPawn = Driver.ReadVirtualMem<uintptr_t>(ProcessId, listEntity + (120) * (entityControllerPawn & 0x1FF), sizeof(uintptr_t));
            if (entityPawn == 0)
                continue;

            //Entity Values
            int playerTeam = Driver.ReadVirtualMem<int>(ProcessId, entityPawn + Offsets::m_iTeamNum, sizeof(int));
            int playerHealth = Driver.ReadVirtualMem<int>(ProcessId, entityPawn + Offsets::m_iHealth, sizeof(int));
            int playerArmor = Driver.ReadVirtualMem<int>(ProcessId, entityPawn + Offsets::m_ArmorValue, sizeof(int));

            if (playerHealth <= 1 || playerHealth > 100)
                continue;

            if (entityPawn == LocalPlayerPawn)
                continue;

            //Rendering

            //Entity Feet
            Vector3 origin = Driver.ReadVirtualMem<Vector3>(ProcessId, entityPawn + Offsets::m_vecOrigin, sizeof(Vector3));

            //Bones Pointer
            uint64_t gameScene = Driver.ReadVirtualMem<uint64_t>(ProcessId, entityPawn + Offsets::m_pGameSceneNode, sizeof(uint64_t));

            //Bones
            uint64_t boneArray = Driver.ReadVirtualMem<uint64_t>(ProcessId, gameScene + 0x160 + 0x80, sizeof(uint64_t));
            Vector3 playerHead = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 6 * 32, sizeof(Vector3));
            Vector3 playerNeck = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 5 * 32, sizeof(Vector3));
            Vector3 playerShoulderL = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 13 * 32, sizeof(Vector3));
            Vector3 playerShoulderR = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 8 * 32, sizeof(Vector3));
            Vector3 playerForeL = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 14 * 32, sizeof(Vector3));
            Vector3 playerForeR = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 9 * 32, sizeof(Vector3));
            Vector3 playerHandL = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 16 * 32, sizeof(Vector3));
            Vector3 playerHandR = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 11 * 32, sizeof(Vector3));
            Vector3 playerWaist = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 0 * 32, sizeof(Vector3));
            Vector3 playerKneeL = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 26 * 32, sizeof(Vector3));
            Vector3 playerKneeR = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 23 * 32, sizeof(Vector3));
            Vector3 playerFeetL = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 27 * 32, sizeof(Vector3));
            Vector3 playerFeetR = Driver.ReadVirtualMem<Vector3>(ProcessId, boneArray + 24 * 32, sizeof(Vector3));


            //ScreenHead
            Vector3 head = { origin.x, origin.y, origin.z + 75.f };

            //WorldToScreen Calls
            Vector3 screenPos = origin.WorldtoScreen(viewMatrix);
            Vector3 screenHead = head.WorldtoScreen(viewMatrix);
            Vector3 boneHead = playerHead.WorldtoScreen(viewMatrix);
            Vector3 boneNeck = playerNeck.WorldtoScreen(viewMatrix);
            Vector3 boneShoulderL = playerShoulderL.WorldtoScreen(viewMatrix);
            Vector3 boneShoulderR = playerShoulderR.WorldtoScreen(viewMatrix);
            Vector3 boneForeL = playerForeL.WorldtoScreen(viewMatrix);
            Vector3 boneForeR = playerForeR.WorldtoScreen(viewMatrix);
            Vector3 boneHandL = playerHandL.WorldtoScreen(viewMatrix);
            Vector3 boneHandR = playerHandR.WorldtoScreen(viewMatrix);
            Vector3 boneWaist = playerWaist.WorldtoScreen(viewMatrix);
            Vector3 boneKneeL = playerKneeL.WorldtoScreen(viewMatrix);
            Vector3 boneKneeR = playerKneeR.WorldtoScreen(viewMatrix);
            Vector3 boneFeetL = playerFeetL.WorldtoScreen(viewMatrix);
            Vector3 boneFeetR = playerFeetR.WorldtoScreen(viewMatrix);

            //Define
            float height = abs(screenPos.y - screenHead.y);
            float width = height / 2.4f;

                //Esp boxes

                //2d
                if (playerTeam == myTeam && espBoxT == true && TeamActiveCombo == 0)
                    Render::DrawRect(screenPos.x - width / 2, screenHead.y, width, height, ImColor(TeamFrameColor[0], TeamFrameColor[1], TeamFrameColor[2]), 1.5);
                else if (playerTeam != myTeam && espBoxE == true && EnemyActiveCombo == 0)
                    Render::DrawRect(screenPos.x - width / 2, screenHead.y, width, height, ImColor(EnemyFrameColor[0], EnemyFrameColor[1], EnemyFrameColor[2]), 1.5);

                //3d


                //Corners
                if (playerTeam == myTeam && espBoxT == true && TeamActiveCombo == 2)
                {
                    //Top Top
                    //Left
                    Render::DrawLine(screenHead.x - width / 3, screenHead.y, screenHead.x - width / 6, screenHead.y, ImColor(TeamFrameColor[0], TeamFrameColor[1], TeamFrameColor[2]), 1.5f);
                    //Right
                    Render::DrawLine(screenPos.x + width / 6, screenHead.y, screenPos.x + width / 3, screenHead.y, ImColor(TeamFrameColor[0], TeamFrameColor[1], TeamFrameColor[2]), 1.5f);

                    //Bottom Bottom
                    //Left
                    Render::DrawLine(screenHead.x - width / 3, screenPos.y, screenHead.x - width / 6, screenPos.y, ImColor(TeamFrameColor[0], TeamFrameColor[1], TeamFrameColor[2]), 1.5f);
                    //Right
                    Render::DrawLine(screenPos.x + width / 6, screenPos.y, screenPos.x + width / 3, screenPos.y, ImColor(TeamFrameColor[0], TeamFrameColor[1], TeamFrameColor[2]), 1.5f);

                    //Top Bottom
                    //Left
                    Render::DrawLine(screenHead.x - width / 3, screenHead.y + height / 10, screenHead.x - width / 3, screenHead.y, ImColor(TeamFrameColor[0], TeamFrameColor[1], TeamFrameColor[2]), 1.5f);
                    //Right
                    Render::DrawLine(screenPos.x + width / 3, screenHead.y + height / 10, screenPos.x + width / 3, screenHead.y, ImColor(TeamFrameColor[0], TeamFrameColor[1], TeamFrameColor[2]), 1.5f);

                    //Bottom Top
                    //Left
                    Render::DrawLine(screenHead.x - width / 3, screenPos.y - height / 10, screenHead.x - width / 3, screenPos.y, ImColor(TeamFrameColor[0], TeamFrameColor[1], TeamFrameColor[2]), 1.5f);

                    Render::DrawLine(screenPos.x + width / 3, screenPos.y - height / 10, screenPos.x + width / 3, screenPos.y, ImColor(TeamFrameColor[0], TeamFrameColor[1], TeamFrameColor[2]), 1.5f);
                }
                else if (playerTeam != myTeam && espBoxE == true && EnemyActiveCombo == 2)
                {
                    //Top Top
                    //Left
                    Render::DrawLine(screenHead.x - width / 3, screenHead.y, screenHead.x - width / 6, screenHead.y, ImColor(EnemyFrameColor[0], EnemyFrameColor[1], EnemyFrameColor[2]), 1.5f);
                    //Right
                    Render::DrawLine(screenPos.x + width / 6, screenHead.y, screenPos.x + width / 3, screenHead.y, ImColor(EnemyFrameColor[0], EnemyFrameColor[1], EnemyFrameColor[2]), 1.5f);

                    //Bottom Bottom
                    //Left
                    Render::DrawLine(screenHead.x - width / 3, screenPos.y, screenHead.x - width / 6, screenPos.y, ImColor(EnemyFrameColor[0], EnemyFrameColor[1], EnemyFrameColor[2]), 1.5f);
                    //Right
                    Render::DrawLine(screenPos.x + width / 6, screenPos.y, screenPos.x + width / 3, screenPos.y, ImColor(EnemyFrameColor[0], EnemyFrameColor[1], EnemyFrameColor[2]), 1.5f);

                    //Top Bottom
                    //Left
                    Render::DrawLine(screenHead.x - width / 3, screenHead.y + height / 10, screenHead.x - width / 3, screenHead.y, ImColor(EnemyFrameColor[0], EnemyFrameColor[1], EnemyFrameColor[2]), 1.5f);
                    //Right
                    Render::DrawLine(screenPos.x + width / 3, screenHead.y + height / 10, screenPos.x + width / 3, screenHead.y, ImColor(EnemyFrameColor[0], EnemyFrameColor[1], EnemyFrameColor[2]), 1.5f);

                    //Bottom Top
                    //Left
                    Render::DrawLine(screenHead.x - width / 3, screenPos.y - height / 10, screenHead.x - width / 3, screenPos.y, ImColor(EnemyFrameColor[0], EnemyFrameColor[1], EnemyFrameColor[2]), 1.5f);
                    //Right
                    Render::DrawLine(screenPos.x + width / 3, screenPos.y - height / 10, screenPos.x + width / 3, screenPos.y, ImColor(EnemyFrameColor[0], EnemyFrameColor[1], EnemyFrameColor[2]), 1.5f);
                }

                //Esp Head Circle
                if (playerTeam == myTeam && espHeadT == true)
                    Render::DrawHeadCircle(boneHead.x, boneHead.y, width / 7.f, ImColor(1.f, 1.f, 1.f), 1.5f);
                else if (playerTeam != myTeam && espHeadE == true)
                    Render::DrawHeadCircle(boneHead.x, boneHead.y, width / 7.f, ImColor(1.f, 1.f, 1.f), 1.5f);

                //Esp Skelton
                if (playerTeam == myTeam && espSkeltonT == true)
                {
                    Render::DrawLine(boneNeck.x, boneNeck.y, boneHead.x, boneHead.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneNeck.x, boneNeck.y, boneShoulderR.x, boneShoulderR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneNeck.x, boneNeck.y, boneShoulderL.x, boneShoulderL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneShoulderL.x, boneShoulderL.y, boneForeL.x, boneForeL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneShoulderR.x, boneShoulderR.y, boneForeR.x, boneForeR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneForeL.x, boneForeL.y, boneHandL.x, boneHandL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneForeR.x, boneForeR.y, boneHandR.x, boneHandR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneNeck.x, boneNeck.y, boneWaist.x, boneWaist.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneWaist.x, boneWaist.y, boneKneeL.x, boneKneeL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneWaist.x, boneWaist.y, boneKneeR.x, boneKneeR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneKneeL.x, boneKneeL.y, boneFeetL.x, boneFeetL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneKneeR.x, boneKneeR.y, boneFeetR.x, boneFeetR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                }
                else if (playerTeam != myTeam && espSkeltonE == true)
                {
                    Render::DrawLine(boneNeck.x, boneNeck.y, boneHead.x, boneHead.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneNeck.x, boneNeck.y, boneShoulderR.x, boneShoulderR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneNeck.x, boneNeck.y, boneShoulderL.x, boneShoulderL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneShoulderL.x, boneShoulderL.y, boneForeL.x, boneForeL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneShoulderR.x, boneShoulderR.y, boneForeR.x, boneForeR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneForeL.x, boneForeL.y, boneHandL.x, boneHandL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneForeR.x, boneForeR.y, boneHandR.x, boneHandR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneNeck.x, boneNeck.y, boneWaist.x, boneWaist.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneWaist.x, boneWaist.y, boneKneeL.x, boneKneeL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneWaist.x, boneWaist.y, boneKneeR.x, boneKneeR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneKneeL.x, boneKneeL.y, boneFeetL.x, boneFeetL.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                    Render::DrawLine(boneKneeR.x, boneKneeR.y, boneFeetR.x, boneFeetR.y, ImColor(1.f, 1.f, 1.f), 1.5f);
                }

                //Health Bar If(s)
                if (playerTeam == myTeam && espHealthBarT == true)
                {
                    if (playerHealth <= 100 && playerHealth >= 76)
                        Render::DrawHealhBar(screenPos.x - width / 2, screenPos.y, width, height / 60, ImColor(0.f, 1.f, 0.f));

                    if (playerHealth <= 75 && playerHealth >= 51)
                        Render::DrawHealhBar(screenPos.x - width / 2, screenPos.y, (width / 1.5f), height / 60, ImColor(255.f, 255.f, 0.f));

                    if (playerHealth <= 50 && playerHealth >= 26)
                        Render::DrawHealhBar(screenPos.x - width / 2, screenPos.y, (width / 2.5f), height / 60, ImColor(255, 127, 80));

                    if (playerHealth <= 25 && playerHealth >= 1)
                        Render::DrawHealhBar(screenPos.x - width / 2, screenPos.y, (width / 4.5f), height / 60, ImColor(1.f, 0.f, 0.f));
                }
                else if (playerTeam != myTeam && espHealthBarE == true)
                {
                    if (playerHealth <= 100 && playerHealth >= 76)
                        Render::DrawHealhBar(screenPos.x - width / 2, screenPos.y, width, height / 60, ImColor(0.f, 1.f, 0.f));

                    if (playerHealth <= 75 && playerHealth >= 51)
                        Render::DrawHealhBar(screenPos.x - width / 2, screenPos.y, (width / 1.5f), height / 60, ImColor(255.f, 255.f, 0.f));

                    if (playerHealth <= 50 && playerHealth >= 26)
                        Render::DrawHealhBar(screenPos.x - width / 2, screenPos.y, (width / 2.5f), height / 60, ImColor(255, 127, 80));

                    if (playerHealth <= 25 && playerHealth >= 1)
                        Render::DrawHealhBar(screenPos.x - width / 2, screenPos.y, (width / 4.5f), height / 60, ImColor(1.f, 0.f, 0.f));
                }
        }
    }
}

