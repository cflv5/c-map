#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

void callback()
{
	printf("Hello World !\n");
}

int main()
{
	struct map* m;
	struct map* map;
	struct mapIterator* iterator = NULL;

	char *strval;
	int intval;
	void (*funcval)();
	char* dynval = malloc(7);
	void* val;
	char const* key;

	m = mapNew();
	strcpy(dynval, "dynval");

	mapAdd("key 1", "value", m);
	mapDynAdd("key 2", dynval, m);
	mapAdd("key 3", (int*) 21, m); // Casted to avoid warning
	mapAdd("key 4", callback, m);

	strval = mapGet("key 1", m);
	intval = (long) mapGet("key 3", m); // Casted to avoid warning
	funcval = mapGet("key 4", m);

	printf("%s\n", strval);
	printf("%d\n", intval);
	funcval();


    iterator = getMapIterator(m);
	printf("\nIterator has next: %s\n", mapIteratorHasNext(iterator) ? "true": "false");

	while (mapIteratorNext(iterator) == 0)
	{
		key = getIteratorKey(iterator);
		val = getIteratorVal(iterator);

		printf("Key: %s\tVal: %p\n", key, val);
	}

	closeIterator(&iterator);
	printf("\nIterator closed. Iterator: %p\n", iterator);
	printf("Iterator after closed has next: %s\n", mapIteratorHasNext(iterator) ? "true" : "false");

	map = mapNew();
	iterator = getMapIterator(map);
	printf("\nIterator on empty map has next: %s\n", mapIteratorHasNext(iterator) ? "true" : "false");
	closeIterator(&iterator);

	mapClose(m);
	mapClose(map);

	return 0;
}
