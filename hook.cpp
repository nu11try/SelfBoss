#include "hook.h"

Hook* Hook::m_This;

int CALLBACK Hook::KeyboardProc(int nCode, DWORD wParam, DWORD lParam)
{
    switch (wParam) {
    case WM_KEYDOWN: {
        KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

        Hook::m_This->hookEvent(kbdStruct.vkCode);
        break;
    }
    default:
        break;
    }

    return 0;
}

Hook::Hook(QObject* parent)
    : QObject(parent)
{
    m_This = this;
    SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)&KeyboardProc, GetModuleHandle(0), 0);
}
