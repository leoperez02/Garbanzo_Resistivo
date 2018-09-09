#!/bin/bash
clear
rm --force *~
cd lib
rm --force *~
rm --force *
cd ..
gcc -Wall -ansi -pedantic -Iinclude -I../DES/include -L../DES/lib/ -c src/TDES.c -o lib/TDES.o
gcc -Wall -ansi -pedantic -Iinclude -I../DES/include lib/TDES.o ../DES/lib/DES.o ../DES/lib/DES_cajas.o src/test_TDES.c -o bin/test_TDES
gcc -Wall -ansi -pedantic -Iinclude -I../DES/include lib/TDES.o ../DES/lib/DES.o ../DES/lib/DES_cajas.o src/cifrador_TDES.c -o bin/cifrador_TDES
cd bin
./test_TDES
#./cifrador_TDES block EEE C
