#include <stdio.h>
#include <stddef.h>

struct llist_head {
	struct llist_node *first;
};

struct llist_node {
	struct llist_node *next;
};

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

/**
 * llist_entry - get the struct of this entry
 * @ptr:	the &struct llist_node pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the llist_node within the struct.
 */
#define llist_entry(ptr, type, member)		\
	container_of(ptr, type, member)

#define llist_for_each_entry(pos, node, member)				\
	for ((pos) = llist_entry((node), typeof(*(pos)), member);	\
	     &(pos)->member != NULL;					\
	     (pos) = llist_entry((pos)->member.next, typeof(*(pos)), member))
/* #define llist_for_each_entry(pos, node, member)				\ */
/* 	for ((pos) = llist_entry((node), typeof(*(pos)), member);	\ */
/* 	     (pos) != llist_entry(NULL, typeof(*(pos)), member);	\ */
/* 	     (pos) = llist_entry((pos)->member.next, typeof(*(pos)), member)) */

struct va {
	int i;
	struct llist_node purge_list;
};

struct va va2 = { 2, { NULL }};
struct va va1 = { 1, { &va2.purge_list }};
/* struct llist_node *valist = &va2.purge_list; */
struct llist_node *valist = NULL;

void foo(struct va *va) {
	if (&va->purge_list != 0)
		printf("Buggy!\n");
}

int main(int argc, char *argv[]) {
	struct va *va;

	va = llist_entry(valist, typeof(*va), purge_list);
	foo(va);

	/* llist_for_each_entry(va, valist, purge_list) { */
	/* 	printf("%d\n", va->i); */
	/* } */

	return 0;
}
