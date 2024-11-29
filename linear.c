#include "random_source.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
//privet
enum
{
    a = 1103515245,
    c = 12345,
    mod = 1024L * 1024L * 1024L * 2L
};
double
next_lin(RandomSource *rs)
{
    unsigned long long *prev = (unsigned long long *) rs->data;
    unsigned long long new = (a * (*prev) + c) % mod;
    *(prev) = new;
    return (double) new / (double) mod;
}



RandomSource *
destroy_lin(RandomSource *src)
{
    free(src->data);
    free(src->ops);
    free(src);
    return NULL;
}

RandomSource *
random_linear_factory(char *seed)
{
    unsigned long result_seed;
    if (sscanf(seed, "%lu", &result_seed) != 1) {
        return NULL;
    }
    RandomSource *result = malloc(sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    result->ops = malloc(sizeof(*result->ops));
    result->ops->next = next_lin;
    result->ops->destroy = destroy_lin;
    
    result->data = malloc(sizeof(result_seed));
    if (result->data == NULL) {
        free(result);
        return NULL;
    }
    result->ops->next = next_lin;
    result->ops->destroy = destroy_lin;
    *((unsigned long long *) result->data) = (result_seed << 1) >> 1;
    return result;
}

