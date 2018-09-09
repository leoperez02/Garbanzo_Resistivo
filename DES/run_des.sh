#!/bin/bash
clear
rm --force *~
cd bin
rm --force *
cd ..
cd lib
rm --force *~
rm --force *.o
cd ..
gcc -Wall -Iinclude -ansi -pedantic -c src/DES_cajas.c -o lib/DES_cajas.o
gcc -Wall -Iinclude -ansi -pedantic -c src/DES.c -o lib/DES.o
gcc -Wall -Iinclude -ansi -pedantic lib/DES.o lib/DES_cajas.o src/test_DES.c -o bin/test_DES
gcc -Wall -Iinclude -ansi -pedantic lib/DES.o lib/DES_cajas.o src/main_DES.c -o bin/main_DES
cd bin
./test_DES
