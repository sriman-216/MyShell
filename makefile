all : my_cp.o my_ls.o my_grep.o my_ps.o my_mv.o myshell.o
		gcc my_cp.o my_ls.o my_grep.o my_ps.o my_mv.o myshell.o -lreadline -o myshell

myshell.o : myshell.c
		gcc -c myshell.c -lreadline -o myshell.o

my_cp.o : my_cp.c
		gcc -c my_cp.c -lreadline -o my_cp.o

my_ls.o : my_ls.c
		gcc -c my_ls.c -lreadline -o my_ls.o

my_mv.o : my_mv.c
		gcc -c my_mv.c -lreadline -o my_mv.o

my_grep.o : my_grep.c
		gcc -c my_grep.c -lreadline -o my_grep.o

my_ps.o : my_ps.c
		gcc -c my_ps.c -lreadline -o my_ps.o
