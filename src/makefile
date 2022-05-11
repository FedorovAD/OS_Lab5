down: main_1 main_2

main_1: lib1.o main_1.c
	gcc main_1.c lib1.o -o main_1

main_2: main_2.o lib1.o lib1.so lib2.o lib2.so
	gcc main_2.o -Wl,-rpath,. -ldl -o main_2
	
lib1.so: lib1.o
	gcc -shared -o lib1.so lib1.o
	
main_2.o: main_2.c
	gcc -c main_2.c

lib1.o: lib1.c
	gcc -fPIC -c lib1.c

lib2.so: lib2.o
	gcc -shared -o lib2.so lib2.o
	
lib2.o: lib2.c
	gcc -fPIC -c lib2.c
