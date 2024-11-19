typedef struct RandomSourceOperations RandomSourceOperations;
typedef struct RandomSource
{
    RandomSourceOperations *ops;
    void *data;
} RandomSource;

typedef struct RandomSourceOperations
{
    RandomSource *(*destroy)(RandomSource *);
    double (*next)(RandomSource *);
} RandomSourceOperations;
