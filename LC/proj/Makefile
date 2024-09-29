.PATH: src/app src/auxiliary src/graphics src/interrupts ../lab6 src/app/ipc src/app/file_explorer src/app/file_explorer/home src/app/image_viewer src/app/paint src/serial_port src/app/file_transfer src/app/text_viewer
# .OBJDIR: ./bin/ # path for .o files : doesn't seem to work in the project
PROG = ${.CURDIR}/proj
PROGRAMS = proj main example home file_expl paint image_viewer text_viewer file_transfer

# C files needed to compile 'proj'
SRCS = app_keyboard.c app_mouse.c app_rtc.c app_timer.c directories.c proj.c setup.c shared.c debug.c utils.c graphics.c interrupts.c kbc_i8042.c keyboard.c mouse.c timer_i8254.c rtc.c window.c vector.c server.c protocol.c scancodes.c messages.c color.c letters.c file_explorer.c sprite.c
SRCS += sp_util.c serial_port.c sp_ih.c app_serial_port.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -I .. -I src -D_LCOM_OPTIMIZED_ -Wno-c11-extensions -O2 #-DPROJ_RELEASE

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>

all: $(PROGRAMS)
	@printf '\033[0;32m'
	@printf "    Project ready! Execute ./main"
	@printf '\033[0m\n'

main: main.o middleman.o client.o protocol.o
	@echo "       Creating main executable..."
	clang $(CFLAGS) main.o middleman.o client.o protocol.o -o main

# object files needed by librakoon
LIBRAKOON_OBJ = api.o client.o protocol.o vector.o messages.o scancodes.o color.o debug.o sprite.o letters.o

librakoon.a: $(LIBRAKOON_OBJ)
	@echo "       Creating/updating librakoon..."
	ar -rcs librakoon.a $(LIBRAKOON_OBJ)

example: example.o librakoon.a
	@echo "       Creating example program(s)..."
	clang $(CFLAGS) -o example example.o -L. -lrakoon

# object files needed by file explorer
FILE_EXPL_OBJ = directories.o file_expl_draw.o
file_expl: file_expl.o $(FILE_EXPL_OBJ) librakoon.a
	@echo "       Creating file explorer..."
	clang $(CFLAGS) -o file_expl file_expl.o $(FILE_EXPL_OBJ) -L. -lrakoon

home: home.o $(FILE_EXPL_OBJ) librakoon.a
	@echo "       Creating home/desktop program..."
	clang $(CFLAGS) -o home home.o $(FILE_EXPL_OBJ) -L. -lrakoon

image_viewer: image_viewer.o cbmp.o librakoon.a
	@echo "       Creating image viewer..."
	clang $(CFLAGS) -o image_viewer image_viewer.o cbmp.o -L. -lrakoon

forker: forker.o
	clang $(CFLAGS) forker.o -o forker

paint: paint.o librakoon.a
	@echo "       Creating paint program..."
	clang $(CFLAGS) -o paint paint.o -L. -lrakoon

text_viewer: text_viewer.o file_expl_draw.o librakoon.a
	@echo "       Creating text viewer program..."
	clang $(CFLAGS) -o text_viewer text_viewer.o file_expl_draw.o -L. -lrakoon

file_transfer: file_transfer.o librakoon.a
	@echo "       Creating file transfer program..."
	clang $(CFLAGS) -o file_transfer file_transfer.o -L. -lrakoon

# the rule below does not work because it is overriden by the included makefile
%: %.o librakoon.a
	@echo "    Linking $@..."
	clang $(CFLAGS) -o $@ $< -L. -lrakoon

# To hide output, the klean rule uses this:
# >/dev/null - stdout goes to /dev/null, effectively not printing output
# 2>&1 - redirects stderr to stdout, which was redirected to /dev/null
# || true - tricks the make command into thinking that the command succeeded, otherwise it outputs "*** Error code 1 (ignored)"
klean:
	rm $(PROGRAMS) librakoon.a >/dev/null 2>&1 || true
	make clean >/dev/null 2>&1 || true
