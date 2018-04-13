.PHONY: all clean

PROJECT=janitor-jamboree
LIBS=\
	`pkg-config --libs libconfig`\
	`sdl-config --libs`\
	-lSDL_image
CFLAGS=\
	-pedantic-errors\
	-std=c99\
	-Wall\
	-Werror\
	-Wextra\
	`pkg-config --cflags libconfig`\
	`sdl-config --cflags`

SRCS=$(wildcard src/*.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

all: $(OBJS)
	gcc $(CFLAGS) $(LIBS) main.c $(OBJS) -o $(PROJECT)

%: %.c
	gcc -c $(CFLAGS) $(LIBS) -o $@ $<

clean:
	rm $(PROJECT)
	rm $(OBJS)
