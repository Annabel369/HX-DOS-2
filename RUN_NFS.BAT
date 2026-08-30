@ECHO OFF
CLS
ECHO Inicializando DOS-WINE para Need For Speed Underground 2...

REM Configurar o PATH para o HX DOS Extender
SET PATH=C:\HXRT\BIN;%PATH%

REM Montar a pasta do jogo como drive D: automaticamente
MOUNT D "/media/astral/DOS71/drive_c/Program Files (x86)/EA GAMES/Need for Speed Underground 2"
D:
REM Copiar nossas DLLs tradutoras para a pasta do jogo (para ter certeza que serão carregadas)
COPY C:\d3d9.dll .
COPY C:\netapi32.dll .
COPY C:\shfolder.dll .
COPY C:\tapi32.dll .
COPY C:\dinput8.dll .

ECHO Iniciando o SPEED2.EXE via DPMILD32...
DPMILD32.EXE SPEED2.EXE > C:\NFS_LOG.TXT

ECHO Jogo finalizado.
PAUSE
