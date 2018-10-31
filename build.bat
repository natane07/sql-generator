cd C:\Users\quent\repos\sql-generator
gcc -c main.c -o obj/main.o
gcc -c src/menu.c -o obj/menu.o
gcc -c src/app.c -o obj/app.o
gcc obj/main.o obj/menu.o obj/app.o -o bin/main.exe