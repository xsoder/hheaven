RAYLIB := $(HOME)/opt/raylib-5.5_linux_amd64

default:
	gcc -I$(RAYLIB)/include -o hheaven hheaven.c -L$(RAYLIB)/lib -l:libraylib.a -lm
