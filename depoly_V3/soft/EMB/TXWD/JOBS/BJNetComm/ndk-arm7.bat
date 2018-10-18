@echo off
set NDK_ROOT=%DEV_ROOT%\android\ndk
set PATH=%NDK_ROOT%\prebuilt\windows\bin;%NDK_ROOT%\toolchains\arm-linux-androideabi-4.9\prebuilt\windows\bin;%PATH%
set NDK_INC=%NDK_ROOT%\platforms\android-24\arch-arm\usr\include
set NDK_LIB=%NDK_ROOT%\platforms\android-24\arch-arm\usr\lib
copy %NDK_LIB%\*_so.o
arm-linux-androideabi-gcc -c -march=armv7-a -O2 -fPIC -Wall -fshort-wchar -ffunction-sections -fdata-sections -I "%NDK_INC%" -I../../../CrHack/inc BJNetComm.c
arm-linux-androideabi-gcc -o libBJNetComm.so -shared -fPIC -Wl,--gc-sections -Wl,--no-wchar-size-warning -Wl,--version-script=BJNetComm.map -L "%NDK_LIB%" -L../../../CrHack/bin/gcc_android_all/armeabi-v7a BJNetComm.o -lUTILs -lCOREs -lc
arm-linux-androideabi-strip --strip-unneeded libBJNetComm.so
del *.o /Q
pause
