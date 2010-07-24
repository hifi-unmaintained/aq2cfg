PLATFORM := Linux26g4
BIN = aq2cfg
CFLAGS = -Iiup/include/
LIBS = `pkg-config gtk+-2.0 --cflags --libs`
IUPMAKE = iupgtk NO_DYNAMIC=Yes
STRIP := strip

ifdef WIN32
    CC = i586-mingw32msvc-gcc
    STRIP = i586-mingw32msvc-strip
    PLATFORM = Win32
    BIN = aq2cfg.exe
    CFLAGS += -mwindows
    LIBS = -lole32 -lcomctl32
    IUPMAKE = iup NO_DYNAMIC=Yes TEC_UNAME=Win32 TEC_SYSNAME=Win32 CC=i586-mingw32msvc-gcc RANLIB=i586-mingw32msvc-ranlib
endif

all: iup/lib/$(PLATFORM)/libiup.a
	$(CC) -o $(BIN) $(CFLAGS) main.c keyboard.c mouse.c iup/lib/$(PLATFORM)/libiup.a $(LIBS)

release: $(BIN)
	$(STRIP) -s $(BIN)

iup/lib/$(PLATFORM)/libiup.a:
	cd iup && make $(IUPMAKE)

clean:
	rm -f aq2cfg aq2cfg.exe
