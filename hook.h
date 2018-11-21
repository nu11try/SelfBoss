#ifndef HOOK_H
#define HOOK_H

#include "hook_global.h"
#include <QObject>
#include <windows.h>

class HOOKSHARED_EXPORT Hook : public QObject {
    Q_OBJECT

public:
    Hook(QObject* parent = 0);

private:
    static int CALLBACK KeyboardProc(int nCode, DWORD wParam, DWORD lParam);
    static Hook* m_This;

signals:
    void hookEvent(int key);
};

#endif // HOOK_H
