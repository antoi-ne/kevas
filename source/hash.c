#include "kevas.h"

// djb2 hash function
uint64_t _kevas_hash(char *key)
{
	uint64_t hash;
	char c;

	hash = 5381;
	
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c;

	return (hash);
}
