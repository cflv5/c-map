#ifndef MAP_H
#define MAP_H

struct map;
struct mapIterator;

struct map* mapNew();
void mapAdd(char* key, void* val, struct map* map);
void mapDynAdd(char* key, void* val, struct map* map);
void* mapGet(char* key, struct map* map);
void mapClose(struct map* map);

struct mapIterator* getMapIterator(struct map* map);
int mapIteratorHasNext(struct mapIterator* iterator);
int mapIteratorNext(struct mapIterator* iterator);
void* getIteratorVal(struct mapIterator* iterator);
char const* getIteratorKey(struct mapIterator* iterator);
void closeIterator(struct mapIterator** iterator);

#endif
