# Projeto MS-DOS 8 🚀 (Codinome: DOS-WINE)

Bem-vindo ao projeto **MS-DOS 8**! Este repositório é o núcleo de uma ideia insanamente ambiciosa: **construir um Sistema Operacional bootável baseado em DOS, capaz de rodar jogos complexos nativos de Windows XP (como *Grand Theft Auto: Vice City*), utilizando aceleração 3D por Software e Wrappers DirectX, direto pelo terminal!**

Esqueça o Windows bugado, drivers piratas e chaves de registro. Aqui nós controlamos o hardware!

## 👑 A Base Absoluta: MS-DOS 7.10 (China DOS Union)
**AVISO TÉCNICO IMPORTANTE PARA TODOS OS DESENVOLVEDORES:**
Sob nenhuma hipótese confundam a fundação deste projeto! Nós **NÃO** estamos rodando no DOSBox purista ou no DOS 6.22! 
Todo o código deste repositório foi construído, testado e validado em cima do lendário **MS-DOS 7.10 extraído do Windows 98 SE pela China DOS Union (CDU)**. 

Por que o MS-DOS 7.10?
- Suporte nativo e perfeito a **FAT32** e LBA (necessário para os 2GB+ de assets do GTA VC).
- Suporte nativo a **LFN (Long File Names)**, impedindo que as pastas dos jogos de Windows se corrompam.
- Gerenciamento agressivo de memória em Modo Real/Irreal (Unreal Mode).

## 🎯 O Que é o "DOS-WINE"?
Assim como a Steam tem o Proton e o Linux tem o Wine ("Wine Is Not an Emulator"), o projeto **MS-DOS 8** atua fornecendo as suas próprias DLLs falsas (Wrappers) para emular as APIs do Windows 2000/XP.

Quando um jogo pede para renderizar um modelo 3D, ele chama a `d3d8.dll` achando que está falando com a Microsoft. A nossa `d3d8.dll` intercepta os polígonos, converte a matemática e envia as requisições de renderização direto para a nossa **Engine VESA Assembly de Baixo Nível (cube3d.asm)**!

## 📂 Estrutura Técnica do Repositório

### 1. Wrappers em C (As DLLs Falsas do Windows)
* `d3d8.c` / `d3d8.dll`: A nossa versão customizada e interceptadora do Direct3D 8. Contém as estruturas VTable do COM C++ simuladas em C puro. Redireciona chamadas de renderização para a VESA.
* `dinput8.c` / `dinput8.dll`: O nosso Wrapper do DirectInput 8. Simula mouses e teclados "fantasmas" injetando zeros no buffer dos jogos para evitar *Page Faults* na ausência de drivers de Windows.
* `test_d3d.c`: Um aplicativo de teste Win32 nativo para validar as chamadas COM da nossa DLL dentro do DOS usando `DPMILD32.EXE`.

### 2. A Engine Gráfica Nativa (Assembly x86)
* `cube3d.asm` (**A Joia da Coroa**): Implementação definitiva de renderização 3D nativa e algoritmos matemáticos (como Bresenham) em Assembly.
    - Utiliza **Unreal Mode 32-bits** para quebrar a barreira dos 64KB de memória do MS-DOS.
    - **Segredo de Ouro**: A segmentação de memória linear (4GB Limit) é injetada no registrador `FS`, em vez do tradicional `ES`. Isso blinda a Engine contra crashes da BIOS e do DOSBox (`Illegal descriptor type 10`), garantindo estabilidade infinita.
    - Acesso direto ao Linear Frame Buffer (LFB) da placa de vídeo via VESA BIOS Extension (Modo 0x114 LFB).

## 🛠️ Como Compilar o "DOS-WINE"

Nossas DLLs são compiladas utilizando o compilador C Win32 (MinGW) para manter compatibilidade absoluta de ABI (Application Binary Interface) com os jogos originais.

**Para a Engine VESA (Objeto C):**
```bash
nasm -f elf32 vesa_engine.asm -o vesa_engine.o
```

**Para as DLLs Tradutoras (MinGW):**
```bash
i686-w64-mingw32-gcc -shared -nostdlib -o d3d8.dll d3d8.c vesa_engine.o d3d8.def -lkernel32 -Wl,--entry=_DllMain@12
i686-w64-mingw32-gcc -shared -nostdlib -o dinput8.dll dinput8.c dinput8.def -lkernel32 -Wl,--entry=_DllMain@12
```

## 🚀 Próximos Passos na Estrada de Tijolos Amarelos
1. **Fundir as Duas Metades**: Lincar os comandos `DrawPrimitive` capturados pelo `d3d8.c` com a Engine de rastreio de polígonos e Bresenham do `cube3d.asm`.
2. **Cubo 3D Giratório**: Substituir a tela preta e o "X" de teste pelo primeiro triângulo geométrico projetado e rotacionado pela nossa própria matemática 3D no DOS.
3. **Boot Loader Final**: Unificar tudo em um `START.BAT` (ou interface dedicada) onde as Splashes Screens (como a da Rockstar North) carregam suavemente direto da linha de comando do MS-DOS 7.10.

# Projeto HX DOS 2 🚀 MS-DOS 7.10


<img width="791" height="627" alt="image" src="https://github.com/user-attachments/assets/66a50cfc-d0b7-4b4d-95b1-6f1ceb62644c" />

Sensacional! O screenshot mostra que tudo funcionou com perfeição matemática. A linha vermelha corta exatamente o eixo Y=300, a verde o eixo X=400, e o quadrado azul está perfeitamente centralizado.

Nós acabamos de construir a fundação absoluta de uma Engine Gráfica. Qualquer jogo 3D (desde o Doom até o GTA Vice City) baseia-se exatamente nessa premissa: escrever cores em um buffer de memória linear de forma extremamente rápida.


<img width="932" height="270" alt="image" src="https://github.com/user-attachments/assets/0eb3eeb2-1b9f-4195-8ec5-75e17112be46" />


Bem-vindo ao projeto **HX DOS 2**! Este repositório nasceu de uma ideia insanamente ambiciosa: **executar jogos complexos nativos de Windows (Win32), como *Grand Theft Auto: Vice City*, puramente no MS-DOS!**

<img width="1332" height="883" alt="image" src="https://github.com/user-attachments/assets/4de8d5f7-0885-4a66-b5f7-8fd62279715b" />

---
*MS-DOS 8: Onde os jogos clássicos do Windows vão para renascer nas raízes da computação!*

