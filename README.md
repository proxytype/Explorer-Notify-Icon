# Explorer Notify Icon
create notification icon in explorer.exe by injection dll.

![alt text](https://raw.githubusercontent.com/proxytype/Explorer-Notify-Icon/main/notifyicon.gif)

Inject dll to explorer.exe, find the handle to "Shell_TrayWnd" and create new NOTIFYICONDATA structure,
listen to notifiy icon clicks events as part of windows procedure (WNDPROC).

WIN32 Functions:

* FindWindow
* Shell_NotifyIcon
* LoadImage
* CallWindowProc
* WinExec
