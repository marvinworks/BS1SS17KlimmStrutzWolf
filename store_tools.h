//
// Created by User on 11.05.2017.
//

#ifndef BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H
#define BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H

#include <stdio.h>

struct key_value{
    int key;
    char *value;
};
struct key_value kv[10];

int put(int key, char *value, struct key_value kv[]);
char* get(int key, struct key_value kv[]);
char* delete(int key, struct key_value kv[]);

#endif //BS1SS17KLIMMSTRUTZWOLF_STORE_TOOLS_H
