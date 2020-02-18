#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdio.h>

#include "hashTable.h"

#define HT_PRIME_1 151 
#define HT_PRIME_2 163

static ht_item HT_DELETED_ITEM = {NULL, NULL};

// Initialize the new items
static ht_item* ht_new_item(const char* k, const char* v){
	ht_item* i = malloc(sizeof(ht_item));
	i -> key = strdup(k);
	i -> value = strdup(v);
	return i;
}

// intialize a new hashtable
ht_hash_table* ht_new(){
	ht_hash_table* ht = malloc(sizeof(ht_hash_table));
	
	ht -> size = 53;
	ht -> count = 0;
	ht -> items = calloc((size_t) ht -> size, sizeof(ht_item*));
	printf("A new hash table is created\n");
	return ht;
}

static void ht_del_item(ht_item* i){
	free(i -> key);
	free(i -> value);
	free(i);
}

void ht_del_hash_table(ht_hash_table* ht){
	for(int i = 0; i < ht -> size; i++){
		ht_item* item = ht -> items[i];
		if(item != NULL){
			ht_del_item(item);
		}
		free(ht -> items);
		free(ht);
	}
}

static int ht_hash(const char* s, const int a, const int m){
	long hash = 0;
	const int len_s = strlen(s);
	for(int i = 0; i < len_s; i++){
		hash += (long)pow((double)a, (double)len_s - (i + 1)) * s[i];
		hash %= m;
	}
	return (int)m;
}

// using open adressing and double hashing
static int ht_get_hash(const char* s, const int num_buckets, const int attempt){
	const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
	const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
	return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value){
	ht_item* item = ht_new_item(key, value);
	int index = ht_get_hash(item -> key, ht -> size, 0);
	ht_item* cur_item = ht -> items[index];
	int i = 1;
	
	while(cur_item != NULL){
		if(cur_item != &HT_DELETED_ITEM){
			if(strcmp(cur_item -> key, key) == 0){
				ht_del_item(cur_item);
				ht -> items[index] = item;
				return;
			}
		}
		index = ht_get_hash(item -> key, ht -> size, i);
		cur_item = ht -> items[index];
		i ++;
	}
	ht -> items[index] = item;
	ht -> count ++;
}

char* ht_search(ht_hash_table* ht, const char* key){
	int index = ht_get_hash(key, ht -> size, 0);
	ht_item* item = ht -> items[index];
	int i = 1;
	
	while(item != NULL){
		if(item != & HT_DELETED_ITEM){
			if(strcmp(item -> key, key) == 0){
				return item -> value;
			}
		}
		index = ht_get_hash(key, ht -> size, i);
		i ++;
		item = ht -> items[index];
	}
	return NULL;
}

void ht_delete(ht_hash_table* ht, const char* key){
	int index = ht_get_hash(key, ht -> size, 0);
	ht_item* item = ht -> items[index];
	int i = 1;
	while(item != NULL){
		// To update the value whose key is already stored in the hash table
		if(item != &HT_DELETED_ITEM){
			if(strcmp(item -> key, key) == 0){
				ht_del_item(item);
				ht -> items[index] = &HT_DELETED_ITEM;
			}
		}
		index = ht_get_hash(key, ht -> size, i);
		i ++;
		item = ht -> items[index];
	}
	ht -> count --;
}

void print_hash_table(ht_hash_table* ht){
	for(int i = 0; i < ht -> size; i++){
		if(ht -> items[i] != NULL){
			printf("The key is: %s and the value is %s \n", ht -> items[i] -> key, ht -> items[i] -> value);
		}
	}
}

int main(){
	ht_hash_table* ht = ht_new();
	ht_insert(ht, "1", "2");
	ht_insert(ht, "2", "3");
	print_hash_table(ht);
	//ht_del_hash_table(ht);
	return 0;
}
