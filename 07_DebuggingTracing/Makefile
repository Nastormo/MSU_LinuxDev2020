
TEST_FILES = test_file.txt test_file_FIX.txt
TRESH = wrapper.so $(TEST_FILES)

all: wrapper.so

wrapper.so : wrapper.c
	gcc -shared -fPIC wrapper.c -o wrapper.so -ldl

test : wrapper.so
	touch $(TEST_FILES)
	rm $(TEST_FILES)
	touch $(TEST_FILES)
	-LD_PRELOAD=$$PWD/wrapper.so rm $(TEST_FILES)
	rm $(TEST_FILES)

clean :
	rm -rf $(TRESH)