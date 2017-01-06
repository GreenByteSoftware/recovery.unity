
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector_str.h"

static char* dupstring(char* value)
{
	char *ret = malloc(sizeof(char) * (strlen(value) + 1));
	strcpy(ret, value);
	return ret;
}

void str_vector_init(Vector_Str *vector)
{
  vector->size = 0;
  vector->capacity = VECTOR_INITIAL_CAPACITY;

  vector->data = malloc(sizeof(str) * vector->capacity);
}

void str_vector_append(Vector_Str *vector, char *value)
{
  str_vector_double_capacity_if_full(vector);

  vector->data[vector->size++].value = dupstring(value);
}

char* str_vector_get(Vector_Str *vector, long long index)
{
  if (index >= vector->size || index < 0) {
    printf("Index %lld out of bounds for vector of size %lld\n", index, vector->size);
    exit(1);
  }
  return vector->data[index].value;
}

void str_vector_set(Vector_Str *vector, long long index, char* value)
{
  while (index >= vector->size) {
    str_vector_append(vector, "");
  }

  vector->data[index].value = strdup(value);
}

void str_vector_double_capacity_if_full(Vector_Str *vector)
{
  if (vector->size >= vector->capacity) {
    vector->capacity *= 2;
    vector->data = realloc(vector->data, sizeof(str) * vector->capacity);
  }
}

void str_vector_free(Vector_Str *vector)
{
  free(vector->data);
}
