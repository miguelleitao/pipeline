
PROGS=saltos pipe pipe2 pipe3

TEST_PROGS=pipe-test pipe2-test pipe3-test test

CFLAGS=-Wall

default: ${PROGS}

all: default ${TEST_PROGS}

pipe-test: pipe.c
	cc -coverage -c -O0 -Wall -D MAX_I=8 $<
	cc -coverage -o $@ pipe.o
	./$@ >$<.out
	gcov $<

pipe2-test: pipe2.c
	cc -coverage -c -O0 -Wall -D MAX_I=8 $<
	cc -coverage -o $@ pipe2.o
	./$@ >$<.out
	gcov $<

pipe3-test: pipe3.c
	cc -coverage -c -O0 -Wall -D MAX_I=8 $<
	cc -coverage -o $@ pipe3.o
	./$@ >$<.out
	gcov $<

test: pipe-test pipe2-test pipe3-test

clean:
	rm -f ${PROGS} ${TEST_PROGS} *.gcno *.gcda *.gcov *.o

push:
	git add .
	git commit -m "update"
	git push
