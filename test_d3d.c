#include <windows.h>

// Definicao do ponteiro da funcao que vamos carregar
typedef void* (__stdcall *PFN_Direct3DCreate8)(UINT SDKVersion);

// Funcao auxiliar para imprimir na tela sem o C Runtime (msvcrt.dll)
void Print(const char* text) {
    DWORD written;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), text, lstrlenA(text), &written, NULL);
}

// Em programas puros Win32 sem C Runtime, a entrada e mainCRTStartup ou WinMainCRTStartup
void __cdecl mainCRTStartup() {
    Print("Iniciando test_d3d.exe (Simulador de jogo Win32)\r\n");
    Print("Tentando carregar d3d8.dll...\r\n");

    HMODULE hMod = LoadLibraryA("d3d8.dll");
    
    if (hMod == NULL) {
        Print("ERRO FATAL: Nao foi possivel encontrar d3d8.dll!\r\n");
        ExitProcess(1);
    }
    Print("SUCESSO: d3d8.dll carregada na memoria!\r\n");

    PFN_Direct3DCreate8 pDirect3DCreate8 = (PFN_Direct3DCreate8)GetProcAddress(hMod, "Direct3DCreate8");
    
    if (pDirect3DCreate8 == NULL) {
        Print("ERRO FATAL: Funcao Direct3DCreate8 nao encontrada na DLL!\r\n");
        FreeLibrary(hMod);
        ExitProcess(1);
    }
    Print("SUCESSO: Endereco da funcao Direct3DCreate8 encontrado!\r\n");

    Print("Chamando Direct3DCreate8...\r\n");
    void* pD3D = pDirect3DCreate8(220); 
    
    if (pD3D == NULL) {
        Print("Retornou NULL. (Esperado para nosso teste).\r\n");
        Print("Verifique se hx_d3d8_log.txt foi criado!\r\n");
    }

    FreeLibrary(hMod);
    Print("Teste concluido com sucesso.\r\n");
    ExitProcess(0);
}
