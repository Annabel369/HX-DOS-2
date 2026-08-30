#include <windows.h>

// Definicoes basicas COM
typedef long HRESULT;
typedef unsigned long ULONG;
#define STDMETHODCALLTYPE __stdcall
#define S_OK 0
#define DI_OK 0
#define DIERR_NOTINITIALIZED 0x80040150
#define E_NOTIMPL 0x80004001

// Definicoes do DInput
typedef struct {
    DWORD dwSize;
    DWORD dwObjSize;
    DWORD dwFlags;
    DWORD dwDataSize;
    DWORD dwNumObjs;
} DIDATAFORMAT;

void WriteLog(const char* text) {
    HANDLE hFile = CreateFileA("hx_dinput8_log.txt", FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD written;
        WriteFile(hFile, text, lstrlenA(text), &written, NULL);
        CloseHandle(hFile);
    }
}

// -------------------------------------------------------------
// VTable e Estrutura para IDirectInputDevice8
// -------------------------------------------------------------
typedef struct IDirectInputDevice8Vtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(void* This, void* riid, void** ppvObj);
    ULONG (STDMETHODCALLTYPE *AddRef)(void* This);
    ULONG (STDMETHODCALLTYPE *Release)(void* This);
    HRESULT (STDMETHODCALLTYPE *GetCapabilities)(void* This, void* pdidc);
    HRESULT (STDMETHODCALLTYPE *EnumObjects)(void* This, void* lpCallback, void* pvRef, DWORD dwFlags);
    HRESULT (STDMETHODCALLTYPE *GetProperty)(void* This, void* rguidProp, void* pdip);
    HRESULT (STDMETHODCALLTYPE *SetProperty)(void* This, void* rguidProp, void* pdip);
    HRESULT (STDMETHODCALLTYPE *Acquire)(void* This);
    HRESULT (STDMETHODCALLTYPE *Unacquire)(void* This);
    HRESULT (STDMETHODCALLTYPE *GetDeviceState)(void* This, DWORD cbData, void* lpvData);
    HRESULT (STDMETHODCALLTYPE *GetDeviceData)(void* This, DWORD cbObjectData, void* rgdod, DWORD* pdwInOut, DWORD dwFlags);
    HRESULT (STDMETHODCALLTYPE *SetDataFormat)(void* This, const DIDATAFORMAT* lpdf);
    HRESULT (STDMETHODCALLTYPE *SetEventNotification)(void* This, HANDLE hEvent);
    HRESULT (STDMETHODCALLTYPE *SetCooperativeLevel)(void* This, HWND hwnd, DWORD dwFlags);
    // Para evitar crash, precisamos preencher a VTable com funcoes dummies que devolvam OK
    void* padding[100]; // Preenchimento seguro de slots
} IDirectInputDevice8Vtbl;

typedef struct IDirectInputDevice8 {
    IDirectInputDevice8Vtbl* lpVtbl;
} IDirectInputDevice8;

HRESULT STDMETHODCALLTYPE DIDevice_Acquire(void* This) {
    WriteLog("[DInput8 Device] Acquire (Teclado/Mouse ativado)\r\n");
    return DI_OK;
}

HRESULT STDMETHODCALLTYPE DIDevice_SetDataFormat(void* This, const DIDATAFORMAT* lpdf) {
    WriteLog("[DInput8 Device] SetDataFormat chamado\r\n");
    return DI_OK;
}

HRESULT STDMETHODCALLTYPE DIDevice_SetCooperativeLevel(void* This, HWND hwnd, DWORD dwFlags) {
    WriteLog("[DInput8 Device] SetCooperativeLevel chamado\r\n");
    return DI_OK;
}

HRESULT STDMETHODCALLTYPE DIDevice_GetDeviceState(void* This, DWORD cbData, void* lpvData) {
    // WriteLog("[DInput8 Device] GetDeviceState (lendo botoes...)\r\n");
    
    // A MAGICA: Limpamos o buffer dizendo que NENHUMA TECLA ou BOTAO esta pressionado
    if (lpvData != NULL && cbData > 0) {
        // Preenche de zeros
        char* buf = (char*)lpvData;
        DWORD i;
        for (i = 0; i < cbData; i++) {
            buf[i] = 0;
        }
    }
    return DI_OK;
}

HRESULT STDMETHODCALLTYPE DIDevice_QueryInterface(void* This, void* riid, void** ppvObj) {
    return DI_OK;
}

ULONG STDMETHODCALLTYPE DIDevice_AddRef(void* This) { return 1; }
ULONG STDMETHODCALLTYPE DIDevice_Release(void* This) { return 0; }

// Instanciando a VTable do Device
IDirectInputDevice8Vtbl MyDIDeviceVtbl = {
    DIDevice_QueryInterface,
    DIDevice_AddRef,
    DIDevice_Release,
    NULL, // GetCapabilities
    NULL, // EnumObjects
    NULL, // GetProperty
    NULL, // SetProperty
    DIDevice_Acquire,
    NULL, // Unacquire
    DIDevice_GetDeviceState,
    NULL, // GetDeviceData
    DIDevice_SetDataFormat,
    NULL, // SetEventNotification
    DIDevice_SetCooperativeLevel
};

IDirectInputDevice8 MyFakeDIDevice = { &MyDIDeviceVtbl };

// -------------------------------------------------------------
// VTable e Estrutura para IDirectInput8
// -------------------------------------------------------------
typedef struct IDirectInput8Vtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(void* This, void* riid, void** ppvObj);
    ULONG (STDMETHODCALLTYPE *AddRef)(void* This);
    ULONG (STDMETHODCALLTYPE *Release)(void* This);
    HRESULT (STDMETHODCALLTYPE *CreateDevice)(void* This, const void* rguid, IDirectInputDevice8** lplpDirectInputDevice, void* punkOuter);
    HRESULT (STDMETHODCALLTYPE *EnumDevices)(void* This, DWORD dwDevType, void* lpCallback, void* pvRef, DWORD dwFlags);
    HRESULT (STDMETHODCALLTYPE *GetDeviceStatus)(void* This, const void* rguidInstance);
    HRESULT (STDMETHODCALLTYPE *RunControlPanel)(void* This, HWND hwndOwner, DWORD dwFlags);
    HRESULT (STDMETHODCALLTYPE *Initialize)(void* This, HINSTANCE hinst, DWORD dwVersion);
} IDirectInput8Vtbl;

typedef struct IDirectInput8 {
    IDirectInput8Vtbl* lpVtbl;
} IDirectInput8;

HRESULT STDMETHODCALLTYPE DI8_CreateDevice(void* This, const void* rguid, IDirectInputDevice8** lplpDirectInputDevice, void* punkOuter) {
    WriteLog("[DInput8] ==========================================\r\n");
    WriteLog("[DInput8] Jogo solicitou a CRIACAO do MOUSE/TECLADO!\r\n");
    WriteLog("[DInput8] Devolvendo hardware virtual fantasma...\r\n");
    WriteLog("[DInput8] ==========================================\r\n");
    
    if (lplpDirectInputDevice) {
        *lplpDirectInputDevice = &MyFakeDIDevice;
    }
    return DI_OK;
}

// Stub para QueryInterface etc
HRESULT STDMETHODCALLTYPE DI8_QueryInterface(void* This, void* riid, void** ppvObj) {
    return DI_OK;
}
ULONG STDMETHODCALLTYPE DI8_AddRef(void* This) { return 1; }
ULONG STDMETHODCALLTYPE DI8_Release(void* This) { return 0; }

// Instanciando a VTable do DirectInput8
IDirectInput8Vtbl MyDI8Vtbl = {
    DI8_QueryInterface,
    DI8_AddRef,
    DI8_Release,
    DI8_CreateDevice,
    NULL, // EnumDevices
    NULL, // GetDeviceStatus
    NULL, // RunControlPanel
    NULL  // Initialize
};

IDirectInput8 MyFakeDI8 = { &MyDI8Vtbl };

// -------------------------------------------------------------
// Exportacao Principal
// -------------------------------------------------------------
HRESULT __stdcall DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, void* riidltf, void** ppvOut, void* punkOuter) {
    WriteLog("[DInput8] DirectInput8Create chamado. Devolvendo Objeto COM Falso.\r\n");
    
    if (ppvOut) {
        *ppvOut = &MyFakeDI8;
    }
    
    return DI_OK; 
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
