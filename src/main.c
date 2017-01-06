#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hierarchy_browser.h"

#define MAX_NAME 128
#define MAX_LINE 1024

void save (char *path, char **lines, long long file_size)
{
	FILE *fop;
	fop = fopen(path, "w");

	for (int o = 0; o < file_size; o++)
		if (lines[o][0] != '\0')
			fprintf(fop, "%s\n", lines[o]);
	fclose(fop);
}

int stcpy(char *a, char *b)
{
	int c = 0;
	while ((a[c] = b[c]) != '\0')c++;

	return 0;
}

int read_lines(FILE *fp)
{
	int l = 0, c;
	while ((c = getc(fp)) != EOF)
		if (c == '\n')
			l++;
	return l; 
}

long long atolla (char *in) {
	long long n = 0, v;
	long long ret = 0;
	
	char arr[2];
	arr[1] = '\0';

	long long o = 0;
	for (o = 0; (in[o]) != '\0'; o++);

	for (long long i = o; (arr[0] = in[i]), i >= 0; i--)
		if ((v = (long long) atoi(arr)) != 0 || arr[0] == '0')
			ret += v * pow(10, n++);
	
	return ret;
}


int recursive_size(gameobject *objects, long long size, long long object)
{

	long long out = 0;
	if (object >= 0)
		for (long long o = 0; o < size; o++)
			for (long long i = 0; i < objects[object].children_c; i++) {
				if (objects[object].children_names[i] == objects[o].transform_name)
					out += recursive_size(objects, size, o);
			}
	else
		for (long long o = 0; o < size; o++)
			if (0 == objects[o].parent_name)
				out += recursive_size(objects, size, o);

	if (object >= 0)
		objects[object].tree_size = out + (objects[object].end - objects[object].start);
	else
		return 0;

	return objects[object].tree_size;
}

int main ()
{
	FILE *fp, *fpt;
	
	char name_in[MAX_NAME], name_out[MAX_NAME];
	
	printf("Enter input and output file names\n");
	
	//char name_in[] = "../scene1.unity", name_out[] = "output.unity";
	scanf("%s %s", name_in, name_out);
	
	fpt = fopen(name_in, "r");
	long long file_size = read_lines(fpt);
	fclose(fpt);

	fp = fopen(name_in, "r");

	printf ("File size: %lld\n", file_size);
	
	char *lines[file_size], l;

	long long go_count = 0;

	for (long long i = 0; i < file_size; i++) {
		char line[MAX_LINE];		
		long long C = -1;
		while ((l = getc(fp)) != '\n') {
			C++;
			if (C >= 0)
				line[C] = l;

		}
		
		line[++C] = '\0';
		lines[i] = malloc( sizeof(char) * C+1);
		memcpy(lines[i], line, sizeof(char) * C+1);

		if(strncmp(lines[i], "--- !u!1 ", 9) == 0)
			go_count++;
		else if(strncmp(lines[i], "--- !u!1001 ", 12) == 0)
			go_count++;

	}

	long long go_index = -1;
	int mode = -1;
	struct gobject objects[go_count];

	long long pr_count = 0;
	long long npr_count = 0;
	long long comp_count = 0;
	long long root_count = 0;
	long long child_count = 0;

	int counted = 0;

	struct array components;

	for (long long o = 0; o < file_size; o++) {
		static char *str;
		
		if(strncmp(lines[o], "%YAML", 5) == 0) {
			str = malloc(sizeof(lines[o]+6));
			memcpy(str, lines[o]+6, sizeof(lines[o]));
			printf("YAML version: %s\n", str);
			free(str);
		} else if (strncmp(lines[o], "%TAG", 4) == 0 && strncmp(lines[o], "%TAG !u! tag:unity3d.com", 24) != 0) {
			
			printf("ERROR: Not Unity TAG!\n");
			return -1;
		} else if(strncmp(lines[o], "--- !u!1 ", 9) == 0) {
			if (mode == 2)
				objects[go_index].comps.data[objects[go_index].comps.size-1].end = o-1;
			counted = 0;
			npr_count++;
			if (go_index >= 0)
				vector_free(&objects[go_index].comps);
			if (go_index >= 0)
				objects[go_index].end = o - 1;
			go_index++;
			vector_init(&objects[go_index].comps);
			objects[go_index].deleted = 0;
			objects[go_index].component_count = 0;
			objects[go_index].component_capacity = 0;
			objects[go_index].children_c = 0;
			objects[go_index].parent_name = -1;
			objects[go_index].prefab = 0;
			components.capacity = 0;
			components.size = 0;
			mode = 0;
			objects[go_index].start = o;
			objects[go_index].name = atolla(lines[o]+10);
		} else if(strncmp(lines[o], "--- !u!1001 ", 11) == 0) {
			if (mode == 2)
				objects[go_index].comps.data[objects[go_index].comps.size-1].end = o-1;
			counted = 0;
			pr_count++;
			if (go_index >= 0)
				vector_free(&objects[go_index].comps);
			if (go_index >= 0)
				objects[go_index].end = o - 1;
			go_index++;
			vector_init(&objects[go_index].comps);
			objects[go_index].deleted = 0;
			objects[go_index].name_str = "Prefab";
			objects[go_index].component_count = 0;
			objects[go_index].component_capacity = 0;
			objects[go_index].children_c = 0;
			objects[go_index].parent_name = -1;
			objects[go_index].prefab = 1;
			components.capacity = 0;
			components.size = 0;
			mode = 0;
			objects[go_index].start = o;
			objects[go_index].name = atolla(lines[o]+13);
		} else if(mode == 0 && strncmp(lines[o], "  m_Name: ", 9) == 0) {
			objects[go_index].name_str = malloc(sizeof(char) * strlen(lines[o]));
			memcpy(objects[go_index].name_str, lines[o]+10, sizeof(char) * strlen(lines[o]));
		} else if(strncmp(lines[o], "--- !u!4 ", 9) == 0) {
			if (mode == 2)
				objects[go_index].comps.data[objects[go_index].comps.size-1].end = o-1;
			mode = 1;
			str = malloc(sizeof(lines[o]+10));
			memcpy(str, lines[o]+10, sizeof(char) * 10);
			objects[go_index].transform_name = atolla(str);
			free(str);
		} else if(strncmp(lines[o], "--- !u!224 ", 11) == 0) {
			if (mode == 2)
				objects[go_index].comps.data[objects[go_index].comps.size-1].end = o-1;
			mode = 1;
			str = malloc(sizeof(lines[o]));
			memcpy(str, lines[o]+12, sizeof(char) * 10);
			free(str);
		} else if(mode == 1 && strncmp(lines[o], "  m_Children:", 13) == 0 && strncmp(lines[o], "  m_Children: []", 16) != 0) {
			long long p = 0;
			for (p = o+1; strncmp(lines[p], "  - {fileID: ", 13) == 0; p++);
			long long *names = malloc(sizeof(long long) * (p-o-1));
			objects[go_index].children_c = p-o-1;
			for (int u = 0; u < p-o-1; u++)
				names[u] = atolla(lines[o+u+1] + 13);

			objects[go_index].children_names = names;
			
		} else if(mode == 1 && counted == 0 && strncmp(lines[o], "  m_Father: ", 11) == 0) {
			counted = 1;
			objects[go_index].parent_name = atolla(lines[o]+20);
			if (objects[go_index].parent_name == 0)
				root_count++;
			else
				child_count++;
		} else if(mode == 0 && counted == 0 && strncmp(lines[o], "    m_TransformParent: ", 23) == 0) {
			counted = 1;
			objects[go_index].parent_name = atolla(lines[o]+31);
			if (objects[go_index].parent_name == 0)
				root_count++;
			else
				child_count++;
		} else if((mode == 0 || mode == 1 || mode == 2) && strncmp(lines[o], "--- !u!", 5) == 0) {
			comp_count++;
			if (mode == 2)
				objects[go_index].comps.data[objects[go_index].comps.size-1].end = o-1;
			mode = 2;
			str = malloc(sizeof(char) * MAX_LINE);
			strncpy(str, lines[o+1], strlen(lines[o+1]));
			str[strlen(lines[o+1])-1] = '\0';
			vector_append(&objects[go_index].comps, new_comp(o, o, str));
			free(str);
		}	

	}
		
	recursive_size(objects, go_count, -1);
	
	printf("\nStatistics:\n\nGameObjects: %lld\nPrefabs: %lld\nRemoveable Components: %lld\nTransform Roots: %lld\nTransform Children: %lld\n\n", npr_count, pr_count, comp_count, root_count, child_count);
	
	int n = -1;
	
	while (1) {
		printf("Choose what to do:\n1. Enter edit mode	2. Write changes\n3. Exit without writing changes\nEmter number: ");
		scanf("%d", &n);

		if (n == 1)
			browse(objects, go_count, lines, -1);
		else if (n == 2)
			save(name_out, lines, file_size);
		else if (n == 3)
			break;
	}
	return 0;
}
