
CC=x86_64-linux-gnu-gcc

WARNFLAGS+=-pedantic -Wall -W -Wundef \
           -Wendif-labels -Wshadow -Wpointer-arith -Wbad-function-cast \
           -Wcast-align -Wwrite-strings -Wstrict-prototypes \
           -Wmissing-prototypes -Wnested-externs -Winline \
           -Wdisabled-optimization -Wno-missing-field-initializers

CFLAGS?=-pipe -O2 $(WARNFLAGS)
CFLAGS+=-g # TODO(sissel): Comment before release
CFLAGS+=$(CPPFLAGS)

CFLAGS+=-I/usr/X11R6/include -I/usr/local/include -I/usr/include/X11


INC=$(shell pkg-config --cflags x11 xtst xinerama xkbcommon 2> /dev/null || echo "$(DEFAULT_INC)")
CFLAGS+=-std=c99 $(INC)


all: xdo.o cmd_key.o xdotool.o

testi: xdo.o cmd_key.o xdotool.o testi.o
	$(CC) -o testi testi.o xdo.o cmd_key.o xdotool.o -L.  -Xlinker -rpath /usr/local/lib \
	-lm -lX11  -lrt -lXtst -lXinerama -lxkbcommon

testi.o: testi.c
	$(CC) $(CFLAGS) -fPIC -c testi.c

xdo.o: xdo.c
	$(CC) $(CFLAGS) -fPIC -c xdo.c


xdotool.o: xdotool.c
	$(CC) $(CFLAGS) -fPIC -c xdotool.c

cmd_key.o: cmd_key.c
	$(CC) $(CFLAGS) -fPIC -c cmd_key.c

clean:
	rm *.o
