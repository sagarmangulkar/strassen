all: strassen.out

strassen.out:
		gcc -std=c11 strassen.c -o strassen.out

clean:
	rm -f strassen.out
