cd %USERPROFILE%\repos\sql-generator
gcc -Wall -O2 -c main.c -o obj/main.o
gcc -Wall -O2 -c src/menu.c -o obj/menu.o
gcc -Wall -O2 -c src/app.c -o obj/app.o
gcc -Wall -O2 -c src/file.c -o obj/file.o
gcc obj/main.o obj/menu.o obj/app.o obj/file.o lib/list.o -o bin/main.exe