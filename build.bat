cd %USERPROFILE%\repos\sql-generator
gcc -Wall -mwindows -c main.c -o obj/main.o
gcc -Wall -mwindows -c src/menu.c -o obj/menu.o
gcc -Wall -mwindows -c src/app.c -o obj/app.o
gcc -Wall -mwindows -c src/file.c -o obj/file.o
gcc -Wall -mwindows -c src/utils.c -o obj/utils.o
gcc obj/main.o obj/menu.o obj/app.o obj/file.o obj/utils.o lib/list.o lib/parser.o -o bin/sql-generator.exe