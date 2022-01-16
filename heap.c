#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

heap heap_create(int k, int (*f)(const void *, const void *))
{
  void **array = malloc((k + 1) * sizeof(*array));
  heap h = malloc(sizeof(heap));
  h->array = array;
  h->f = f;
  h->n = 0;
  h->nmax = k;
  return h;
}

void heap_destroy(heap h)
{
  printf("coucou");
  for (int i = 0; i < h->nmax+1; i++)
  {
    free(h->array[i]);
  }
  free(h->array[0]);
  free(h->array);
  free(h->f);
  free(h);
}

bool heap_empty(heap h)
{
  return h->n == 0;
}

bool heap_add(heap h, void *object)
{
  if (h->n < h->nmax)
  {
    h->array[h->n + 1] = object;
    h->n = h->n + 1;
    if (h->n > 1)
    {
      if(h->f(h->array[h->n],h->array[(h->n)/2])<0){
      h->array[0]=object;
      h->array[h->n]=h->array[(h->n)/2];
      h->array[(h->n)/2]=h->array[0];
    }
    }
    return false;
  }
  return true;
}

void *heap_top(heap h)
{
  if(h->n>0){
    return h->array[1];
  }
  return NULL;
}

void *heap_pop(heap h) {

  assert(h != NULL);

  void * racine = heap_top(h);
  if(racine == NULL)return NULL;

  // void * tmpI = racine; 
  h->array[1] = h->array[h->n];
  // h->array[h->n] = tmpI;

  h->n--;

  //Comparaison
  int i = 1;
  while (i <= h->n/2 
  && (h->f(h->array[i*2], h->array[i]) < 0 || h->f(h->array[i*2+1], h->array[i]) < 0))
  {
    int minI = h->f(h->array[i*2], h->array[i*2+1]) < 0 ? i*2 : i*2+1;

    //swap
    void * tmp = h->array[i];
    h->array[i] = h->array[minI];
    h->array[minI] = tmp;

    i = minI;
  }  

  return racine;
}