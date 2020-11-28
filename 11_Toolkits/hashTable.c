#include <stdio.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gmodule.h>
#include <glib/gstdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

struct Data {
    char* word;
    int val;
};

gint compare_func(gconstpointer a, gconstpointer b) {
    struct Data* da = (struct Data*)a;
    struct Data* db = (struct Data*)b;
    return db->val - da->val;
}

void printTable (gpointer key, gpointer value, gpointer array) {
    struct Data *t = malloc(sizeof(struct Data));
    t -> word = key;
    t -> val = GPOINTER_TO_INT(value);
    g_array_append_val((GArray*)array, *t);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        g_printf("hashTable <out_file>\n");
    }
    char *line = malloc(81 * sizeof(char));
    size_t len = 80;
    ssize_t read;
    int *val;
    char** mas_word;
    int size;
    struct Data* sortData;
    GArray* array; 
    array = g_array_new(FALSE, FALSE, sizeof(struct Data));                     
    
    FILE * f = g_fopen(argv[1], "r");
    if (f == NULL) {
        g_printf("File not exist");
        return 1;
    }

    GHashTable* table = g_hash_table_new(g_str_hash, g_str_equal);

    while ((read = getline(&line, &len, f)) != -1) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
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
    fclose(f);
    size = g_hash_table_size(table);
    g_hash_table_foreach(table, (GHFunc)printTable, array);
    g_hash_table_destroy(table);

    g_array_sort(array, (GCompareFunc)compare_func);
    for (int i = 0; i < size; i++) {
        sortData = &g_array_index (array, struct Data, i);
        printf("%s %d\n", sortData->word, sortData->val);
        free(sortData->word);
    }
    g_array_free(array, TRUE);
    return 0;
}