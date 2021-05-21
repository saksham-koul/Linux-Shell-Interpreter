run: shell cat date ls mkdir rm
	./shell

shell: cat date ls mkdir rm
	gcc myshell.c -o shell

cat: cat.c
	gcc cat.c -o cat
	
date: date.c
	gcc date.c -o date
	
ls: ls.c
	gcc ls.c -o ls

mkdir: mkdir.c
	gcc mkdir.c -o mkdir
	
rm: rm.c
	gcc rm.c -o rm
