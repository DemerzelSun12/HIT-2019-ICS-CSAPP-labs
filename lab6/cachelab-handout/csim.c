#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "cachelab.h"

//#define DEBUG_ON 
#define ADDRESS_LENGTH 64
#define MAGIC_LRU_NUM 999

/* Type: Memory address */
typedef unsigned long long int mem_addr_t;

/* Type: Cache line
   LRU is a counter used to implement LRU replacement policy  */
typedef struct cache_line {
    int valid;
    mem_addr_t tag;
	mem_addr_t lru;
} cache_line_t;

typedef struct cache_set_t {
	cache_line_t* cache_line_t_s;
}cache_set_t;

typedef struct cache_t {
	int set_num;
	int line_num;
	cache_set_t* cache_set_t_s;
}cache_t;

/* Globals set by command line args */
int verbosity = 0; /* print trace if set */
int s = 0; /* set index bits */
int b = 0; /* block offset bits */
int E = 0; /* associativity */
char* trace_file = NULL;

/* Derived from command line args */
int S; /* number of sets */
int B; /* block size (bytes) */

/* Counters used to record cache statistics */
int miss_count = 0;
int hit_count = 0;
int eviction_count = 0;
unsigned long long int lru_counter = 1;

/* The cache we are simulating */
mem_addr_t set_index_mask;
cache_t cache;



int findMinLruNumber(cache_t* cache, mem_addr_t Set_Bits) {
	int i, minIndex = 0;
	mem_addr_t minLru = MAGIC_LRU_NUM;
	for (i = 0; i < cache->line_num; i++) {
		if (cache->cache_set_t_s[Set_Bits].cache_line_t_s[i].lru < minLru) {
			minIndex = i;
			minLru = cache->cache_set_t_s[Set_Bits].cache_line_t_s[i].lru;
		}
	}
	return minIndex;
}

int Is_Miss(cache_t* cache, mem_addr_t Set_Bits, mem_addr_t Tag_Bits) {
	int i, j, miss = 1;
	for (i = 0; i < cache->line_num; i++) {
		if (cache->cache_set_t_s[Set_Bits].cache_line_t_s[i].valid == 1 && cache->cache_set_t_s[Set_Bits].cache_line_t_s[i].tag == Tag_Bits) {
			miss = 0;
			cache->cache_set_t_s[Set_Bits].cache_line_t_s[i].lru = MAGIC_LRU_NUM;
			for (j = 0; j < cache->line_num; j++) {
				if (j != i)
					cache->cache_set_t_s[Set_Bits].cache_line_t_s[j].lru--;
			}
			break;
		}
	}
	return miss;
}

int Eviction_Cache(cache_t* cache, mem_addr_t Set_Bits, mem_addr_t Tag_Bits) {
	int i, j, k, full = 1, Eviction_Index;
	for (i = 0; i < cache->line_num; i++) {
		if (cache->cache_set_t_s[Set_Bits].cache_line_t_s[i].valid == 0) {
			full = 0;
			break;
		}
	}
	if (full == 0) {
		cache->cache_set_t_s[Set_Bits].cache_line_t_s[i].valid = 1;
		cache->cache_set_t_s[Set_Bits].cache_line_t_s[i].tag = Tag_Bits;
		cache->cache_set_t_s[Set_Bits].cache_line_t_s[i].lru = MAGIC_LRU_NUM;
		for (j = 0; j < cache->line_num; j++) {
			if (j != i)
				cache->cache_set_t_s[Set_Bits].cache_line_t_s[j].lru--;
		}
	}
	else {
		Eviction_Index = findMinLruNumber(cache, Set_Bits);
		cache->cache_set_t_s[Set_Bits].cache_line_t_s[Eviction_Index].valid = 1;
		cache->cache_set_t_s[Set_Bits].cache_line_t_s[Eviction_Index].tag = Tag_Bits;
		cache->cache_set_t_s[Set_Bits].cache_line_t_s[Eviction_Index].lru = MAGIC_LRU_NUM;
		for (k = 0; k < cache->line_num; k++) {
			if (k != Eviction_Index)
				cache->cache_set_t_s[Set_Bits].cache_line_t_s[k].lru--;
		}
	}
	return full;
}

mem_addr_t GetSet(mem_addr_t addr, int s, int b) {
	mem_addr_t mask = (1 << s) - 1;
	return (addr >> b) & mask;
}

mem_addr_t GetBits(mem_addr_t addr, int s, int b) {
	return addr >> (s + b);
}

/* 
 * initCache - Allocate memory, write 0's for valid and tag and LRU
 * also computes the set_index_mask
 */
void initCache(int s, int E, int b, cache_t* cache)
{
	if (s < 0) {
		printf("Invalid cache sets number!\n");
	}
	cache->set_num = 2 << s;
	cache->line_num = E;
	cache->cache_set_t_s = (cache_set_t*)malloc(cache->set_num * sizeof(cache_set_t));
	if (!cache->cache_set_t_s) {
		printf("Set Memory error\n");
		exit(0);
	}
	int i, j;
	for (i = 0; i < cache->set_num; i++) {
		cache->cache_set_t_s[i].cache_line_t_s = (cache_line_t*)malloc(E * sizeof(cache_line_t));
		if (!cache->cache_set_t_s) {
			printf("Line Memory error\n");
			exit(0);
		}
		for (j = 0; j < E; j++) {
			cache->cache_set_t_s[i].cache_line_t_s[j].valid = 0;
			cache->cache_set_t_s[i].cache_line_t_s[j].lru = 0;
			cache->cache_set_t_s[i].cache_line_t_s[j].tag = 0;
		}
	}
	return;
}


/* 
 * freeCache - free allocated memory
 */
void freeCache(cache_t *cache)
{
	if (cache == NULL)
		return;
	free(cache);
}


/* 
 * accessData - Access data at memory address addr.
 *   If it is already in cache, increast hit_count
 *   If it is not in cache, bring it in cache, increase miss count.
 *   Also increase eviction_count if a line is evicted.
 */
void accessData(cache_t *cache, mem_addr_t addr, unsigned int len, mem_addr_t Set_Bits, mem_addr_t Tag_Bits, int verbosity)
{
	if (Is_Miss(cache, Set_Bits, Tag_Bits) == 1) {
		miss_count++;
		if (verbosity)
			printf("miss ");
		if (Eviction_Cache(cache, Set_Bits, Tag_Bits) == 1) {
			eviction_count++;
			if (verbosity)
				printf("eviction ");
		}
	}
	else {
		hit_count++;
		if (verbosity)
			printf("hit ");
	}
}


/*
 * replayTrace - replays the given trace file against the cache 
 */
void replayTrace(char* trace_fn)
{
    char buf[1000];
    mem_addr_t addr=0;
    unsigned int len=0;
    FILE* trace_fp = fopen(trace_fn, "r");

    if(!trace_fp){
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }

    while(fgets(buf, 1000, trace_fp) != NULL) {

		if (buf[0] == 'I')continue;



        if(buf[1]=='S' || buf[1]=='L' || buf[1]=='M') {
            sscanf(buf+3, "%llx,%u", &addr, &len);
			mem_addr_t Set_Bits = GetSet(addr, s, b);
			mem_addr_t Tag_Bits = GetBits(addr, s, b);
            if(verbosity)
                printf("%c %llx,%u ", buf[1], addr, len);

			if (buf[1] == 'S' || buf[1] == 'L') {
				accessData(&cache, addr, len, Set_Bits, Tag_Bits, verbosity);
			}

            /* If the instruction is R/W then access again */
			if (buf[1] == 'M') {
				accessData(&cache, addr, len, Set_Bits, Tag_Bits, verbosity);
				accessData(&cache, addr, len, Set_Bits, Tag_Bits, verbosity);
			}
            
            if (verbosity)
                printf("\n");
        }
    }

    fclose(trace_fp);
}

/*
 * printUsage - Print usage info
 */
void printUsage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/*
 * main - Main routine 
 */
int main(int argc, char* argv[])
{
    char c;

    while( (c=getopt(argc,argv,"s:E:b:t:vh")) != -1){
        switch(c){
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            verbosity = 1;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }

    /* Make sure that all required command line args were specified */
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }

    /* Compute S, E and B from command line args */
    
 
    /* Initialize cache */
    initCache(s, E, b, &cache);

#ifdef DEBUG_ON
    printf("DEBUG: S:%u E:%u B:%u trace:%s\n", S, E, B, trace_file);
    printf("DEBUG: set_index_mask: %llu\n", set_index_mask);
#endif
 
    replayTrace(trace_file);

    /* Free allocated memory */
    freeCache(cache);

    /* Output the hit and miss statistics for the autograder */
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
