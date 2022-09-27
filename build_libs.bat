@ECHO off
SetLocal EnableDelayedExpansion

IF NOT EXIST bin mkdir bin

SET cc=clang
SET cppc=clang++

REM ==============
SET c_filenames= 
SET c_filenames=!c_filenames! source\impl\stb_impl.c
REM ==============


REM ==============
SET compiler_flags=-Wall -Wvarargs -Werror -Wno-unused-function -Wno-format-security -Wno-incompatible-pointer-types-discards-qualifiers -Wno-unused-but-set-variable -Wno-int-to-void-pointer-cast -c
SET include_flags=-Isource -Ithird_party/include -Ithird_party/include/imgui -Ithird_party/include/imgui/backends
SET defines=-D_DEBUG -D_CRT_SECURE_NO_WARNINGS
SET backend=-DBACKEND_GL46
REM ==============

REM SET compiler_flags=!compiler_flags! -fsanitize=address

ECHO "Building stbimpl.lib..."
%cc% %c_filenames% %compiler_flags% %defines% %backend% %include_flags% -obin/stbimpl.o
llvm-ar rc bin/stbimpl.lib bin/stbimpl.o

del /f bin\stbimpl.o
