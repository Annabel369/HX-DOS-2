#include <windows.h>
long __stdcall lineAnswer(void* hCall, const char* lpUserUserInfo, DWORD dwSize) { return 0; }
long __stdcall lineMakeCall(void* hLine, void** lphCall, const char* lpszDestAddress, DWORD dwCountryCode, const void* const lpCallParams) { return 0; }
long __stdcall lineGetID(void* hLine, DWORD dwAddressID, void* hCall, DWORD dwSelect, void* lpDeviceID, const char* lpszDeviceClass) { return 0; }
long __stdcall lineClose(void* hLine) { return 0; }
long __stdcall lineNegotiateAPIVersion(void* hLineApp, DWORD dwDeviceID, DWORD dwAPILowVersion, DWORD dwAPIHighVersion, DWORD* lpdwAPIVersion, void* lpExtensionID) { return 0; }
long __stdcall lineOpen(void* hLineApp, DWORD dwDeviceID, void** lphLine, DWORD dwAPIVersion, DWORD dwExtVersion, DWORD dwCallbackInstance, DWORD dwPrivileges, DWORD dwMediaModes, const void* const lpCallParams) { return 0; }
long __stdcall lineGetDevCaps(void* hLineApp, DWORD dwDeviceID, DWORD dwAPIVersion, DWORD dwExtVersion, void* lpLineDevCaps) { return 0; }
long __stdcall lineInitialize(void** lphLineApp, HINSTANCE hInstance, void* lpfnCallback, const char* lpszAppName, DWORD* lpdwNumDevs) { return 0; }
long __stdcall lineShutdown(void* hLineApp) { return 0; }
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
