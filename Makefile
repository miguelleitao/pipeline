
PROGS=saltos pipe pipe2 pipe3

TEST_PROGS=pipe-test pipe2-test pipe3-test test

default: ${PROGS}

all: default ${TEST_PROGS}

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
	rm -f ${PROGS} ${TEST_PROGS} pipe.gc* *.o

push:
	git add .
	git commit -m "update"
	git push
