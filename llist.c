#include <stdio.h>
#include <stdlib.h>


// ==============================
// Linked List
// ==============================


// Structure -> List Node
typedef struct llist_node {
	struct llist_node* next;
	void* value;
} llist_node;

typedef unsigned char llist_bool;

// True / false
#define llist_true 1
#define llist_false 0

// Null
#define llist_null 0

// Structure -> List representation
typedef struct {
	int len;
	llist_node* start;
	llist_node* last;
} llist;

// List functions
// ==============

// Get Linked list length
int llist_len(llist* l) {
	int len = l->len;
	if (len < -1) {
		return -1;
	}
	return l->len;
}

// Get node by id
// Can return `llist_null` if fail
llist_node* llist_get_node(llist* l, int id) {
	if (l->len < 1 || id < 0)		return llist_null;
	else if (id == 0) 				return l->start;
	else if (id >= llist_len(l))	return llist_null;
	if (l->start == llist_null) 	return llist_null;

	llist_node* node;
	node = l->start;

	// We skip 0 element as it is 'start' object inside list
	for (int i = 0; i < id; i++) {
		node = node->next;
		if (node == llist_null)		return llist_null;
	}

	return node;
}

// Get value by id
// Can return `llist_null` if fail
void* llist_get(llist* l, int id) {
	llist_node* node = llist_get_node(l, id);
	if (node == llist_null) 		return llist_null;
	return node->value;
}

// Create new Linked List
// Need to be freed before finishing with that
llist* llist_new() {
	llist* list = (llist*) malloc(sizeof(llist));
	list->len = 0;
}

// Used to free up the memory
// Need to be called always when done with List
void llist_free(llist* l) {
	llist_node* node = l->start;
	// Clear all nodes
	if (node != llist_null) {
		while (1) {
			llist_node* next = node->next;
			free(node);
			node = next;
			if (node->next == llist_null) break;
		}
	}
	// Clear list
	free(l);
}

llist_node* llist_node_new(void *elem) {
	llist_node* node = malloc(sizeof(llist_node));
	node->next = llist_null;
	node->value = elem;
	return node;
}

// Add element to the List
// Returns new length after element had added
// Return the same length if element is not added successfuly
int llist_add(llist* l, void* elem) {
	if (l->len == 0) {
		l->start = llist_node_new(elem);
		l->len = 1;
		l->last = l->start;
		return 1;
	}
	if (l->last != llist_null) {
		llist_node* new_node = llist_node_new(elem);
		llist_node* prev_last_node = l->last;
		prev_last_node->next = new_node;
		l->last = new_node;
		l->len++;
	}
	return l->len;
}

// Remove element from list
// Returns `llist_true` if all is OK and `llist_false` if not removed or not exist
llist_bool llist_remove(llist* l, int id) {
	if (l->len < 1) {
		return llist_false;
	}
	if (id < 0 || id >= l->len) return llist_false;
	// If we remove first element
	if (id == 0) {
		if (l->start == llist_null) return llist_false;
		l->start = l->start->next;
		l->len--;
		return llist_true;
	} else { // If we want to remove not the first element
		// Get previous Node
		llist_node* prev = llist_get_node(l, id-1);
		// Get Node which need to be removed
		llist_node* curr = llist_get_node(l, id);
		// Get next Node if exists
		llist_node* next =  curr->next;
		// If next Node is not exist, then this node is the last one, so the previous one will became [l->last].
		if (next == llist_null) {
			l->last = prev;
		}
		// Remove current Node
		// Previous node will link to the next one, by skipping current
		// If next one is [llist_null] then it is ok.
		prev->next = next;
		free(curr);
		l->len--;
		return llist_true;
	}
}

// Puller
// ===

// Structure -> Puller
typedef struct list_puller {
	llist_node* node;
} llist_puller;

// Create list iterator to iterate over each element of the list
// Need to be freed before finishing with that
llist_puller* llist_puller_new(llist* l) {
	llist_puller* it = malloc(sizeof(llist_puller));
	it->node = l->start;
	return it;
}

// Pull items from Puller until `llist_null` will be returned
void* llist_puller_pull(llist_puller* it) {
	if (it->node == llist_null) return llist_null;
	void* value = it->node->value;
	it->node = it->node->next;
	return value;
}

void llist_puller_free(llist_puller* it) {
	free(it);
}