#include <windows.h>

typedef long HRESULT;
typedef unsigned long ULONG;
#define STDMETHODCALLTYPE __stdcall
#define S_OK 0

extern void vesa_init(void);
extern void vesa_draw_pixel(int x, int y, int color);

void WriteLog9(const char* text) {
    HANDLE hFile = CreateFileA("hx_d3d9_log.txt", FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD written;
        WriteFile(hFile, text, lstrlenA(text), &written, NULL);
        CloseHandle(hFile);
    }
}

HRESULT STDMETHODCALLTYPE Dev9_Present(void* This, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const void* pDirtyRegion) {
    WriteLog9("[D3D9 Device] Present chamado (troca de buffer)!\r\n");
    return S_OK;
}

HRESULT STDMETHODCALLTYPE Dev9_Clear(void* This, DWORD Count, const void* pRects, DWORD Flags, DWORD Color, float Z, DWORD Stencil) {
    WriteLog9("[D3D9 Device] Clear chamado (limpar a tela preta)!\r\n");
    vesa_draw_pixel(0, 0, Color);
    return S_OK;
}

HRESULT STDMETHODCALLTYPE DummyDev9() { 
    return S_OK; 
}

void* MyDevice9Vtbl[120];

typedef struct {
    void** lpVtbl;
} IDirect3DDevice9;

IDirect3DDevice9 MyFakeDevice9 = { MyDevice9Vtbl };

HRESULT STDMETHODCALLTYPE D3D9_CreateDevice(void* This, UINT Adapter, int DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, void* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface) {
    WriteLog9("[D3D9] ==========================================\r\n");
    WriteLog9("[D3D9] Jogo solicitou a CRIACAO da PLACA DE VIDEO DX9!\r\n");
    WriteLog9("[D3D9] Devolvendo a placa virtual falsa...\r\n");
    WriteLog9("[D3D9] ==========================================\r\n");
    
    vesa_init();
    
    if (ppReturnedDeviceInterface) {
        *ppReturnedDeviceInterface = &MyFakeDevice9;
    }
    return S_OK;
}

UINT STDMETHODCALLTYPE D3D9_GetAdapterCount(void* This) { return 1; }

HRESULT STDMETHODCALLTYPE DummyD3D9() { 
    return S_OK; 
}

void* MyD3D9Vtbl[18];

typedef struct {
    void** lpVtbl;
} IDirect3D9;

IDirect3D9 MyFakeD3D9 = { MyD3D9Vtbl };

void* __stdcall Direct3DCreate9(UINT SDKVersion) {
    int i;
    for(i=0; i<18; i++) MyD3D9Vtbl[i] = DummyD3D9;
    MyD3D9Vtbl[4] = D3D9_GetAdapterCount;
    MyD3D9Vtbl[16] = D3D9_CreateDevice;

    for(i=0; i<120; i++) MyDevice9Vtbl[i] = DummyDev9;
    MyDevice9Vtbl[17] = Dev9_Present;
    MyDevice9Vtbl[43] = Dev9_Clear;

    WriteLog9("[D3D9] Direct3DCreate9 chamado. Devolvendo Objeto COM.\r\n");
    return &MyFakeD3D9;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
