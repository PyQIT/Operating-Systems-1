rule: pipe.c clean
	gcc -Wall -o pipe1 pipe.c

clean:
	rm -f pipe1
