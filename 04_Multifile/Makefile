GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.*
CFLAGS = -Wall -fPIC

#%.o: %.c
#	cc $< $(CFLAGS) -c -o $@

#%.a: const.o fun.o
#	ar -rcs $@ $^

%.so: const.o fun.o
	cc -shared $^ -o $@

all: README prog prog-a prog-so

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a 
	cc $(CFLAGS) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so 
	cc $(CFLAGS) -L. $< -loutput -o $@

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared  $^ -o $@

README: prog
	./$< 2> $@

fun.o: outlib.h

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
liboutput.so
