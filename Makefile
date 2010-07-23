all:
	gcc -o aq2cfg main.c keyboard.c mouse.c -Iiup/include/ iup/libiup.a `pkg-config gtk+-2.0 --cflags --libs`

win32:
	i586-mingw32msvc-gcc -Os -mwindows -o aq2cfg.exe main.c keyboard.c mouse.c -Iiupw32/include/ iupw32/libiup.a -lole32 -lcomctl32
	i586-mingw32msvc-strip -s aq2cfg.exe

clean:
	rm -f aq2cfg aq2cfg.exe
