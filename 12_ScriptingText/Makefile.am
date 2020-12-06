SUBDIRS = src test

gitclean: maintainer-clean
	git clean -fd

gcov:	check
	$(MAKE) -C src gcov