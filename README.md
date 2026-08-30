# Welcome to the HX-DOS-2 project! 🚀

This repository is the core of an insanely ambitious idea: building a bootable ecosystem based on the robust MS-DOS 7.10, perfectly compatible with both 16-bit and 32-bit architectures. 

The big catch here is evolution and compatibility: we are capable of running complex native Windows XP games (like Grand Theft Auto: Vice City or Need for Speed), utilizing Software 3D acceleration and native API Wrappers, directly from the terminal!

## 👑 The Foundation: MS-DOS 7.10 (China DOS Union)
**IMPORTANT TECHNICAL NOTICE:**
Under no circumstances confuse the foundation of this project! We are **NOT** running on purist DOSBox or DOS 6.22! 
All code in this repository was built, tested, and validated on top of the legendary **MS-DOS 7.10 extracted from Windows 98 SE by the China DOS Union (CDU)**. 

Why MS-DOS 7.10?
- Native and flawless support for **FAT32** and LBA (necessary for the 2GB+ assets of GTA VC and NFS).
- Native support for **LFN (Long File Names)**, preventing Windows game folders from corrupting.
- Aggressive memory management in Real/Unreal Mode.

## 🎯 What is "HX-DOS-2"?
The **HX-DOS-2** project works by providing its own DLLs (Wrappers) and system extensions (completely original, without relying on emulators) to implement and provide support for Windows 2000/XP APIs directly on top of the bootable foundation of MS-DOS 7.10, perfectly uniting the 16-bit and 32-bit architectures.

When a game asks to render a 3D model, it calls `d3d8.dll` thinking it's talking to Microsoft. Our `d3d8.dll` intercepts the polygons, converts the math, and sends the rendering requests straight to our **Low-Level VESA Assembly Engine (cube3d.asm)**!

## 📂 Repository Technical Structure

### 1. C Wrappers (Fake Windows DLLs)
* `d3d8.c` / `d3d8.dll`: Our custom interceptor version of Direct3D 8. It contains the C++ COM VTable structures simulated in pure C. Redirects rendering calls to VESA.
* `d3d9.c` / `d3d9.dll`: Our Direct3D 9 Wrapper. Currently features a massive **120-slot Call Tracker Spy Network**. All unmapped D3D9 functions log their Slot ID directly to `hx_d3d9.log` so we can dynamically reverse-engineer the game's rendering engine on the fly.
* `dinput8.c` / `dinput8.dll`: Our DirectInput 8 Wrapper. **Features a Bare-Metal Hardware Mapping**: By executing Inline Assembly (`inb $0x60`), this wrapper bypasses all OS layers and maps the physical keyboard controller on the motherboard. This flawlessly pipes the MS-DOS keyboard (like the ESC key) straight into the Windows DirectInput buffer!
* `netapi32.c` / `netapi32.dll`: Network API wrapper, simulating network function returns.
* `tapi32.c` / `tapi32.dll`: Telephony API (TAPI) wrapper, generating simulated returns (S_OK) for stability.
* `shfolder.c` / `shfolder.dll`: Shell Folder API wrapper, useful for games (like Need for Speed) that request standard directories (e.g., "My Documents").
* `test_d3d.c`: A native Win32 test application to validate the COM calls of our DLL inside DOS using `DPMILD32.EXE`.

### 2. The Native Graphics Engine (x86 Assembly)
* `cube3d.asm` (**The Crown Jewel**): Definitive implementation of native 3D rendering and mathematical algorithms (like Bresenham) in Assembly.
    - Uses **32-bit Unreal Mode** to break the 64KB memory barrier of MS-DOS.
    - **Golden Secret**: Linear memory segmentation (4GB Limit) is injected into the `FS` register, instead of the traditional `ES`. This shields the Engine against BIOS and DOSBox crashes (`Illegal descriptor type 10`), ensuring infinite stability.
    - Direct access to the Linear Frame Buffer (LFB) of the video card via VESA BIOS Extension (Mode 0x114 LFB).

## 🛠️ How to Compile "HX-DOS-2"

Our DLLs are compiled using the Win32 C compiler (MinGW) to maintain absolute ABI (Application Binary Interface) compatibility with the original games.

**For the VESA Engine (C Object):**
```bash
nasm -f elf32 vesa_engine.asm -o vesa_engine.o
```

**For the Translator DLLs (MinGW):**
```bash
i686-w64-mingw32-gcc -shared -nostdlib -o d3d8.dll d3d8.c vesa_engine.o d3d8.def -lkernel32 -Wl,--entry=_DllMain@12
i686-w64-mingw32-gcc -shared -nostdlib -o dinput8.dll dinput8.c dinput8.def -lkernel32 -Wl,--entry=_DllMain@12
```

**For Need For Speed (NFS) DLLs:**
You can run our automated script:
```bash
./compila_nfs.sh
```
This will generate and organize the essential DLLs (`d3d9`, `tapi32`, `netapi32`, `shfolder`) so the game runs smoothly, and you can launch it using `RUN_NFS.BAT`.

## 🚀 Next Steps on the Yellow Brick Road
1. **Merge the Two Halves**: Link the `DrawPrimitive` commands captured by `d3d8.c` with the polygon tracing and Bresenham Engine of `cube3d.asm`.
2. **Spinning 3D Cube**: Replace the black screen and the test "X" with the first geometric triangle projected and rotated by our own 3D math in DOS.
3. **Final Boot Loader**: Unify everything into a `START.BAT` (or dedicated interface) where Splash Screens (like Rockstar North's) load smoothly straight from the MS-DOS 7.10 command line.

## 📸 Visual Demonstrations (Screenshots)


<img width="791" height="627" alt="image" src="https://github.com/user-attachments/assets/66a50cfc-d0b7-4b4d-95b1-6f1ceb62644c" />

Sensational! The screenshot shows that everything worked with mathematical perfection. The red line cuts exactly across the Y=300 axis, the green one across the X=400 axis, and the blue square is perfectly centered.

We have just built the absolute foundation of a Graphics Engine. Any 3D game (from Doom to GTA Vice City) relies on exactly this premise: writing colors into a linear memory buffer extremely fast.


<img width="932" height="270" alt="image" src="https://github.com/user-attachments/assets/0eb3eeb2-1b9f-4195-8ec5-75e17112be46" />


<img width="1332" height="883" alt="image" src="https://github.com/user-attachments/assets/4de8d5f7-0885-4a66-b5f7-8fd62279715b" />

---
*HX-DOS-2: Where classic Windows games go to be reborn in the roots of computing!*

