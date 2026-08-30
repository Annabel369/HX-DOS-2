bits 32

global _vesa_init
global _vesa_draw_pixel
global _vesa_clear

section .bss
    lfb_ptr resd 1

section .text

; DPMI struct para INT 31h AX=0300h
struc dpmi_regs
    .edi resd 1
    .esi resd 1
    .ebp resd 1
    .res1 resd 1
    .ebx resd 1
    .edx resd 1
    .ecx resd 1
    .eax resd 1
    .flags resw 1
    .es resw 1
    .ds resw 1
    .fs resw 1
    .gs resw 1
    .ip resw 1
    .cs resw 1
    .sp resw 1
    .ss resw 1
endstruc

section .data
    regs istruc dpmi_regs
    iend

; void vesa_init(void);
_vesa_init:
    push ebp
    mov ebp, esp
    pusha

    ; Zerar a struct
    mov edi, regs
    mov ecx, 50
    xor eax, eax
    rep stosb

    ; Setar registradores para INT 10h, AX=4F02h, BX=4115h (800x600 32-bit LFB)
    mov word [regs + dpmi_regs.eax], 0x4F02
    mov word [regs + dpmi_regs.ebx], 0x4115
    
    ; Chamar DPMI Simulate Real Mode Interrupt (INT 31h, AX=0300h)
    mov eax, 0x0300
    mov ebx, 0x0010 ; INT 10h
    xor ecx, ecx
    mov edi, regs
    int 0x31

    ; Endereco padrao do LFB do DOSBox (Hardcoded para prova de conceito)
    mov dword [lfb_ptr], 0xE0000000

    popa
    pop ebp
    ret

; void vesa_draw_pixel(int x, int y, int color);
_vesa_draw_pixel:
    push ebp
    mov ebp, esp
    push ebx
    push edx

    mov eax, [ebp+12] ; y
    mov ebx, 800
    mul ebx           ; eax = y * 800
    add eax, [ebp+8]  ; eax = y * 800 + x
    shl eax, 2        ; eax = (y * 800 + x) * 4 bytes (32-bits)

    mov edx, [lfb_ptr]
    add edx, eax      ; LFB + offset

    mov eax, [ebp+16] ; color
    mov [edx], eax    ; Escrever no LFB!

    pop edx
    pop ebx
    pop ebp
    ret

; void vesa_clear(int color);
_vesa_clear:
    push ebp
    mov ebp, esp
    pusha

    mov edi, [lfb_ptr]
    mov eax, [ebp+8]   ; color
    mov ecx, 800 * 600 ; pixels
    rep stosd          ; preencher LFB inteiro com a cor

    popa
    pop ebp
    ret
