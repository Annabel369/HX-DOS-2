@ECHO OFF
CLS
ECHO Inicializando DOS-WINE para Need For Speed Underground 2...

REM Configurar o PATH para o HX DOS Extender
SET PATH=C:\HXRT\BIN;%PATH%

REM Ir para a pasta do jogo (montada no drive D pelo DOSBox)
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
