
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector_comp.h"

void vector_init(Vector_Comp *vector)
{
  vector->size = 0;
  vector->capacity = VECTOR_INITIAL_CAPACITY;

  vector->data = malloc(sizeof(component) * vector->capacity);
}

void vector_append(Vector_Comp *vector, component value)
{
  vector_double_capacity_if_full(vector);

  vector->data[vector->size++] = value;
}

component new_comp(long long start, long long end, char *name)
{
	component ret;
	ret.start = start;
	ret.end = end;
	ret.name = malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(ret.name, name);
	return ret;
}

component vector_get(Vector_Comp *vector, long long index)
{
  if (index >= vector->size || index < 0) {
    printf("Index %lld out of bounds for vector of size %lld\n", index, vector->size);
    exit(1);
  }
  return vector->data[index];
}

void vector_set(Vector_Comp *vector, long long index, component value)
{
  while (index >= vector->size) {
    vector_append(vector, new_comp(0, 0, ""));
  }

  vector->data[index] = value;
}

void vector_double_capacity_if_full(Vector_Comp *vector)
{
  if (vector->size >= vector->capacity) {
    vector->capacity *= 2;
    vector->data = realloc(vector->data, sizeof(component) * vector->capacity);
  }
}

void vector_free(Vector_Comp *vector)
{
  free(vector->data);
}
