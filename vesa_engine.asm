bits 32

global _vesa_init
global _vesa_draw_pixel

section .text

; void vesa_init(void);
_vesa_init:
    ; Em um ambiente real DPMI 32-bits (como o HX), as interrupcoes de video INT 10h
    ; podem ser chamadas via DPMI Simulate Real Mode Interrupt (INT 31h, AX=0300h)
    ; Para manter este esqueleto simples, vamos assumir que o LFB ja esta
    ; mapeado pelo HXGUI ou faremos apenas um stub.
    ret

; void vesa_draw_pixel(int x, int y, int color);
_vesa_draw_pixel:
    push ebp
    mov ebp, esp
    
    ; Argumentos:
    ; [ebp+8] = x
    ; [ebp+12] = y
    ; [ebp+16] = color

    ; Aqui no futuro multiplicaremos Y * Pitch + X e escreveremos na memoria LFB.
    
    pop ebp
    ret
