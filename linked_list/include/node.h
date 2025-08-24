struct Node {
    int data;
    struct Node *next;
};

struct Node* create_node(int data);
void print_list(struct Node* head);
void insert_at_beginning(struct Node** head_ref, int data);
void insert_at_end(struct Node** head_ref, int data);
void insert_at_position(struct Node** head_ref, int data, int position);
void free_list(struct Node** head_ref);

int delete_at_position(struct Node** head_ref, int position);
