; ============================================================
; VESALFB.ASM - Meta 1.5 do Projeto HX DOS 2
; Entra em VESA 800x600 16-bits via LFB (Linear Frame Buffer)
; Utiliza "Unreal Mode" e introduz controle espacial (draw_pixel)
; ============================================================
cpu 386
bits 16
org 100h

start:
    ; 1. Entrar no "Unreal Mode" (Modo Irreal)
    cli                     
    push ds
    push es

    ; Calcula o endereco linear exato do GDT
    xor eax, eax
    mov ax, ds
    shl eax, 4
    add eax, gdt_start
    mov dword [gdt_desc + 2], eax

    lgdt [gdt_desc]

    mov eax, cr0
    or al, 1
    mov cr0, eax

    jmp $+2                 
    mov bx, 8
    mov fs, bx
    mov gs, bx

    mov eax, cr0
    and al, 0xFE
    mov cr0, eax

    pop es
    pop ds
    sti                     

    ; 2. Obter informacoes do Modo VESA
    mov ax, 4F01h           
    mov cx, 0114h           
    mov di, mode_info       
    int 10h
    
    cmp ax, 004Fh
    jne erro

    mov eax, dword [mode_info + 40]
    mov dword [lfb_ptr], eax

    ; 3. Entrar no modo grafico COM LFB ativado!
    mov ax, 4F02h
    mov bx, 4114h           ; 0x114 + 0x4000 (LFB)
    int 10h
    
    cmp ax, 004Fh
    jne erro

    ; ============================================================
    ; 4. DESENHANDO NA TELA COM CONTROLE ESPACIAL
    ; ============================================================

    ; A. Limpar a tela (Pintar tudo de preto)
    mov edi, dword [lfb_ptr]
    mov ecx, 480000         ; 800x600 pixels
    mov ax, 0x0000          ; Preto
clear_screen:
    mov [fs:edi], ax
    add edi, 2
    dec ecx
    jnz clear_screen

    ; B. Desenhar uma linha horizontal vermelha (Y = 300)
    mov dx, 300             ; Y = 300
    mov cx, 0               ; X = 0
    mov bx, 0xF800          ; Cor: Vermelho (RGB 565)
h_line:
    call draw_pixel
    inc cx                  ; Avanca X
    cmp cx, 800
    jne h_line

    ; C. Desenhar uma linha vertical verde (X = 400)
    mov cx, 400             ; X = 400
    mov dx, 0               ; Y = 0
    mov bx, 0x07E0          ; Cor: Verde (RGB 565)
v_line:
    call draw_pixel
    inc dx                  ; Avanca Y
    cmp dx, 600
    jne v_line

    ; D. Desenhar um quadrado azul no centro (X: 350-450, Y: 250-350)
    mov dx, 250             ; Y inicial
box_y_loop:
    mov cx, 350             ; X inicial
box_x_loop:
    mov bx, 0x001F          ; Cor: Azul (RGB 565)
    call draw_pixel
    inc cx
    cmp cx, 450
    jne box_x_loop
    
    inc dx
    cmp dx, 350
    jne box_y_loop

    ; 5. Esperar o usuario apertar uma tecla
    mov ah, 00h
    int 16h

    ; 6. Voltar ao modo de texto normal e sair
    mov ax, 0003h
    int 10h
    mov ax, 4C00h
    int 21h

erro:
    mov ax, 0003h
    int 10h
    mov dx, msg_erro
    mov ah, 09h
    int 21h
    mov ax, 4C00h
    int 21h


; ============================================================
; SUB-ROTINAS DO HX DOS 2
; ============================================================

; Função: draw_pixel
; Desenha um pixel exato na tela (LFB)
; Entrada: CX = X (0-799), DX = Y (0-599), BX = Cor (RGB 565 16-bits)
draw_pixel:
    push eax
    push edi

    ; Calculo: Endereco = LFB + ((Y * Largura) + X) * 2 bytes
    
    ; Passo 1: EAX = Y * 800
    movzx eax, dx           ; EAX = Y
    imul eax, 800           ; Multiplica por 800 (largura da tela)
    
    ; Passo 2: EAX = EAX + X
    movzx edi, cx           ; Pega o X
    add eax, edi            ; EAX = (Y * 800) + X
    
    ; Passo 3: EAX = EAX * 2 (pois cada pixel tem 16-bits = 2 bytes)
    shl eax, 1              ; Shift Left 1 é igual a multiplicar por 2
    
    ; Passo 4: Somar com a base do LFB e gravar na memoria
    mov edi, dword [lfb_ptr]
    add edi, eax            ; EDI aponta para o pixel exato!
    
    mov [fs:edi], bx        ; PINTA O PIXEL!

    pop edi
    pop eax
    ret


; --- DADOS E VARIAVEIS ---
msg_erro db 'Falha ao iniciar VESA ou LFB!', 13, 10, '$'
lfb_ptr  dd 0

gdt_start:
    dd 0, 0
gdt_data:
    dw 0xFFFF               
    dw 0                    
    db 0                    
    db 10010010b            
    db 11001111b            
    db 0                    
gdt_desc:
    dw 15                   
    dd gdt_start            

mode_info:
    times 256 db 0
