#define VECTOR_INITIAL_CAPACITY 100

typedef struct {
	char *value;
} str;

typedef struct {
  long long size;
  long long capacity;
  str *data;
} Vector_Str;

void str_vector_init(Vector_Str *vector);

void str_vector_append(Vector_Str *vector, char *value);

char* str_vector_get(Vector_Str *vector, long long index);

void str_vector_set(Vector_Str *vector, long long index, char *value);

void str_vector_double_capacity_if_full(Vector_Str *vector);

void str_vector_free(Vector_Str *vector);
