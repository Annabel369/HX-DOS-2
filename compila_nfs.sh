#!/bin/bash
echo "Compilando d3d9.dll..."
i686-w64-mingw32-gcc -shared -nostdlib -o d3d9.dll d3d9.c vesa_engine.o d3d9.def -lkernel32 -Wl,--entry=_DllMain@12

echo "Compilando netapi32.dll..."
i686-w64-mingw32-gcc -shared -nostdlib -o netapi32.dll netapi32.c netapi32.def -lkernel32 -Wl,--entry=_DllMain@12

echo "Compilando shfolder.dll..."
i686-w64-mingw32-gcc -shared -nostdlib -o shfolder.dll shfolder.c shfolder.def -lkernel32 -Wl,--entry=_DllMain@12

echo "Compilando tapi32.dll..."
i686-w64-mingw32-gcc -shared -nostdlib -o tapi32.dll tapi32.c tapi32.def -lkernel32 -Wl,--entry=_DllMain@12

echo "Concluído!"
