#include <dwmapi.h>
#include <d3d11.h>
#include <windowsx.h>
#include <sstream>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"

#include "Communication.hpp"
#include "KernalInterface.hpp"
#include "Cheats.hpp"
#include "Global.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
    if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param))
    {
        return 0L;
    }

    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0L;
    }

    return DefWindowProc(window, message, w_param, l_param);
}

bool isRunning(LPCSTR pName)
{
    HWND hwnd;
    hwnd = FindWindow(NULL, pName);
    if (hwnd != 0) {
        return true;
    }
    else {
        return false;
    }
}

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show)
{
    //Overlay Start
    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.hInstance = instance;
    wc.lpfnWndProc = window_procedure;
    wc.lpszClassName = " ";

    RegisterClassExA(&wc);

    const HWND Overlay = CreateWindowExA(WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_LAYERED, wc.lpszClassName, " ", WS_POPUP, 0, 0, screenWidth, screenHeight, nullptr, nullptr, wc.hInstance, nullptr);

    SetLayeredWindowAttributes(Overlay, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);

    {
        RECT client_area1{};
        GetClientRect(Overlay, &client_area1);

        RECT window_area1{};
        GetWindowRect(Overlay, &window_area1);

        POINT diff1{};
        ClientToScreen(Overlay, &diff1);

        const MARGINS margins1
        {
            window_area1.left + (diff1.x - window_area1.left),
            window_area1.top + (diff1.y - window_area1.top),
            client_area1.right,
            client_area1.bottom
        };
        
        DwmExtendFrameIntoClientArea(Overlay, &margins1);
    }
        
    DXGI_SWAP_CHAIN_DESC overlayDesc{};
    overlayDesc.BufferDesc.RefreshRate.Numerator = 300U; //fps
    overlayDesc.BufferDesc.RefreshRate.Denominator = 1U;
    overlayDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    overlayDesc.SampleDesc.Count = 1U;
    overlayDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    overlayDesc.BufferCount = 2U;
    overlayDesc.OutputWindow = Overlay;
    overlayDesc.Windowed = TRUE;
    overlayDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    overlayDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    constexpr D3D_FEATURE_LEVEL levels[2]
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_0
    };

    ID3D11Device* device{ nullptr };
    ID3D11DeviceContext* device_context{ nullptr };
    IDXGISwapChain* swap_chain{ nullptr };
    ID3D11RenderTargetView* render_target_view{ nullptr };
    D3D_FEATURE_LEVEL level{};

    D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0U, levels, 2U, D3D11_SDK_VERSION, &overlayDesc, &swap_chain, &device, &level, &device_context);

    ID3D11Texture2D* back_buffer{ nullptr };
    swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));

    if (back_buffer)
    {
        device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
        back_buffer->Release();
    }

    ShowWindow(Overlay, cmd_show);
    UpdateWindow(Overlay);

    ImGui::CreateContext();
    ImGui::StyleColorsClassic();

    ImGui_ImplWin32_Init(Overlay);;
    ImGui_ImplDX11_Init(device, device_context);



    //Main Loop
    while (mainloop == true)
    {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (menu == true)
            SetWindowLong(Overlay, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOPMOST);
        else
            SetWindowLong(Overlay, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_LAYERED);

        if (GetAsyncKeyState(VK_INSERT) < 0)
        {
            if (menu == false)
                menu = true;
            else
                menu = false;
            Sleep(150);
        }

        Menus::DrawInGameMenu();
        Cheats::espLoop();

        ImGui::Render();

        constexpr float color[4](0.f, 0.f, 0.f, 0.f);
        device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
        device_context->ClearRenderTargetView(render_target_view, color);

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        swap_chain->Present(0U, 0U);
    }



    //Overlay End
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();

    if (swap_chain)
    {
        swap_chain->Release();
    }
    if (device_context)
    {
        device_context->Release();
    }
    if (device)
    {
        device->Release();
    }
    if (render_target_view)
    {
        render_target_view->Release();
    }

    DestroyWindow(Overlay);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

