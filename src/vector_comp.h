#define VECTOR_INITIAL_CAPACITY 100

typedef struct {
	long long start;
	long long end;
	char *name;
} component;

typedef struct {
  long long size;
  long long capacity;
  component *data;
} Vector_Comp;

void vector_init(Vector_Comp *vector);

void vector_append(Vector_Comp *vector, component value);

component new_comp(long long start, long long end, char *name);

component vector_get(Vector_Comp *vector, long long index);

void vector_set(Vector_Comp *vector, long long index, component value);

void vector_double_capacity_if_full(Vector_Comp *vector);

void vector_free(Vector_Comp *vector);
