.PHONY: all clean

PROJECT=janitor-jamboree
LIBS=\
	`pkg-config --libs libconfig`\
	`sdl2-config --libs`\
	-lSDL2_image\
	-lSDL2_mixer\
	`xml2-config --libs`
CFLAGS=\
	-pedantic-errors\
	-std=c99\
	-DWANT_ZLIB\
	-Isrc/tmx\
	-I/usr/include/libxml2\
	-Wall\
	-Werror\
	-Wextra\
	`pkg-config --cflags libconfig`\
	`sdl2-config --cflags`\
	`xml2-config --cflags`
SRCS=$(wildcard src/*.c) $(wildcard src/tmx/*.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

all: $(OBJS)
	gcc $(CFLAGS) $(LIBS) main.c $(OBJS) -o $(PROJECT)

%: %.c
	gcc -c $(CFLAGS) $(LIBS) -o $@ $<

clean:
	rm $(PROJECT)
	rm $(OBJS)
