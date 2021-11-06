#include "kevas.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

KEVAS * kevas_new(void)
{
	kevas_t * store;

	store = malloc(sizeof(kevas_t));
	if (store == NULL)
		return (NULL);

	store->table_size = 16;
	store->table = malloc(sizeof(kevas_row_t) * store->table_size);
	if (store->table == NULL)
	{
		free(store);
		return (NULL);
	}
	memset(store->table, 0, sizeof(kevas_row_t) * store->table_size);

	return (store);
}

void kevas_destroy(KEVAS * store)
{
	// TODO: implement
}

void * kevas_get(KEVAS * store, char * key)
{
	uint64_t index;
	kevas_row_t * row;
	size_t i;

	index = _kevas_hash(key) % store->table_size;
	row = &store->table[index];
	
	i = 0;
	while (i < row->size)
	{
		if (strcmp(key, row->entries[i]->key) == 0)
			return (row->entries[i]->def);
		i++;
	}

	return (NULL);
}

int kevas_set(KEVAS * store, char * key, void * def, void ** old)
{
	uint64_t index;
	kevas_row_t * row;
	kevas_entry_t ** new_entries;
	size_t i;
	kevas_entry_t * current_entry;

	index = _kevas_hash(key) % store->table_size;
	row = &store->table[index];

	i = 0;
	current_entry = NULL;
	while (i < row->size && current_entry == NULL)
	{
		if (strcmp(key, row->entries[i]->key) == 0)
			current_entry = row->entries[i];
		i++;
	}

	if(current_entry == NULL)
	{
		new_entries = malloc(sizeof(kevas_entry_t **) * (row->size + 1));
		memcpy(new_entries, row->entries, sizeof(kevas_entry_t **) * row->size);

		new_entries[row->size] = _kevas_entry_create(key, def);
		if (new_entries[row->size] == NULL)
		{
			free(new_entries);
			return (0);
		}

		row->size++;
		free(row->entries);
		row->entries = new_entries;

		*old = NULL;
	}
	else
	{
		*old = current_entry->def;
		current_entry->def = def;
	}

	return (0);
}

// TODO: special case when last entry of row removed
int kevas_pop(KEVAS * store, char * key, void ** old)
{
	size_t i;
	uint64_t index;
	uint64_t entry_index;
	kevas_row_t * row;
	kevas_entry_t * current_entry;
	kevas_entry_t ** new_entries;

	index = _kevas_hash(key) % store->table_size;
	row = &store->table[index];

	i = 0;
	current_entry = NULL;
	while (i < row->size && current_entry == NULL)
	{
		if (strcmp(key, row->entries[i]->key) == 0)
		{
			current_entry = row->entries[i];
			entry_index = i;
		}
		i++;
	}

	*old = current_entry->def;

	if (current_entry == NULL)
		return (0);

	new_entries = malloc(sizeof(kevas_entry_t **) * (row->size - 1));
	if (new_entries == NULL)
	{
		*old = NULL;
		return (1);
	}

	memcpy(new_entries, row->entries, entry_index * sizeof(kevas_entry_t **));

	memcpy(new_entries + entry_index, row->entries + entry_index + 1, (row->size - entry_index - 1) * sizeof(kevas_entry_t **));

	free (row->entries);

	row->entries = new_entries;

	_kevas_entry_free(current_entry);

	row->size--;

	return (0);
}

// TODO: remove or modify for prod
void kevas_print(KEVAS * store)
{
	printf("start\n");
	for(size_t i = 0; i < store->table_size; i++)
	{
		printf("%2zu   ", i);
		if (store->table[i].size == 0)
		{
			printf("---");
		}
		else
		{
			for(size_t j = 0; j < store->table[i].size; j++)
			{
				printf("'%s': %p, ", store->table[i].entries[j]->key, store->table[i].entries[j]->def);
			}
		}
		printf("\n");
	}
	printf("end\n");
}
