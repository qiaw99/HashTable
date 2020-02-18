# HashTable
__Implementation of hash table with open adressing__

```C
#define HT_PRIME_1 151 
#define HT_PRIME_2 163
```
> We define two randomized prime numbers for hashing functions, which should not be close to the 2 potency.

__Use of generic string hashing function, expressed below in pseudocode.__
```
function hash(string, a, num_buckets):
    hash = 0
    string_len = length(string)
    for i = 0, 1, ..., string_len:
        hash += (a ** (string_len - (i+1))) * char_code(string[i])
    hash = hash % num_buckets
    return hash
```

```C
static int ht_hash(const char* s, const int a, const int m){
	long hash = 0;
	const int len_s = strlen(s);
	for(int i = 0; i < len_s; i++){
		hash += (long)pow((double)a, (double)len_s - (i + 1)) * s[i];
		hash %= m;
	}
	return (int)m;
}
```
> Using double hashing function: (h1(x) + i*h2(x)) mod size

__Deleting the element from hash table, which is implemented by open adressing, is unfortunately difficult rather than insert() and search. Because we couldn't just set the slot NULL. If we do that, we couldn't get the value while searching the elements which are stored after the deleted slot. The solution is that we mark this slot "deleted".__
```C
void ht_delete(ht_hash_table* ht, const char* key){
	int index = ht_get_hash(key, ht -> size, 0);
	ht_item* item = ht -> items[index];
	int i = 1;
	while(item != NULL){
		if(item != &HT_DELETED_ITEM){
			if(strcmp(item -> key, key) == 0){
				ht_del_item(item);
				// mark the slot "deleted"
				ht -> items[index] = &HT_DELETED_ITEM;
			}
		}
		index = ht_get_hash(key, ht -> size, i);
		i ++;
		item = ht -> items[index];
	}
	ht -> count --;
}
```
