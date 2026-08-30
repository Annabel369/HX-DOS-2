#include <windows.h>
#include <stdio.h>

typedef long HRESULT;
typedef unsigned long ULONG;
#define STDMETHODCALLTYPE __stdcall
#define S_OK 0

extern void vesa_init(void);
extern void vesa_draw_pixel(int x, int y, int color);
extern void vesa_clear(int color);

void WriteLog9(const char* text) {
    HANDLE hFile = CreateFileA("hx_d3d9.log", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE && hFile != NULL) {
        SetFilePointer(hFile, 0, NULL, FILE_END);
        DWORD written;
        WriteFile(hFile, text, lstrlenA(text), &written, NULL);
        CloseHandle(hFile);
    }
}

HRESULT STDMETHODCALLTYPE Dev9_Present(void* This, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const void* pDirtyRegion) {
    WriteLog9("[D3D9 Device] Present (Slot 17) chamado (troca de buffer)! DESENHANDO TESTE VESA!\r\n");
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
    WriteLog9("[D3D9 Device] Clear (Slot 43) chamado (limpar a tela preta)!\r\n");
    vesa_clear(Color);
    return S_OK;
}

HRESULT STDMETHODCALLTYPE Dev9_BeginScene(void* This) {
    WriteLog9("[D3D9 Device] BeginScene (Slot 41) chamado (preparando para desenhar poligonos)!\r\n");
    return S_OK;
}

HRESULT STDMETHODCALLTYPE Dev9_EndScene(void* This) {
    WriteLog9("[D3D9 Device] EndScene (Slot 42) chamado (terminou de desenhar poligonos)!\r\n");
    return S_OK;
}

HRESULT STDMETHODCALLTYPE DummyDev9_Slot0(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 0\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot1(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 1\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot2(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 2\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot3(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 3\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot4(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 4\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot5(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 5\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot6(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 6\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot7(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 7\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot8(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 8\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot9(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 9\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot10(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 10\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot11(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 11\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot12(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 12\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot13(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 13\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot14(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 14\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot15(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 15\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot16(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 16\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot18(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 18\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot19(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 19\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot20(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 20\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot21(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 21\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot22(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 22\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot23(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 23\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot24(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 24\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot25(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 25\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot26(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 26\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot27(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 27\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot28(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 28\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot29(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 29\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot30(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 30\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot31(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 31\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot32(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 32\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot33(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 33\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot34(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 34\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot35(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 35\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot36(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 36\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot37(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 37\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot38(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 38\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot39(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 39\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot40(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 40\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot44(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 44\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot45(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 45\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot46(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 46\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot47(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 47\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot48(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 48\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot49(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 49\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot50(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 50\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot51(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 51\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot52(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 52\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot53(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 53\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot54(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 54\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot55(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 55\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot56(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 56\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot57(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 57\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot58(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 58\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot59(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 59\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot60(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 60\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot61(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 61\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot62(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 62\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot63(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 63\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot64(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 64\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot65(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 65\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot66(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 66\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot67(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 67\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot68(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 68\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot69(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 69\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot70(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 70\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot71(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 71\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot72(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 72\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot73(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 73\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot74(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 74\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot75(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 75\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot76(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 76\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot77(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 77\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot78(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 78\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot79(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 79\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot80(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 80\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot81(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 81\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot82(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 82\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot83(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 83\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot84(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 84\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot85(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 85\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot86(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 86\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot87(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 87\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot88(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 88\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot89(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 89\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot90(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 90\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot91(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 91\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot92(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 92\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot93(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 93\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot94(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 94\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot95(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 95\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot96(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 96\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot97(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 97\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot98(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 98\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot99(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 99\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot100(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 100\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot101(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 101\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot102(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 102\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot103(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 103\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot104(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 104\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot105(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 105\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot106(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 106\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot107(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 107\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot108(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 108\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot109(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 109\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot110(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 110\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot111(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 111\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot112(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 112\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot113(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 113\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot114(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 114\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot115(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 115\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot116(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 116\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot117(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 117\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot118(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 118\r\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE DummyDev9_Slot119(void* This) {
    WriteLog9("[D3D9 Device] ALERTA: Funcao nao mapeada chamada! Slot: 119\r\n");
    return S_OK;
}
void* MyDevice9Vtbl[120];
void InitVtbl() {
    MyDevice9Vtbl[0] = DummyDev9_Slot0;
    MyDevice9Vtbl[1] = DummyDev9_Slot1;
    MyDevice9Vtbl[2] = DummyDev9_Slot2;
    MyDevice9Vtbl[3] = DummyDev9_Slot3;
    MyDevice9Vtbl[4] = DummyDev9_Slot4;
    MyDevice9Vtbl[5] = DummyDev9_Slot5;
    MyDevice9Vtbl[6] = DummyDev9_Slot6;
    MyDevice9Vtbl[7] = DummyDev9_Slot7;
    MyDevice9Vtbl[8] = DummyDev9_Slot8;
    MyDevice9Vtbl[9] = DummyDev9_Slot9;
    MyDevice9Vtbl[10] = DummyDev9_Slot10;
    MyDevice9Vtbl[11] = DummyDev9_Slot11;
    MyDevice9Vtbl[12] = DummyDev9_Slot12;
    MyDevice9Vtbl[13] = DummyDev9_Slot13;
    MyDevice9Vtbl[14] = DummyDev9_Slot14;
    MyDevice9Vtbl[15] = DummyDev9_Slot15;
    MyDevice9Vtbl[16] = DummyDev9_Slot16;
    MyDevice9Vtbl[17] = Dev9_Present;
    MyDevice9Vtbl[18] = DummyDev9_Slot18;
    MyDevice9Vtbl[19] = DummyDev9_Slot19;
    MyDevice9Vtbl[20] = DummyDev9_Slot20;
    MyDevice9Vtbl[21] = DummyDev9_Slot21;
    MyDevice9Vtbl[22] = DummyDev9_Slot22;
    MyDevice9Vtbl[23] = DummyDev9_Slot23;
    MyDevice9Vtbl[24] = DummyDev9_Slot24;
    MyDevice9Vtbl[25] = DummyDev9_Slot25;
    MyDevice9Vtbl[26] = DummyDev9_Slot26;
    MyDevice9Vtbl[27] = DummyDev9_Slot27;
    MyDevice9Vtbl[28] = DummyDev9_Slot28;
    MyDevice9Vtbl[29] = DummyDev9_Slot29;
    MyDevice9Vtbl[30] = DummyDev9_Slot30;
    MyDevice9Vtbl[31] = DummyDev9_Slot31;
    MyDevice9Vtbl[32] = DummyDev9_Slot32;
    MyDevice9Vtbl[33] = DummyDev9_Slot33;
    MyDevice9Vtbl[34] = DummyDev9_Slot34;
    MyDevice9Vtbl[35] = DummyDev9_Slot35;
    MyDevice9Vtbl[36] = DummyDev9_Slot36;
    MyDevice9Vtbl[37] = DummyDev9_Slot37;
    MyDevice9Vtbl[38] = DummyDev9_Slot38;
    MyDevice9Vtbl[39] = DummyDev9_Slot39;
    MyDevice9Vtbl[40] = DummyDev9_Slot40;
    MyDevice9Vtbl[41] = Dev9_BeginScene;
    MyDevice9Vtbl[42] = Dev9_EndScene;
    MyDevice9Vtbl[43] = Dev9_Clear;
    MyDevice9Vtbl[44] = DummyDev9_Slot44;
    MyDevice9Vtbl[45] = DummyDev9_Slot45;
    MyDevice9Vtbl[46] = DummyDev9_Slot46;
    MyDevice9Vtbl[47] = DummyDev9_Slot47;
    MyDevice9Vtbl[48] = DummyDev9_Slot48;
    MyDevice9Vtbl[49] = DummyDev9_Slot49;
    MyDevice9Vtbl[50] = DummyDev9_Slot50;
    MyDevice9Vtbl[51] = DummyDev9_Slot51;
    MyDevice9Vtbl[52] = DummyDev9_Slot52;
    MyDevice9Vtbl[53] = DummyDev9_Slot53;
    MyDevice9Vtbl[54] = DummyDev9_Slot54;
    MyDevice9Vtbl[55] = DummyDev9_Slot55;
    MyDevice9Vtbl[56] = DummyDev9_Slot56;
    MyDevice9Vtbl[57] = DummyDev9_Slot57;
    MyDevice9Vtbl[58] = DummyDev9_Slot58;
    MyDevice9Vtbl[59] = DummyDev9_Slot59;
    MyDevice9Vtbl[60] = DummyDev9_Slot60;
    MyDevice9Vtbl[61] = DummyDev9_Slot61;
    MyDevice9Vtbl[62] = DummyDev9_Slot62;
    MyDevice9Vtbl[63] = DummyDev9_Slot63;
    MyDevice9Vtbl[64] = DummyDev9_Slot64;
    MyDevice9Vtbl[65] = DummyDev9_Slot65;
    MyDevice9Vtbl[66] = DummyDev9_Slot66;
    MyDevice9Vtbl[67] = DummyDev9_Slot67;
    MyDevice9Vtbl[68] = DummyDev9_Slot68;
    MyDevice9Vtbl[69] = DummyDev9_Slot69;
    MyDevice9Vtbl[70] = DummyDev9_Slot70;
    MyDevice9Vtbl[71] = DummyDev9_Slot71;
    MyDevice9Vtbl[72] = DummyDev9_Slot72;
    MyDevice9Vtbl[73] = DummyDev9_Slot73;
    MyDevice9Vtbl[74] = DummyDev9_Slot74;
    MyDevice9Vtbl[75] = DummyDev9_Slot75;
    MyDevice9Vtbl[76] = DummyDev9_Slot76;
    MyDevice9Vtbl[77] = DummyDev9_Slot77;
    MyDevice9Vtbl[78] = DummyDev9_Slot78;
    MyDevice9Vtbl[79] = DummyDev9_Slot79;
    MyDevice9Vtbl[80] = DummyDev9_Slot80;
    MyDevice9Vtbl[81] = DummyDev9_Slot81;
    MyDevice9Vtbl[82] = DummyDev9_Slot82;
    MyDevice9Vtbl[83] = DummyDev9_Slot83;
    MyDevice9Vtbl[84] = DummyDev9_Slot84;
    MyDevice9Vtbl[85] = DummyDev9_Slot85;
    MyDevice9Vtbl[86] = DummyDev9_Slot86;
    MyDevice9Vtbl[87] = DummyDev9_Slot87;
    MyDevice9Vtbl[88] = DummyDev9_Slot88;
    MyDevice9Vtbl[89] = DummyDev9_Slot89;
    MyDevice9Vtbl[90] = DummyDev9_Slot90;
    MyDevice9Vtbl[91] = DummyDev9_Slot91;
    MyDevice9Vtbl[92] = DummyDev9_Slot92;
    MyDevice9Vtbl[93] = DummyDev9_Slot93;
    MyDevice9Vtbl[94] = DummyDev9_Slot94;
    MyDevice9Vtbl[95] = DummyDev9_Slot95;
    MyDevice9Vtbl[96] = DummyDev9_Slot96;
    MyDevice9Vtbl[97] = DummyDev9_Slot97;
    MyDevice9Vtbl[98] = DummyDev9_Slot98;
    MyDevice9Vtbl[99] = DummyDev9_Slot99;
    MyDevice9Vtbl[100] = DummyDev9_Slot100;
    MyDevice9Vtbl[101] = DummyDev9_Slot101;
    MyDevice9Vtbl[102] = DummyDev9_Slot102;
    MyDevice9Vtbl[103] = DummyDev9_Slot103;
    MyDevice9Vtbl[104] = DummyDev9_Slot104;
    MyDevice9Vtbl[105] = DummyDev9_Slot105;
    MyDevice9Vtbl[106] = DummyDev9_Slot106;
    MyDevice9Vtbl[107] = DummyDev9_Slot107;
    MyDevice9Vtbl[108] = DummyDev9_Slot108;
    MyDevice9Vtbl[109] = DummyDev9_Slot109;
    MyDevice9Vtbl[110] = DummyDev9_Slot110;
    MyDevice9Vtbl[111] = DummyDev9_Slot111;
    MyDevice9Vtbl[112] = DummyDev9_Slot112;
    MyDevice9Vtbl[113] = DummyDev9_Slot113;
    MyDevice9Vtbl[114] = DummyDev9_Slot114;
    MyDevice9Vtbl[115] = DummyDev9_Slot115;
    MyDevice9Vtbl[116] = DummyDev9_Slot116;
    MyDevice9Vtbl[117] = DummyDev9_Slot117;
    MyDevice9Vtbl[118] = DummyDev9_Slot118;
    MyDevice9Vtbl[119] = DummyDev9_Slot119;
}


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

    InitVtbl();

    WriteLog9("[D3D9] Direct3DCreate9 chamado. Devolvendo Objeto COM.\r\n");
    return &MyFakeD3D9;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}
