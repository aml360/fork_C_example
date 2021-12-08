all:
	gcc src/main.c -o main
	mv main dist/main
	./dist/main

clean:
	rm -r dist/*