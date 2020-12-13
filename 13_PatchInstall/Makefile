CC = gcc
CFLAGS = -Wall 
DESTDIR_BIN = /usr/bin/
DESTDIR_LOC = /usr/share/locale/
LOCALE_PATH = ru/LC_MESSAGES/

ifdef DESTDIR
	DESTDIR_BIN = $(DESTDIR)
	DESTDIR_LOC = $(DESTDIR)
endif

all: install

install: $(LOCALE_PATH)bin_search.mo bin_search clean_gen

bin_search: bin_search.c
	$(CC) $< -o $(DESTDIR_BIN)$@

$(LOCALE_PATH)bin_search.mo: bin_search.ru.po
	mkdir -p `dirname $(DESTDIR_LOC)$@`
	msgfmt $< -o $(DESTDIR_LOC)$@     

bin_search.ru.po: update.pot
	msgmerge -U $@ $<

update.pot: bin_search.pot bin_search.c
	xgettext -k_ -c bin_search.c -o update.new.pot
	cp bin_search.pot update.pot
	msgmerge -U update.pot update.new.pot

clean_gen:
	-rm update*

clean: clean_gen
	-rm $(DESTDIR_BIN)bin_search
	-rm -rf $(DESTDIR_LOC)ru

