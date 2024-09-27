#include <stdio.h>
#include <stdlib.h>

// Struct for a linked list node
typedef struct Node {
    void *address;  // Pointer to the allocated memory
    size_t size;    // Size of the allocated memory
    struct Node *next;
} Node;

// Function to manage the static head of the linked list
Node **gc_get_head() {
    static Node *head = NULL;  // Static variable to hold the head of the linked list
    return &head;              // Return the address of the head so it can be updated in both gc_malloc and gc_free_all
}

// Custom malloc replacement
void *gc_malloc(size_t size) {
    Node **head = gc_get_head();  // Get a pointer to the static head

    // Allocate memory
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Create a new node to store the memory address
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Node allocation failed\n");
        free(ptr);  // Clean up allocated memory
        return NULL;
    }

    // Set the node's values
    new_node->address = ptr;
    new_node->size = size;
    new_node->next = *head;  // Insert at the beginning of the list
    *head = new_node;        // Update the head of the list
    printf("1 11--> %p\n",new_node->address);

    return ptr;  // Return the allocated memory
}

// Function to free all allocated memory
void gc_free_all() {
    Node **head = gc_get_head();  // Get a pointer to the static head
    Node *current = *head;
    // Traverse and free the linked list
    while (current != NULL) {
        printf("--> %p\n",current->address);
        Node *next_node = current->next;
        free(current->address);  // Free the allocated memory
        free(current);           // Free the node
        current = next_node;
    }

    *head = NULL;  // Reset the head of the list
}

int main() {
    // Example usage
    int *numbers = (int *)gc_malloc(5 * sizeof(int));  // Allocate memory for an array of 5 integers
    if (numbers != NULL) {
        for (int i = 0; i < 5; i++) {
            numbers[i] = i;
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    // Allocate another block of memory
    char *text = (char *)gc_malloc(20 * sizeof(char));
    if (text != NULL) {
        sprintf(text, "Hello, World!");
        printf("%s\n", text);
    }

    // Call this at the end to clean up all allocated memory
    gc_free_all();

    return 0;
}
