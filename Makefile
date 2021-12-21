
all: saltos pipe pipe2 pipe3

saltos: saltos.c
	cc -Wall -o $@ $<

pipe: pipe.c
	cc -Wall -o $@ $<

pipe-test: pipe.c
	cc -coverage -O0 -Wall -D MAX_I=8 -o $@ $<

pipe2-test: pipe2.c
	cc -coverage -O0 -Wall -D MAX_I=8 -o $@ $<

pipe3-test: pipe3.c
	cc -coverage -O0 -Wall -D MAX_I=8 -o $@ $<

test: pipe-test
	./$< >$<.out
	gcov pipe.c

clean:
	rm -f saltos pipe pipe-test pipe.gc* *.o

push:
	git add .
	git commit -m "update"
	git push
