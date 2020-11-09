CFLAGS = -Wall

all: libbuf.so test_clear test_grow test_init test_pop test_push

%.c: test/%.ts
	checkmk $< > $@

libbuf.so: src/buf.c src/buf.h
	gcc $(CFLAGS) -shared -fPIC $< -o $@

test_%: %.c libbuf.so
	gcc `pkg-config --cflags check` -Isrc $< -o $@ `pkg-config --libs check` -L./ -lbuf

check: all
	LD_LIBRARY_PATH=./ ./test_clear
	LD_LIBRARY_PATH=./ ./test_grow
	LD_LIBRARY_PATH=./ ./test_init
	LD_LIBRARY_PATH=./ ./test_pop
	LD_LIBRARY_PATH=./ ./test_push

clean:
	-rm test_*
	-rm *.c
	-rm libbuf.so