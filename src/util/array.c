

#include "array.h"
#include "alloc.h"

#include <string.h>

// both return whether resizing is successful
static bool __array_resize__(array_t a, unsigned long n);
static bool __array_expand_to_fit_more__(array_t a, unsigned long more);

array_t array_new(unsigned long size)
{
    array_t a;

    a = (array_t) mem_alloc(sizeof(struct array_s));
    if (!a) {
        return NULL;
    }
 
    a->elts   = NULL;
    a->nelts  = 0;
    a->nalloc = 0;
    a->size   = size;

    return a;
}

array_t array_newlen(unsigned long size, unsigned long n)
{
    array_t a;

    a = (array_t) mem_alloc(sizeof(struct array_s));
    if (!a) {
        return NULL;
    }

    a->elts = (array_t) mem_alloc(size * n);
    if (!a->elts) {
        return NULL;
    }

    a->nelts  = 0;
    a->nalloc = n;
    a->size   = size;

    return a;
}

void array_free(array_t a)
{
    if (a->elts) {
        mem_free(a->elts);
    }
    mem_free(a);
}

void *array_index(array_t a, unsigned long index)
{
    if (a->nelts <= index) {
        return NULL;
    }

    return (void*)((unsigned char *)a->elts + a->size * index);
}

void array_push(array_t a, void* ptr)
{
    void *elt;
    unsigned char *p;
    if (!__array_expand_to_fit_more__(a, 1)) {
        return;
    }

    elt = (unsigned char *)a->elts + a->size * a->nelts;
    p = (unsigned char*) a->elts;
    memcpy(p + a->size * a->nelts, ptr, a->size);
    a->nelts++;
}

static bool __array_resize__(array_t a, unsigned long n)
{
    unsigned long size = a->size * n;
 
    if (size) {
        a->elts = mem_realloc(a->elts, size);
        if (!a->elts) {
            return false;
        }
    }

    a->nalloc = n;
    
    return true;
}

static bool __array_expand_to_fit_more__(array_t a, unsigned long more)
{
    if (a->nelts + more > a->nalloc) {
      unsigned long nalloc = 2 * (more >= a->nalloc ? more : a->nalloc);
      return __array_resize__(a, nalloc);
    }
    return true;
}
