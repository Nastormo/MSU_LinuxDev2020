CFLAGS := $(shell pkg-config --libs --cflags glib-2.0)

hashTable: hashTable.c
	gcc hashTable.c $(CFLAGS) -o hashTable

clean:
	rm hashTable