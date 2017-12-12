
all: saltos pipe

saltos: saltos.c
	cc -Wall -o $@ $<

pipe: pipe.c
	cc -Wall -o $@ $<
