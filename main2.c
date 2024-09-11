#include <stdio.h> 
#include <stdlib.h> 

typedef struct list_elem
{
    int value; 
    struct list_elem *next; 
} l_elem;

typedef struct
{
    l_elem *head; 
    l_elem *tail; 
    int size; 
} list1;

void init_list(list1 *list_ptr);
void append(list1 *list_ptr, int value);
void print_list(list1 *list_ptr);
void clear_list(list1 *list_ptr);
int get_by_index(list1 *list_ptr, int index);
void delete_by_index(list1 *list_ptr, int index);
void delete_all_odd(list1 *list_ptr);
void delete_all_even(list1 *list_ptr);

int main()
{
    int i;
    int a,b,c;
    list1 mylist;
    init_list(&mylist);
    printf("append values from 0 to 9\n");
    for(i=0;i<10;i++) append(&mylist,i);
    print_list(&mylist);
    printf("get_by_index():\n");
    printf("mylist[0]==%d\n", get_by_index(&mylist,0));
    printf("mylist[4]==%d\n", get_by_index(&mylist,4));
    printf("mylist[9]==%d\n", get_by_index(&mylist,9));
    a=get_by_index(&mylist,10);
    a=get_by_index(&mylist,-10);
    a=get_by_index(&mylist,-1);
    b=get_by_index(&mylist,-4);
    c=get_by_index(&mylist,-9);
    printf("mylist[-1]==%d, mylist[-4]==%d, mylist[-9]==%d\n",a,b,c);
    printf("delete_by_index():\n");
    delete_by_index(&mylist,0);
    delete_by_index(&mylist,-4);
    delete_by_index(&mylist,9);
    delete_by_index(&mylist,7);
    print_list(&mylist);
    for(i=0;i<10;i++)append(&mylist,i);
    print_list(&mylist);
    // delete_all_odd(&mylist);
    // print_list(&mylist);
    // delete_all_even(&mylist);
    // print_list(&mylist);
    // for(i=1;i<6;i+=2)append(&mylist,i);
    // for(i=0;i<6;i+=2)append(&mylist,i);
    // for(i=1;i<6;i+=2)append(&mylist,i);
    // for(i=0;i<6;i+=2)append(&mylist,i);
    // for(i=1;i<6;i+=2)append(&mylist,i);
    // print_list(&mylist);
    // delete_all_odd(&mylist);
    // print_list(&mylist);
    // for(i=0;i<10;i++)append(&mylist,i);
    // print_list(&mylist);
    // delete_all_odd(&mylist);
    // print_list(&mylist);
    // delete_all_even(&mylist);
    // print_list(&mylist);
    // clear_list(&mylist);
    return 0;
}

void init_list(list1 *list_ptr)
{
    list_ptr->head = NULL;
    list_ptr->tail = NULL;
    list_ptr->size = 0;
}

void append(list1 *list_ptr, int value)
{
    l_elem *new_elem = malloc(sizeof(l_elem));
    new_elem->value = value;
    if (list_ptr->head == NULL) 
    {
        new_elem->next = new_elem; 
        list_ptr->head = new_elem;
    } 
    else 
    {
        l_elem *tail = list_ptr->head;
        while (tail->next != list_ptr->head)
        {
            tail = tail->next; 
        }
        tail->next = new_elem;
        new_elem->next = list_ptr->head; 
    }

    list_ptr->size++; 
}

void print_list(list1 *list_ptr)
{
    if (list_ptr->head == NULL) 
    {
        printf("print list(): list is empty\n");
        return;
    }
    l_elem *current_elem = list_ptr->head; 
    printf("print list(): "); 
    while (current_elem != list_ptr->head) 
    {
        printf("%d ", current_elem->value);
        current_elem = current_elem->next; 
    }
    printf("\n"); 
}

void clear_list(list1 *list_ptr)
{
    l_elem *current_elem = list_ptr->head; 
    l_elem *next_elem; 
    printf("clear_elements(): "); 
    while (current_elem != NULL) 
    {
        next_elem = current_elem->next; 
        printf("%d ", current_elem->value); 
        free(current_elem); 
        current_elem = next_elem; 
    }
    list_ptr->head = NULL; 
    list_ptr->tail = NULL; 
    list_ptr->size = 0; 
    printf("\n"); 
}

int get_by_index(list1 *list_ptr, int index)
{
    if (list_ptr == NULL)
    {
        return 0;
    }
    if (abs(index) >= list_ptr->size) 
    {
        printf("get_by_index(%d): Index %d out of range\n", index, index); 
        return 0;
    }
    if (index < 0) 
    {
        index = list_ptr->size - abs(index); 
    }
    l_elem *current_elem = list_ptr->head; 

    for (int i = 0; i<index; i++) 
    {
        current_elem = current_elem->next;
    }
    return current_elem->value; 
}

void delete_by_index(list1 *list_ptr, int index)
{
    if (index < 0) 
    {
        index += list_ptr->size; 
    }
    if (abs(index) >= list_ptr->size) 
    {
        printf("delete_by_index(%d): Index %d out of range\n", index, index); 
        return;
    }
    if (index == 0) 
    {
        l_elem *temp_elem = list_ptr->head; 
        list_ptr->head = list_ptr->head->next;
    if (list_ptr->size == 1) 
    {
        list_ptr->tail = NULL; 
    }
    free(temp_elem); 
    }
    else 
    {
        l_elem *current_elem = list_ptr->head; 
        for (int i = 0; i < index - 1; i++) 
        {
            current_elem = current_elem->next;
        }
        l_elem *temp_elem = current_elem->next; 
        current_elem->next = current_elem->next->next;
        if (index == list_ptr->size - 1) 
        {
            list_ptr->tail = current_elem; 
        }
        free(temp_elem); 
    }
    list_ptr->size--; 
}