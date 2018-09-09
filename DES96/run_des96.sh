#!/bin/bash
clear
rm --force *~
cd bin
rm --force *
cd ..
cd lib
rm --force *~
rm DES96.o
rm DES96_cajas.o
cd ..
gcc -Wall -Ilib -ansi -pedantic -c -w src/DES96_cajas.c -o lib/DES96_cajas.o
gcc -Wall -Ilib -ansi -pedantic -c -w src/DES96.c -o lib/DES96.o
gcc -Wall -Ilib -ansi -pedantic  lib/DES.o lib/DES_cajas.o lib/DES96.o lib/DES96_cajas.o src/main.c -o bin/main
cd bin
./main
