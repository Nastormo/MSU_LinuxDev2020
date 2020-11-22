CC = gcc
CFLAGS = -Wall

all: bin_search ru/LC_MESSAGES/bin_search.mo

bin_search: bin_search.c
	$(CC) $< -o $@

test: test.c
	$(CC) $< -o $@

ru/LC_MESSAGES/bin_search.mo: bin_search.ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

bin_search.ru.po: update.pot
	msgmerge -U $@ $<

update.pot: bin_search.pot bin_search.c
	xgettext -k_ -c bin_search.c -o update.new.pot
	cp bin_search.pot update.pot
	msgmerge -U update.pot update.new.pot

doxygen: Doxyfile
	doxygen $<

clean:
	-rm -rf ru
	-rm update*
	-rm bin_search
	-rm test
	-rm *~
