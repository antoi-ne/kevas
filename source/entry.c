#include "kevas.h"
#include <stdlib.h>
#include <string.h>

kevas_entry_t * _kevas_entry_create(char * key, void * def)
{
	kevas_entry_t * entry;

	entry = malloc(sizeof(kevas_entry_t));
	if (entry == NULL)
		return (NULL);

	entry->key = strdup(key);
	if (entry->key == NULL)
	{
		free(entry);
		return (NULL);
	}

	entry->def = def;

	return entry;
}

void _kevas_entry_free(kevas_entry_t * entry)
{
	free (entry->key);
	free(entry);
}
