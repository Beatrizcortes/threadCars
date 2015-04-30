threads: prac4.c
	gcc prac4.c -Wall -o threads -lpthread

clean:
	rm threads
	echo done
