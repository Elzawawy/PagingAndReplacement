#ifndef MEM_MANAGER_H_
#define MEM_MANAGER_H_

typedef enum ReplacementPolicy
{
    FIFO=0,
    LRU,
    CLOCK
}ReplacementPolicy;

void pageReplacer_init(int numOfPages, ReplacementPolicy policy);
int requestPage(int pageReference);

#endif