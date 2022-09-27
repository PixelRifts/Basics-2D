@ECHO off
SetLocal EnableDelayedExpansion

IF NOT EXIST bin mkdir bin
IF NOT EXIST bin\cimgui.dll (
  ECHO Moved cimgui.dll to bin
  MOVE /Y third_party\lib\cimgui.dll bin\cimgui.dll
)

SET cc=clang

REM ==============
REM Gets list of all C files
SET c_filenames= 
FOR %%f in (source\*.c) do SET c_filenames=!c_filenames! %%f
FOR %%f in (source\base\*.c) do SET c_filenames=!c_filenames! %%f
FOR %%f in (source\core\*.c) do SET c_filenames=!c_filenames! %%f
FOR %%f in (source\os\*.c) do SET c_filenames=!c_filenames! %%f
SET c_filenames=!c_filenames! source\impl\ext.c
REM ==============



REM ==============
REM optional layers

ECHO Optional Layer Selected: Render2D
SET c_filenames=!c_filenames! source\opt\render_2d.c

ECHO Optional Layer Selected: Physics2D
SET c_filenames=!c_filenames! source\opt\phys_2d.c

ECHO Optional Layer Selected: C ImGUI
SET c_filenames=!c_filenames! source\opt\ui.c

REM ==============



REM ==============
SET compiler_flags=-Wall -Wvarargs -Werror -Wno-unused-function -Wno-format-security -Wno-incompatible-pointer-types-discards-qualifiers -Wno-unused-but-set-variable -Wno-int-to-void-pointer-cast
SET include_flags=-Isource -Ithird_party/include -Ithird_party/source
SET linker_flags=-g -lshell32 -luser32 -lwinmm -luserenv -lgdi32 -Lthird_party/lib -lbin/stbimpl -lcimgui
SET defines=-D_DEBUG -D_CRT_SECURE_NO_WARNINGS
SET output=-obin/codebase.exe
SET backend=-DBACKEND_GL46
REM ==============

REM SET compiler_flags=!compiler_flags! -fsanitize=address

ECHO "Building codebase.exe..."
%cc% %c_filenames% %compiler_flags% %defines% %backend% %include_flags% %linker_flags% %output%
