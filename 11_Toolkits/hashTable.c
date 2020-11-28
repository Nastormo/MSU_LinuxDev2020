#include <stdio.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gmodule.h>
#include <glib/gstdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        g_printf("hashTable <out_file>\n");
    }
    char *line = malloc(81 * sizeof(char));
    size_t len = 80;
    ssize_t read;
    int *val;
    char** mas_word;
    
    FILE * f = g_fopen(argv[1], "r");
    if (f == NULL) {
        g_printf("File not exist");
        return 1;
    }

    GHashTable* table = g_hash_table_new(g_str_hash, g_str_equal);

    while ((read = getline(&line, &len, f)) != -1) {
        g_printf("%s %ld\n", line,  len);
        mas_word = g_strsplit(line, " ", 0);
        int i = 0;
        while(mas_word[i] != NULL) {
            char *key = g_strdup(mas_word[i]);
            val = g_hash_table_lookup(table, key);
            if (!val) { 
                g_hash_table_insert(table, key, GINT_TO_POINTER(1));
            } else {
                g_hash_table_replace(table, key, GINT_TO_POINTER(GPOINTER_TO_INT(val) + 1));
            }
            i++;
        }
        g_strfreev(mas_word);
    }
    g_hash_table_destroy(table);

    fclose(f);
    // if (line)
    //     free(line);
    // exit(EXIT_SUCCESS);
    //g_strsplit ()
    return 0;
}