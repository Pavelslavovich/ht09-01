#include "mtwister.h"
#include "random_source.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
//test1
double
next(RandomSource *rs)
{
    return genRand(rs->data);
}

RandomSource *
destroy(RandomSource *src)
{
    free(src->data);
    free(src->ops);
    free(src);
    return NULL;
}

RandomSource *
random_mt_factory(char *seed)
{
    char *end = NULL;
    errno = 0;
    unsigned long long seedd = strtoull(seed, &end, 10);
    if (errno != 0 || *end || end == seed) {
        return NULL;
    }

    RandomSource *result = malloc(sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    MTRand *r = malloc(sizeof(MTRand));
    if (r == NULL) {
        free(result);
        return NULL;
    }

    MTRand r1 = seedRand((uint32_t) seedd);
    result->data = r;
    memcpy(result->data, &r1, sizeof(r1));
    result->ops = malloc(sizeof(*result->ops));
    result->ops->next = next;
    result->ops->destroy = destroy;

    return result;
}
