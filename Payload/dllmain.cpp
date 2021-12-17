// dllmain.cpp : Defines the entry point for the DLL application.
// https://stackoverflow.com/questions/38806602/notify-icon-click-win32-api-in-c
#include "pch.h"
#include <shellapi.h>
#include <strsafe.h>

#define APPWM_ICONNOTIFY (WM_APP + 1)

const LPCWSTR normalICON = L"C:\\chrome.ico";

HWND g_hWnd = NULL;
HICON hNormal = NULL;
WNDPROC wndProc = NULL;

LRESULT CALLBACK notifyCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    LRESULT result = CallWindowProc(wndProc, hwnd, uMsg, wParam, lParam);

    switch (uMsg)
    {

        case APPWM_ICONNOTIFY:
        {
            switch (lParam)
            {
            case WM_LBUTTONUP:
                WinExec("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe", SW_NORMAL);
                break;
            case WM_RBUTTONUP:
            
                break;
            }

        }

    }

    return result;
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        g_hWnd = FindWindow(L"Shell_TrayWnd", NULL);
        if (g_hWnd)
        {
            hNormal = (HICON)LoadImage(NULL, normalICON, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

            NOTIFYICONDATA nid = {};
            nid.cbSize = sizeof(nid);
            nid.hWnd = g_hWnd;
            nid.uID = 1;
            nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
            nid.uCallbackMessage = APPWM_ICONNOTIFY;
            nid.hIcon = hNormal;
            StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Chrome Quick Launch");

            Shell_NotifyIcon(NIM_ADD, &nid);

            wndProc = (WNDPROC)SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, (LONG_PTR)notifyCallback);

        }

        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

