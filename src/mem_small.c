/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <assert.h>
#include "mem.h"
#include "mem_internals.h"

void *
emalloc_small(unsigned long size)
{   
    
    void* PTR=NULL;
    if(arena.chunkpool==NULL){
        unsigned long m =mem_realloc_small();
        unsigned long i=0;
        while(m>=CHUNKSIZE){
            void** a=arena.chunkpool+i*96;
            *a=(void*)arena.chunkpool+(i+1)*96;
            m=m-96;
            i=i+1;
        }
        
    }
    if(arena.chunkpool!=NULL){
        void*p=*((void**)arena.chunkpool);
        PTR =mark_memarea_and_get_user_ptr(arena.chunkpool,CHUNKSIZE,SMALL_KIND);
        arena.chunkpool=p;
    }
    
    return (void *) PTR ;
}

void efree_small(Alloc a) {
    void **p=a.ptr;
    *p=arena.chunkpool;
    arena.chunkpool=a.ptr;
    
}
