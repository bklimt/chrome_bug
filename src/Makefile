
SHELL := /bin/bash

all: ../output/movie.mpg

../output/movie.mpg: ../bin/chrome_bug
	cd .. && bin/chrome_bug
	for i in ../output/frame*.pcx; do convert $$i $${i%.pcx}.jpg; done;
	ffmpeg -i ../chrome_bugs.mp3 -f image2 -r 30 -i ../output/frame-%08d.jpg -r 30 ../output/movie.mpg
	#convert ../output/*.pcx ../output/movie.mpg

../bin/chrome_bug: ../obj/disk.o ../obj/pcx.o ../obj/sprite.o ../obj/bug.o ../obj/main.o
	gcc -g -o $@ $^ -lm -lstdc++

../obj/disk.o: disk.cc disk.h pcx.h
	gcc -g -Wall -c -o $@ $<

../obj/pcx.o: pcx.cc pcx.h disk.h
	gcc -g -Wall -c -o $@ $<

../obj/sprite.o: sprite.cc sprite.h pcx.h disk.h
	gcc -g -Wall -c -o $@ $<

../obj/bug.o: bug.cc bug.h sprite.h pcx.h disk.h
	gcc -g -Wall -c -o $@ $<

../obj/main.o: main.cc bug.h sprite.h pcx.h disk.h
	gcc -g -Wall -c -o $@ $<

clean:
	rm ../obj/*.o ../bin/*
