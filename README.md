# HashTable
__Implementation of hash table with open adressing__

```C
#define HT_PRIME_1 151 
#define HT_PRIME_2 163
```
> We define two randomized prime numbers for hashing functions, which should not be close to the 2 potency.

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
