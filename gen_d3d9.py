import os

file_path = "d3d9.c"

# We keep the original includes and custom implementations
header = """#include <windows.h>
#include <stdio.h>

typedef long HRESULT;
typedef unsigned long ULONG;
#define STDMETHODCALLTYPE __stdcall
#define S_OK 0

extern void vesa_init(void);
extern void vesa_draw_pixel(int x, int y, int color);
extern void vesa_clear(int color);

void WriteLog9(const char* text) {
    HANDLE hFile = CreateFileA("hx_d3d9.log", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE && hFile != NULL) {
        SetFilePointer(hFile, 0, NULL, FILE_END);
        DWORD written;
        WriteFile(hFile, text, lstrlenA(text), &written, NULL);
        CloseHandle(hFile);
    }
}

HRESULT STDMETHODCALLTYPE Dev9_Present(void* This, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const void* pDirtyRegion) {
    WriteLog9("[D3D9 Device] Present (Slot 17) chamado (troca de buffer)! DESENHANDO TESTE VESA!\\r\\n");
    int x, y;
    for(y = 0; y < 600; y++) {
        for(x = 0; x < 800; x++) {
            int r = (x ^ y) & 0xFF;
            int b = (x | y) & 0xFF;
            vesa_draw_pixel(x, y, (r << 16) | b);
        }
    }
    return S_OK;
}

HRESULT STDMETHODCALLTYPE Dev9_Clear(void* This, DWORD Count, const void* pRects, DWORD Flags, DWORD Color, float Z, DWORD Stencil) {
    WriteLog9("[D3D9 Device] Clear (Slot 43) chamado (limpar a tela preta)!\\r\\n");
    vesa_clear(Color);
    return S_OK;
}

HRESULT STDMETHODCALLTYPE Dev9_BeginScene(void* This) {
    WriteLog9("[D3D9 Device] BeginScene (Slot 41) chamado (preparando para desenhar poligonos)!\\r\\n");
    return S_OK;
}

HRESULT STDMETHODCALLTYPE Dev9_EndScene(void* This) {
    WriteLog9("[D3D9 Device] EndScene (Slot 42) chamado (terminou de desenhar poligonos)!\\r\\n");
    return S_OK;
}

"""

dummies = ""
for i in range(120):
    if i not in [17, 41, 42, 43]:
        dummies += f"""HRESULT STDMETHODCALLTYPE DummyDev9_Slot{i}(void* This) {{
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: {i}\\r\\n");
    return S_OK;
}}
"""

vtable_decl = "void* MyDevice9Vtbl[120];\n"
vtable_init = "void InitVtbl() {\n"
for i in range(120):
    if i == 17:
        vtable_init += "    MyDevice9Vtbl[17] = Dev9_Present;\n"
    elif i == 41:
        vtable_init += "    MyDevice9Vtbl[41] = Dev9_BeginScene;\n"
    elif i == 42:
        vtable_init += "    MyDevice9Vtbl[42] = Dev9_EndScene;\n"
    elif i == 43:
        vtable_init += "    MyDevice9Vtbl[43] = Dev9_Clear;\n"
    else:
        vtable_init += f"    MyDevice9Vtbl[{i}] = DummyDev9_Slot{i};\n"
vtable_init += "}\n\n"

footer = """
typedef struct {
    void** lpVtbl;
} IDirect3DDevice9;

IDirect3DDevice9 MyFakeDevice9 = { MyDevice9Vtbl };

HRESULT STDMETHODCALLTYPE D3D9_CreateDevice(void* This, UINT Adapter, int DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, void* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface) {
    WriteLog9("[D3D9] ==========================================\\r\\n");
    WriteLog9("[D3D9] Jogo solicitou a CRIACAO da PLACA DE VIDEO DX9!\\r\\n");
    WriteLog9("[D3D9] Devolvendo a placa virtual falsa...\\r\\n");
    WriteLog9("[D3D9] ==========================================\\r\\n");
    
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

    InitVtbl();

    WriteLog9("[D3D9] Direct3DCreate9 chamado. Devolvendo Objeto COM.\\r\\n");
    return &MyFakeD3D9;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
"""

with open(file_path, "w") as f:
    f.write(header + dummies + vtable_decl + vtable_init + footer)

print("d3d9.c gerado com sucesso!")
