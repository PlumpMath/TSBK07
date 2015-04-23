
all: lab4

lab4:  GL_utilities.c MicroGlut.o loadobj.c VectorUtils3.c main.c LoadTGA.o
	clang-3.5 -std=c99 -Wall GL_utilities.c MicroGlut.o LoadTGA.o loadobj.c VectorUtils3.c main.c -o lab4 -lGL -lm -DGL_GLEXT_PROTOTYPES -lXt -lX11

loadobj.o: loadobj.h
	gcc -w -c loadobj.c

MicroGlut.o: MicroGlut.h
	gcc -w -c MicroGlut.c

LoadTGA.o: LoadTGA.h
	gcc -w -c LoadTGA.c

clean :
	rm lab4 LoadTGA.o MicroGlut.o
