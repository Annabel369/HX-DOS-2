# Projeto HX DOS 2 🚀

<img width="932" height="270" alt="image" src="https://github.com/user-attachments/assets/0eb3eeb2-1b9f-4195-8ec5-75e17112be46" />


Bem-vindo ao projeto **HX DOS 2**! Este repositório nasceu de uma ideia insanamente ambiciosa: **executar jogos complexos nativos de Windows (Win32), como *Grand Theft Auto: Vice City*, puramente no MS-DOS!**

Utilizando o *HX DOS Extender* de Japheth como nossa base e motor DPMI, nós construímos uma arquitetura de "Wrappers DLL" capaz de interceptar as requisições que os jogos fazem para o DirectX e redirecioná-las para a nossa própria implementação em C e Assembly.

## 🎯 O Que Conquistamos na Fase 1 (PoC)?
Durante a primeira Prova de Conceito, provamos que a teoria é sólida:
- **Gráficos (d3d8.dll)**: Criamos uma DLL COM falsa do DirectX 8 que intercepta a requisição do `Direct3DCreate8`, enganando o motor RenderWare do GTA VC para que não travasse na inicialização gráfica. Integramos isso a um esqueleto de rastreador (Software Rasterizer) em Assembly que escreve diretamente na memória Linear Frame Buffer (LFB) do VESA no DOS.
- **Controles (dinput8.dll)**: Para evitar o colapso do sistema (Page Fault) quando o jogo lia o hardware do usuário, criamos uma interface COM `IDirectInputDevice8` que simula um Mouse Fantasma. Ele alimenta a memória do jogo com zeros perfeitos, evitando o fechamento instantâneo por *nullptr*.
- **Fusão com HXGUI**: Incorporamos o poderoso projeto oficial HXGUI (`winmm.dll`, `dsound.dll`, etc.) ao nosso sistema de arquivos, resolvendo imediatamente o abismo de dependências multimídia de jogos AAA dos anos 2000.

O resultado? **O GTA Vice City carregou a janela no MS-DOS sem travar no clique!**

## 📂 Estrutura do Projeto

### 🔧 Wrappers em C (DirectX Interceptors)
* `d3d8.c` / `d3d8.def` / `d3d8.dll`: A nossa versão customizada do Direct3D 8. Contém as estruturas VTable do COM C++ simuladas em C puro.
* `dinput8.c` / `dinput8.def` / `dinput8.dll`: A implementação customizada do DirectInput 8 para lidar com cliques de hardware via `IDirectInputDevice8`.
* `test_d3d.c` / `test_d3d.exe`: Um pequeno aplicativo nativo Win32 (sem dependência do C Runtime) que testa o carregamento da nossa falsa `d3d8.dll` dentro do DOSBox usando o `dpmild32.exe`.

### 🖥️ Motor Gráfico VESA (Assembly)
* `vesalfb.asm`: Uma prova de conceito em modo Real/Unreal que escreve gradientes lisos a 800x600 utilizando o buffer linear da placa de vídeo (sem bank switching).
* `vesadraw.asm`: A versão antiga 16-bits que usava Bank Switching.
* `vesa_engine.asm`: O elo de ligação! Funções gráficas exportadas (`_vesa_draw_pixel`) que são chamadas de dentro do C para desenhar na tela preta.

## 🛠️ Como Compilar
Tudo foi feito para ser compilado no Linux com ferramentas Cross-Platform padrão:

**Para o Assembly:**
```bash
nasm -f elf32 vesa_engine.asm -o vesa_engine.o
```

**Para as DLLs (Cross-Compiler MinGW):**
```bash
i686-w64-mingw32-gcc -shared -nostdlib -o d3d8.dll d3d8.c vesa_engine.o d3d8.def -lkernel32 -Wl,--entry=_DllMain@12
i686-w64-mingw32-gcc -shared -nostdlib -o dinput8.dll dinput8.c dinput8.def -lkernel32 -Wl,--entry=_DllMain@12
```

## 🚀 Próximos Passos
1. **O Desafio do Rastreador (Software Rasterizer)**: Conectar o método `IDirect3DDevice8::Clear` ou `DrawPrimitive` com a nossa engine `vesa_engine.asm` para vermos os primeiros polígonos reais gerados pela CPU em vez de uma tela preta.
2. **Suporte de Entrada**: Mapear as chamadas reais da interrupção INT 33h do mouse do DOS para o buffer de zeros da função `GetDeviceState` no `dinput8.c`.

---
*Criado com orgulho em uma maratona de engenharia reversa no MS-DOS!*
