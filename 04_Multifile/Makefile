GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so
TEST_TRASH = *_0 *_1 *_3
CFLAGS = -Wall -fPIC

%.o: %.c
	cc $< $(CFLAGS) -c -o $@

launch_%: %
	LD_LIBRARY_PATH=`pwd` ./$< > $<_0 2>&1
	LD_LIBRARY_PATH=`pwd` ./$< 1 > $<_1 2>&1
	LD_LIBRARY_PATH=`pwd` ./$< 1 2 3 > $<_3 2>&1

################################################################

test: launch_prog launch_prog-a launch_prog-so
	-cmp prog_0 prog-a_0
	-cmp prog-a_0 prog-so_0
	-cmp prog-so_0 prog_0
	-cmp prog_1 prog-a_1
	-cmp prog-a_1 prog-so_1
	-cmp prog-so_1 prog_1
	-cmp prog_3 prog-a_3
	-cmp prog-a_3 prog-so_3
	-cmp prog-so_3 prog_3

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

clean_test:
	rm -f $(TEST_TRASH)

distclean: clean clean_test
	rm -rf $(GENERATES)
