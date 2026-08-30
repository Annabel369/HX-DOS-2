#include <windows.h>

// Definicoes basicas COM
typedef long HRESULT;
typedef unsigned long ULONG;
#define STDMETHODCALLTYPE __stdcall
#define S_OK 0
#define E_NOTIMPL 0x80004001

// Funcoes Assembly externas
extern void vesa_init(void);
extern void vesa_draw_pixel(int x, int y, int color);

// Funcao auxiliar de Log
void WriteLog(const char* text) {
    HANDLE hFile = CreateFileA("hx_d3d8_log.txt", FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD written;
        WriteFile(hFile, text, lstrlenA(text), &written, NULL);
        CloseHandle(hFile);
    }
}

// -------------------------------------------------------------
// VTable e Estrutura para IDirect3DDevice8
// -------------------------------------------------------------
typedef struct IDirect3DDevice8Vtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(void* This, void* riid, void** ppvObj);
    ULONG (STDMETHODCALLTYPE *AddRef)(void* This);
    ULONG (STDMETHODCALLTYPE *Release)(void* This);
    HRESULT (STDMETHODCALLTYPE *TestCooperativeLevel)(void* This);
    UINT (STDMETHODCALLTYPE *GetAvailableTextureMem)(void* This);
    HRESULT (STDMETHODCALLTYPE *ResourceManagerDiscardBytes)(void* This, DWORD Bytes);
    HRESULT (STDMETHODCALLTYPE *GetDirect3D)(void* This, void** ppD3D8);
    HRESULT (STDMETHODCALLTYPE *GetDeviceCaps)(void* This, void* pCaps);
    HRESULT (STDMETHODCALLTYPE *GetDisplayMode)(void* This, void* pMode);
    HRESULT (STDMETHODCALLTYPE *GetCreationParameters)(void* This, void* pParameters);
    HRESULT (STDMETHODCALLTYPE *SetCursorProperties)(void* This, UINT XHotSpot, UINT YHotSpot, void* pCursorBitmap);
    void (STDMETHODCALLTYPE *SetCursorPosition)(void* This, int X, int Y, DWORD Flags);
    BOOL (STDMETHODCALLTYPE *ShowCursor)(void* This, BOOL bShow);
    HRESULT (STDMETHODCALLTYPE *CreateAdditionalSwapChain)(void* This, void* pPresentationParameters, void** pSwapChain);
    HRESULT (STDMETHODCALLTYPE *GetSwapChain)(void* This, void** pSwapChain);
    UINT (STDMETHODCALLTYPE *GetNumberOfSwapChains)(void* This);
    HRESULT (STDMETHODCALLTYPE *Reset)(void* This, void* pPresentationParameters);
    HRESULT (STDMETHODCALLTYPE *Present)(void* This, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const void* pDirtyRegion);
    // ... muitos outros metodos. O GTA geralmente usa ate o GetBackBuffer/Clear/BeginScene.
    // Vamos preencher as slots essenciais:
    void* padding[18]; // pulando slots nao essenciais para este teste
    HRESULT (STDMETHODCALLTYPE *Clear)(void* This, DWORD Count, const void* pRects, DWORD Flags, DWORD Color, float Z, DWORD Stencil);
    // ...
} IDirect3DDevice8Vtbl;

typedef struct IDirect3DDevice8 {
    IDirect3DDevice8Vtbl* lpVtbl;
} IDirect3DDevice8;

// Implementacao de funcoes do Device
HRESULT STDMETHODCALLTYPE Device_Present(void* This, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const void* pDirtyRegion) {
    WriteLog("[D3D8 Device] Present chamado (troca de buffer)!\r\n");
    return S_OK;
}

HRESULT STDMETHODCALLTYPE Device_Clear(void* This, DWORD Count, const void* pRects, DWORD Flags, DWORD Color, float Z, DWORD Stencil) {
    WriteLog("[D3D8 Device] Clear chamado (limpar a tela preta)!\r\n");
    // Aqui chamaremos a VESA!
    vesa_draw_pixel(0, 0, Color);
    return S_OK;
}

// Preenchendo a VTable falsa do Device
IDirect3DDevice8Vtbl MyDeviceVtbl = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    Device_Present, // O 17o metodo e o Present
    {0}, 
    Device_Clear // Este seria o metodo Clear no DX8
};

IDirect3DDevice8 MyFakeDevice = { &MyDeviceVtbl };


// -------------------------------------------------------------
// VTable e Estrutura para IDirect3D8
// -------------------------------------------------------------
typedef struct IDirect3D8Vtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(void* This, void* riid, void** ppvObj);
    ULONG (STDMETHODCALLTYPE *AddRef)(void* This);
    ULONG (STDMETHODCALLTYPE *Release)(void* This);
    HRESULT (STDMETHODCALLTYPE *RegisterSoftwareDevice)(void* This, void* pInitializeFunction);
    UINT (STDMETHODCALLTYPE *GetAdapterCount)(void* This);
    HRESULT (STDMETHODCALLTYPE *GetAdapterIdentifier)(void* This, UINT Adapter, DWORD Flags, void* pIdentifier);
    UINT (STDMETHODCALLTYPE *GetAdapterModeCount)(void* This, UINT Adapter);
    HRESULT (STDMETHODCALLTYPE *EnumAdapterModes)(void* This, UINT Adapter, UINT Mode, void* pMode);
    HRESULT (STDMETHODCALLTYPE *GetAdapterDisplayMode)(void* This, UINT Adapter, void* pMode);
    HRESULT (STDMETHODCALLTYPE *CheckDeviceType)(void* This, UINT Adapter, int CheckType, int DisplayFormat, int BackBufferFormat, BOOL Windowed);
    HRESULT (STDMETHODCALLTYPE *CheckDeviceFormat)(void* This, UINT Adapter, int DeviceType, int AdapterFormat, DWORD Usage, int RType, int CheckFormat);
    HRESULT (STDMETHODCALLTYPE *CheckDeviceMultiSampleType)(void* This, UINT Adapter, int DeviceType, int SurfaceFormat, BOOL Windowed, int MultiSampleType);
    HRESULT (STDMETHODCALLTYPE *CheckDepthStencilMatch)(void* This, UINT Adapter, int DeviceType, int AdapterFormat, int RenderTargetFormat, int DepthStencilFormat);
    HRESULT (STDMETHODCALLTYPE *CheckDeviceFormatConversion)(void* This, UINT Adapter, int DeviceType, int SourceFormat, int TargetFormat);
    HRESULT (STDMETHODCALLTYPE *GetDeviceCaps)(void* This, UINT Adapter, int DeviceType, void* pCaps);
    HMONITOR (STDMETHODCALLTYPE *GetAdapterMonitor)(void* This, UINT Adapter);
    HRESULT (STDMETHODCALLTYPE *CreateDevice)(void* This, UINT Adapter, int DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, void* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface);
} IDirect3D8Vtbl;

typedef struct IDirect3D8 {
    IDirect3D8Vtbl* lpVtbl;
} IDirect3D8;

// Implementacoes para IDirect3D8
HRESULT STDMETHODCALLTYPE D3D8_CreateDevice(void* This, UINT Adapter, int DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, void* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface) {
    WriteLog("[D3D8] ==========================================\r\n");
    WriteLog("[D3D8] Jogo solicitou a CRIACAO da PLACA DE VIDEO!\r\n");
    WriteLog("[D3D8] Devolvendo a placa virtual falsa...\r\n");
    WriteLog("[D3D8] ==========================================\r\n");
    
    vesa_init(); // Prepara o terreno VESA Assembly
    
    if (ppReturnedDeviceInterface) {
        *ppReturnedDeviceInterface = &MyFakeDevice;
    }
    return S_OK; // D3D_OK
}

// Outros metodos dummy...
UINT STDMETHODCALLTYPE D3D8_GetAdapterCount(void* This) { return 1; }

IDirect3D8Vtbl MyD3D8Vtbl = {
    NULL, NULL, NULL, NULL, 
    D3D8_GetAdapterCount, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    D3D8_CreateDevice
};

IDirect3D8 MyFakeD3D8 = { &MyD3D8Vtbl };

// -------------------------------------------------------------
// Exportacao Principal
// -------------------------------------------------------------
void* __stdcall Direct3DCreate8(UINT SDKVersion) {
    WriteLog("[D3D8] Direct3DCreate8 chamado. Devolvendo Objeto COM.\r\n");
    return &MyFakeD3D8;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
