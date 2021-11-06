#ifndef KEVAS_H
#define KEVAS_H

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct kevas_entry_s kevas_entry_t;
typedef struct kevas_row_s kevas_row_t;
typedef struct kevas_s kevas_t;
typedef kevas_t KEVAS;

struct kevas_entry_s
{
	char * key;
	void * def;
};

struct kevas_row_s
{
	size_t size;
	kevas_entry_t ** entries;
};

struct kevas_s
{
	size_t table_size;
	kevas_row_t * table;
};

KEVAS * kevas_new(void);

void kevas_destroy(KEVAS * store);

void * kevas_get(KEVAS * store, char * key);

int kevas_set(KEVAS * store, char * key, void * def, void ** old);

int kevas_pop(KEVAS * store, char * key, void ** old);

uint64_t _kevas_hash(char * key);

kevas_entry_t * _kevas_entry_create(char * key, void * def);

void _kevas_entry_free(kevas_entry_t * entry);

void kevas_print(KEVAS * store);

#endif
