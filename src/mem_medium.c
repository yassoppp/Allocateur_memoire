/******************************************************
 * Copyright Grégory Mounié 2018                      *
 * This code is distributed under the GLPv3+ licence. *
 * Ce code est distribué sous la licence GPLv3+.      *
 ******************************************************/

#include <stdint.h>
#include <assert.h>
#include "mem.h"
#include "mem_internals.h"

unsigned int puiss2(unsigned long size) {
    unsigned int p=0;
    size = size -1; // allocation start in 0
    while(size) {  // get the largest bit
	p++;
	size >>= 1;
    }
    if (size > (1 << p))
	p++;
    return p;
}


void *
emalloc_medium2(unsigned long size)
{   
   /*if(arena.TZL[17]==NULL){
       mem_realloc_medium();
   }*/

    unsigned int x=puiss2(size);
    /*if(x>TZL_SIZE){
        mem_realloc_medium();
    }*/
    if (arena.TZL[x]!=NULL){
        void* p=arena.TZL[x];
        arena.TZL[x]=*(void**)arena.TZL[x];
        return p;
    }
    else{
        void* p=emalloc_medium2(1<<(x+1));
        if(p!=NULL){
            void* comagnon=(void*)((unsigned long)p ^ (1<<x));
            *(void**)comagnon=arena.TZL[x];
            arena.TZL[x]=comagnon;
        }
        return p;
    }
    
}
void *
emalloc_medium(unsigned long size){
    unsigned int x=puiss2(size);
    int s=0;
    for(int i=x;i<arena.medium_next_exponant+FIRST_ALLOC_MEDIUM_EXPOSANT;i++){
        if(arena.TZL[i]){
            s=s+1;
        }
    }
    if(s==0){
        mem_realloc_medium();
    }
    return mark_memarea_and_get_user_ptr(emalloc_medium2(size),1<<x,1);
}



void efree_medium(Alloc a) {
    unsigned long taille=a.size;
    unsigned int x = puiss2(taille);
    void** p=&arena.TZL[x];
    void* compagnon=(void*)(((unsigned long)a.ptr) ^(1<<(x)));
    while(*p!=NULL && *p!=compagnon){
        p=(void**)*p;
    }
    if(*p !=compagnon){
        void** m= (void**)(a.ptr);
        *m=(void*)arena.TZL[x];
        arena.TZL[x]=(void**)(a.ptr);
    }
    else{
        *p=*(void**)compagnon;
       
        if((unsigned long)a.ptr>(unsigned long )compagnon){
            Alloc c;
            c.ptr=compagnon;
            c.size=(1<<(x+1));
            efree_medium(c);
        }
        else{
            Alloc b;
            b.ptr=a.ptr;
            b.size=(1<<(x+1));
            efree_medium(b);
        }
    }
}


