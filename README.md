# Linked List realization in C
Look at the example
```c
int main() {
	
	// Create list
	llist* list = llist_new();


	// Add elements into it (For example strings)
	llist_add(list, "Hello!\0");
	llist_add(list, "Hi Jack!\0");
	llist_add(list, "I am SECRET MESSAGE!\0");
	llist_add(list, "Fox n Go!\0");

	// Remove element (For example element: 2)
	// Has to return: llist_true
	llist_bool removing = llist_remove(list, 2);

	// Iterate over it
	llist_puller* p = llist_puller_new(list);
	while (1) {
		// Read each value
		char* str = (char*) llist_puller_pull(p);

		// Break when list ended
		if (str == llist_null) break;

		// Print each value
		printf("%s\n", str);
	}
	
	
	// Get and print list Length
	int len = list->len;
	printf("%d\n", list->len);

	// Free List after using
	llist_free(list);




	return 0;
}
```
