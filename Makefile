make:
	gcc -c -fpic libvc.cpp
	gcc -shared -o libvc.so libvc.o

clean:
	rm *.so
	rm *.o
