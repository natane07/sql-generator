cd %USERPROFILE%\repos\sql-generator
gcc -c main.c -o obj/main.o
gcc -c src/menu.c -o obj/menu.o
gcc -c src/app.c -o obj/app.o
gcc -c src/file.c -o obj/file.o
gcc obj/main.o obj/menu.o obj/app.o obj/file.o lib/list.o -o bin/main.exe