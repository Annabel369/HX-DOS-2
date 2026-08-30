; ============================================================
; CUBE3D.ASM - A Engine 3D "Hardcore" (MS-DOS)
; Renderizacao via VESA LFB e Modo Unreal (32-bits no modo real)
; ============================================================
cpu 386
bits 16
org 100h

start:
    ; 0. Encontrar o VESA LFB Base Address para o Modo 0x114 (800x600 16-bits)
    mov ax, 4F01h
    mov cx, 114h
    mov di, mode_info
    int 10h

    ; Armazenar o ponteiro LFB
    mov eax, dword [mode_info + 40]
    mov dword [lfb_ptr], eax

    ; 1. Entrar no Modo Grafico VESA 0x114 com LFB (Bit 14 ativado)
    mov ax, 4F02h
    mov bx, 4114h 
    int 10h

    ; 2. Setup do Unreal Mode (para acessar RAM > 1MB via ES)
    cli
    push ds
    push es
    
    ; Carregar a GDT provisoria (nao precisamos mudar CS)
    ; Apenas carregamos um seletor de dados 32-bits para o ES
    lgdt [gdt_desc]
    
    ; Ativar Modo Protegido rapidinho (Bit 0 do CR0)
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp .flush_pmode
.flush_pmode:

    ; Configurar ES para abarcar 4GB (Seletor 10h da nossa GDT)
    mov bx, 10h
    mov es, bx
    
    ; Desligar Modo Protegido voltando ao Real Mode
    mov eax, cr0
    and al, 0xFE
    mov cr0, eax
    
    ; Flush na fila de instrucoes e recarregar CS original
    push cs
    push word rmode_entry
    retf

rmode_entry:
    ; Restaurar Data Segments normais, mas ES continua destravado (Unreal!)
    pop es
    pop ds
    sti

    ; ==========================================
    ; AQUI COMECA A ENGINE GRAFICA!
    ; ==========================================
    
    ; Desenhar uma linha diagonal Verde!
    ; draw_line(X0=100, Y0=100, X1=700, Y1=500, Cor=0x07E0)
    push dword 0x07E0 ; Cor Verde 16-bits
    push dword 500    ; Y1
    push dword 700    ; X1
    push dword 100    ; Y0
    push dword 100    ; X0
    call draw_line

    ; Desenhar a outra diagonal Vermelha para formar um "X"
    push dword 0xF800 ; Cor Vermelha 16-bits
    push dword 100    ; Y1
    push dword 700    ; X1
    push dword 500    ; Y0
    push dword 100    ; X0
    call draw_line

    ; O codigo ira esperar uma tecla abaixo!

wait_key:
    ; Esperar pressionar tecla para sair
    mov ah, 00h
    int 16h

exit:
    ; Voltar para modo texto (Modo 03h)
    mov ax, 0003h
    int 10h
    
    ; Sair pro DOS
    mov ax, 4C00h
    int 21h

; ------------------------------------------------------------
; ROTINA: draw_pixel
; Entradas: CX = X, DX = Y, EBX = Cor (16-bits no ax)
; Destroi: EAX, EDI
; ------------------------------------------------------------
draw_pixel:
    ; Prevenir desenhar fora da tela
    cmp cx, 800
    jae .skip
    cmp dx, 600
    jae .skip
    
    ; Formula 16-bits: Offset = (Y * 800 * 2) + (X * 2)
    mov eax, 1600    ; 800 * 2 bytes por linha
    mul edx          ; EAX = Y * 1600
    
    mov edi, eax
    mov eax, ecx
    shl eax, 1       ; EAX = X * 2
    add edi, eax     ; EDI = Y*1600 + X*2
    
    ; Adicionar a base da placa de video
    add edi, dword [lfb_ptr]
    
    ; Gravar o Pixel usando o ES (Unreal Mode)
    mov [es:edi], bx

.skip:
    ret

; ------------------------------------------------------------
; ROTINA: draw_line (Algoritmo de Bresenham)
; Argumentos via pilha (32-bits): [X0], [Y0], [X1], [Y1], [Cor]
; ------------------------------------------------------------
draw_line:
    push ebp
    mov ebp, esp
    sub esp, 24       ; Espaco para variaveis locais na pilha
    pusha             ; Salvar todos os registradores

    mov ecx, [ebp+8]  ; CX = X0
    mov edx, [ebp+12] ; DX = Y0
    mov esi, [ebp+16] ; SI = X1
    mov edi, [ebp+20] ; DI = Y1
    mov ebx, [ebp+24] ; BX = Cor

    ; Calcular DX = abs(X1 - X0)
    mov eax, esi
    sub eax, ecx
    jge .dx_pos
    neg eax
.dx_pos:
    mov [ebp-4], eax  ; Variavel local: dx

    ; Calcular DY = -abs(Y1 - Y0)
    mov eax, edi
    sub eax, edx
    jge .dy_pos
    neg eax
.dy_pos:
    neg eax           ; DY deve ser negativo no algoritmo
    mov [ebp-8], eax  ; Variavel local: dy

    ; Passo X (sx)
    mov eax, 1
    cmp ecx, esi
    jl .sx_pos
    mov eax, -1
.sx_pos:
    mov [ebp-12], eax ; Variavel local: sx

    ; Passo Y (sy)
    mov eax, 1
    cmp edx, edi
    jl .sy_pos
    mov eax, -1
.sy_pos:
    mov [ebp-16], eax ; Variavel local: sy

    ; Erro inicial (err) = dx + dy
    mov eax, [ebp-4]
    add eax, [ebp-8]
    mov [ebp-20], eax ; Variavel local: err

.loop:
    ; Desenhar o pixel atual (CX=X, DX=Y, EBX=Cor)
    pusha
    call draw_pixel
    popa

    ; Checar se chegou no final (X0 == X1 e Y0 == Y1)
    cmp ecx, esi
    jne .continue
    cmp edx, edi
    je .done

.continue:
    ; e2 = 2 * err
    mov eax, [ebp-20]
    shl eax, 1
    mov [ebp-24], eax ; Variavel local: e2

    ; if e2 >= dy
    cmp eax, [ebp-8]
    jl .check_y
    
    ; err += dy
    mov eax, [ebp-8]
    add [ebp-20], eax
    
    ; X0 += sx
    mov eax, [ebp-12]
    add ecx, eax

.check_y:
    ; if e2 <= dx
    mov eax, [ebp-24]
    cmp eax, [ebp-4]
    jg .loop
    
    ; err += dx
    mov eax, [ebp-4]
    add [ebp-20], eax
    
    ; Y0 += sy
    mov eax, [ebp-16]
    add edx, eax

    jmp .loop

.done:
    popa
    add esp, 24       ; Limpar variaveis locais
    pop ebp
    ret 20            ; Limpar os 5 argumentos da pilha

; ------------------------------------------------------------
; DADOS E ESTRUTURAS
; ------------------------------------------------------------
lfb_ptr dd 0

gdt:
    dq 0 ; Null Descriptor
    ; Seletor 08h: Code Segment (Real Mode 64k)
    dw 0xFFFF, 0x0000, 0x9A00, 0x0000
    ; Seletor 10h: Data Segment (4GB Limit para Unreal Mode)
    dw 0xFFFF, 0x0000, 0x9200, 0x00CF 
gdt_desc:
    dw 23
    dd gdt

; Estrutura de Informacao do Modo VESA (256 bytes necessarios)
mode_info: resb 256
