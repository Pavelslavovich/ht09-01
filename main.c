#include "random_source.h"
#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int
main(int argc, char *argv[])
{
    if (argc < 4) {
        return EXIT_FAILURE;
    }

    char *end = NULL;
    errno = 0;
    unsigned long long n = strtoull(argv[2], &end, 10);
    if (errno != 0 || *end || end == argv[2] || n > 100000) {
        return EXIT_FAILURE;
    }

    void *handle = dlopen(NULL, RTLD_LAZY);
    if (!handle) {
        perror("dlopen");
        return EXIT_FAILURE;
    }

    RandomSource *(*random_factory)(const char *);
    if (!strcmp(argv[1], "mt")) {
        random_factory = dlsym(handle, "random_mt_factory");
    } else if (!strcmp(argv[1], "linear")) {
        random_factory = dlsym(handle, "random_linear_factory");
    } else {
        dlclose(handle);
        return EXIT_FAILURE;
    }

    if (!random_factory) {
        dlclose(handle);
        perror("dlsym");
        return EXIT_FAILURE;
    }

    RandomSource *gen = (*random_factory)(argv[3]);
    if (!gen) {
        dlclose(handle);
        return EXIT_FAILURE;
    }

    for (unsigned long long i = 0; i < n; i++) {
        printf("%.10g\n", gen->ops->next(gen));
    }

    gen->ops->destroy(gen);
    dlclose(handle);

    return EXIT_SUCCESS;
}
