struct Node {
    int data;
    struct Node *next;
};

struct Node* create_node(int n);
void print_list(struct Node* head);
