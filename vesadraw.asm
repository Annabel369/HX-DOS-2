; ============================================================
; VESADRAW.COM - Meta 1.3 do Projeto HX DOS 2
; Entra em VESA 800x600 (16-bits de cor) e desenha na tela
; Usando Bank Switching (VBE Func 05h) no Modo Real
; ============================================================
cpu 386
bits 16
org 100h

start:
    ; 1. Entrar no modo grafico 800x600 com 16-bits de cor (Modo 0x114)
    ; (Usamos 16-bits em vez de 32-bits para facilitar o calculo no Bank Switching)
    mov ax, 4F02h
    mov bx, 0114h           ; 0x114 = 800x600, 16 bits (65 mil cores)
    int 10h
    
    ; Verifica erro
    cmp ax, 004Fh
    jne erro

    ; 2. Configurar o ponteiro para a janela de memoria da Placa de Video
    ; O segmento padrão para VESA Bank 0 é A000h
    mov ax, 0A000h
    mov es, ax

    ; 3. Desenhar a tela inteira (800 x 600 pixels)
    ; Em 16-bits, cada pixel ocupa 2 bytes. 
    ; Tamanho total da tela = 800 * 600 * 2 = 960.000 bytes
    ; Como cada banco (janela) tem 64KB (65.536 bytes), precisaremos trocar de banco 14 vezes.

    xor dx, dx              ; DX = numero do Banco Atual (Bank Number)
    mov cx, 15              ; Loop para 15 bancos (15 * 64KB cobre a tela)

draw_bank:
    push cx                 ; Salva contador do loop externo

    ; Solicita a placa de video a troca para o Banco DX
    mov ax, 4F05h           ; VBE Window Control
    mov bh, 00h             ; Set Window
    mov bl, 00h             ; Window A
    ; DX ja contem o numero da janela
    int 10h

    ; Agora preenchemos esse bloco de 64KB
    xor di, di              ; ES:DI comeca em A000:0000
    mov cx, 32768           ; 32768 WORDS = 65536 BYTES

fill_pixel:
    ; Vamos gerar uma cor baseada na posicao para criar um efeito legal
    ; Cor em 16-bits: RRRRRGGG GGGBBBBB (5-6-5)
    mov ax, di              ; Usa o offset atual para variar a cor
    add ax, dx              ; Soma o banco atual para a cor mudar na tela
    stosw                   ; Salva o pixel (AX) na VRAM (ES:DI) e avanca DI
    loop fill_pixel         ; Repete para todo o bloco de 64KB

    pop cx                  ; Recupera contador
    inc dx                  ; Vai para a proxima pagina/banco da placa de video
    loop draw_bank          ; Repete o loop externo

    ; 4. Esperar o usuario apertar uma tecla
    mov ah, 00h
    int 16h

    ; 5. Voltar ao modo de texto normal
    mov ax, 0003h
    int 10h

    ; Sair
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

msg_erro db 'Falha ao iniciar VESA 800x600x16', 13, 10, '$'
