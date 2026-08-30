#include <windows.h>
unsigned char __stdcall Netbios(struct _NCB* pncb) {
    return 0; // NRC_GOODRET
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
