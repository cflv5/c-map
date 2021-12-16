#include <stdlib.h>
#include <string.h>

#include "map.h"

#define MAP_BY_VAL 0
#define MAP_BY_REF 1

typedef struct mapitem
{
	char* key;
	void* val;
	int type;
} MI;

typedef struct map
{
	int size;
	MI* items;
} M;

typedef struct mapIterator
{
	int indx;
	M* map;
	MI* item;
} MITR;

M* mapNew()
{
	M* map;

	map = malloc(sizeof(M));
	map->size = 0;
	map->items = NULL;

	return map;
}

void mapAdd(char* key, void* val, M* map)
{
	char* newkey;

	newkey = malloc(strlen(key) + 1);
	strcpy(newkey, key);

	if (map->size == 0)
	{
		map->items = malloc(sizeof(MI));
	}
	else
	{
		map->items = realloc(map->items, sizeof(MI) * (map->size + 1));
	}

	(map->items + map->size)->key = newkey;
	(map->items + map->size)->val = val;
	(map->items + map->size++)->type = MAP_BY_VAL;
}

void mapDynAdd(char* key, void* val, M* map)
{
	mapAdd(key, val, map);
	(map->items + map->size - 1)->type = MAP_BY_REF;
}

void* mapGet(char* key, M* map)
{
	int i;

	for (i = 0; i < map->size; i++)
	{
		if (strcmp((map->items + i)->key, key) == 0)
		{
			return (map->items + i)->val;
		}
	}

	return NULL;
}

void mapClose(M* map)
{
	int i = 0;

	for(; i < map->size; i++)
	{
		free((map->items + i)->key);

		if ((map->items + i)->type == MAP_BY_REF)
		{
			free((map->items + i)->val);
		}
	}

	free(map->items);
	free(map);
}

int getSize(struct map* map)
{
	if(map == NULL)
	{
		return 0;
	}
	return map->size;
}

MITR* getMapIterator(M* map)
{
	MITR *iterator = NULL;

	if (map == NULL)
	{
		return NULL;
	}

	iterator = (MITR *)malloc(sizeof(MITR));
	if (iterator == NULL)
	{
		return NULL;
	}

	iterator->map = map;
	iterator->indx = -1;
	iterator->item = NULL;

	return iterator;
}

int mapIteratorHasNext(MITR* iterator)
{
	int hasNext = 0;
	M* map = NULL;

	if(iterator != NULL)
	{
		map = iterator->map;
		if(map && map->size > 0 && (iterator->indx + 1) < map->size)
		{
			hasNext = 1;
		}
	}

	return hasNext;
}

int mapIteratorNext(MITR* iterator)
{
	M* map = NULL;

	if (iterator == NULL)
	{
		return 1;
	}

	map = iterator->map;
	if(map == NULL)
	{
		return 2;
	}

	if (map->size == 0 || (iterator->indx + 1) >= map->size)
	{
		return 3;
	}
	else
	{
		iterator->indx++;
		iterator->item = (map->items + iterator->indx);
	}

	return 0;
}

void* getIteratorVal(MITR* iterator)
{
	void* item = NULL;

	if(iterator != NULL && iterator->item != NULL)
	{
		item = iterator->item->val;
	}

	return item;
}

char const* getIteratorKey(struct mapIterator* iterator)
{
	char const* key = NULL;

	if (iterator != NULL && iterator->item != NULL)
	{
		key = iterator->item->key;
	}

	return key;
}


void closeIterator(MITR** iterator)
{
	if(*iterator != NULL)
	{
		free(*iterator);
		*iterator = NULL;
	}
}