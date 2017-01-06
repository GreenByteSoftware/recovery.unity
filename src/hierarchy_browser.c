#include "hierarchy_browser.h"
#include <stdio.h>
#include <stdlib.h>

void recursive_delete(gameobject *objects, long long size, long long object, char **lines)
{
	if (objects[object].deleted == 1)
		return;
	for (long long i = 0; i < objects[object].children_c; i++)
		for (long long o = 0; o < size; o++)
			if (objects[object].children_names[i] == objects[o].transform_name)
				recursive_delete(objects, size, o, lines);

	printf("Deleting %s\n", objects[object].name_str);
	for (long long o = objects[object].start; o <= objects[object].end; o++)
		lines[o][0] = '\0';
	objects[object].deleted = 1;
	objects[object].name_str = "Deleted";
}

void editMode(gameobject *objects, long long size, long long obj, char **lines) {
	while (1) {
		int choice, valid = 0;
		while (valid == 0) {
			if (objects[obj].prefab == 0)
				printf ("Selected \"%s\" Here is what you can do:\n1. Browse deeper	2. List components\n3. Show object start/end	4. Delete object\n5. Cancel\n", objects[obj].name_str);
			else
				printf ("Selected \"%s\" Here is what you can do:\n1. List components	2. Delete object\n3. Cancel\n", objects[obj].name_str);
			printf ("Enter number: ");
			scanf("%d", &choice);
			if (choice > 0 && choice < 6 && objects[obj].prefab == 0)
				valid = 1;
			else if (choice > 0 && choice < 4 && objects[obj].prefab == 1){
				valid = 1;
				choice += 2;
			} else {
				printf ("Invalid selection. Press enter to continue");
				getc (stdin);
				getc (stdin);
			}
		}

		if (choice == 1) {
			browse(objects, size, lines, obj);
		} else if (choice == 2) {

		} else if (choice == 3) {
			printf ("Start: %lld	End: %lld\n", objects[obj].start+1, objects[obj].end+1);
		} else if (choice == 4) {
			recursive_delete(objects, size, obj, lines);
			break;
		} else if (choice == 5) {
			break;
		}
	}
	printf("Quit edit mode. Press any key to continue");
	getc(stdin);
	getc(stdin);

}

static long long ask_root_obj(gameobject *objects, long long size, long long parent_name)
{
	printf("Listing GameObjects that are children of index %lld\n", parent_name);
	long long o = 0;
	for (long long i = 0; i < size; i++)
		if (parent_name >= 0)
			for (long long p = 0; p < objects[parent_name].children_c; p++) {
				if (objects[i].transform_name == objects[parent_name].children_names[p])
					printf("%lld. %lld	%s\n", ++o, objects[i].tree_size, objects[i].name_str);
			}
		else if (parent_name == -1 && objects[i].parent_name == 0)
			printf("%lld. %lld	%s\n", ++o, objects[i].tree_size, objects[i].name_str);
	printf("-2. Back\n");
	long long n, a = 0;
	printf("Select GameObject: ");
	scanf("%lld", &n);
	
	if (n == -2)
		return -2;
	
	for (long long i = 0; i < size; i++)
		if (parent_name >= 0)
			for (long long p = 0; p < objects[parent_name].children_c; p++) {
				if (parent_name >= 0 && objects[i].transform_name == objects[parent_name].children_names[p] && ++a == n)
					return i;
			}
		else if (parent_name == -1 && objects[i].parent_name == 0 && ++a == n)
			return i;
	return -1;
}

void browse(gameobject *objects, long long size, char **lines, long long parent_object)
{
	while (1) {
		long long obj = ask_root_obj(objects, size, parent_object);
		
		while (obj == -1 || (obj >= 0 && objects[obj].deleted == 1)) {
			printf("Invalid selection. Press any key to retry.");
			getc (stdin);
			getc (stdin);
			obj = ask_root_obj(objects, size, parent_object);
		}

		if (obj >= 0)
			editMode (objects, size, obj, lines);
		else
			break;
	}
}


