#include "vector_comp.h"
#include "vector_str.h"

typedef struct gobject {
	long long name;
	char *name_str;
	long long transform_name;

	int deleted;

	long long children_c;
	long long *children_names;
	struct gobject *children;
	long long parent_name;
	long long component_count;
	long long component_capacity;
	char **components;
	Vector_Comp comps;

	int prefab;
	
	long long tree_size;
	long long start;
	long long end;
} gameobject;


struct array {
	long long size;
	long long capacity;
	char **values;
};

