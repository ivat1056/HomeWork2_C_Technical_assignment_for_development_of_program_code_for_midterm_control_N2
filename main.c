#include <stdio.h>
#include <stdlib.h>

typedef struct list_elem
{
    int value;
    struct list_elem *next;
}l_elem;

typedef struct
{
    l_elem *head;
    int size;
}list1;

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
    delete_all_odd(&mylist);
    print_list(&mylist);
    delete_all_even(&mylist);
    print_list(&mylist);
    for(i=1;i<6;i+=2)append(&mylist,i);
    for(i=0;i<6;i+=2)append(&mylist,i);
    for(i=1;i<6;i+=2)append(&mylist,i);
    for(i=0;i<6;i+=2)append(&mylist,i);
    for(i=1;i<6;i+=2)append(&mylist,i);
    print_list(&mylist);
    delete_all_odd(&mylist);
    print_list(&mylist);
    for(i=0;i<10;i++)append(&mylist,i);
    print_list(&mylist);
    delete_all_odd(&mylist);
    print_list(&mylist);
    delete_all_even(&mylist);
    print_list(&mylist);
    clear_list(&mylist);
    return 0;
}

void init_list(list1 *list_ptr)
{
    list_ptr->head = NULL;
    list_ptr->size = 0;
}

void append(list1 *list_ptr, int value)
{
    l_elem *new_elem = (l_elem*)malloc(sizeof(l_elem));
    if (new_elem == NULL) {
        printf("Memory allocation error\n");
        return;
    }
    new_elem->value = value;

    if (list_ptr->head == NULL) 
    {
        new_elem->next = new_elem;
        list_ptr->head = new_elem;
    } 
    else 
    {
        l_elem *temp = list_ptr->head;
        while (temp->next != list_ptr->head) 
        {
            temp = temp->next;
        }
        temp->next = new_elem;
        new_elem->next = list_ptr->head;
    }
    
    list_ptr->size++;
}

void print_list(list1 *list_ptr)
{
    if (list_ptr->head == NULL) 
    {
        printf("print_list(): List is empty\n");
        return;
    }
        l_elem *temp = list_ptr->head;
        printf("print_list(): ");
        do 
        {
            printf("%d ", temp->value);
            temp = temp->next;
        } 
        while (temp != list_ptr->head);
    printf("\n");
}

void clear_list(list1 *list_ptr)
{
    if (list_ptr->head == NULL) return;
    l_elem *current = list_ptr->head;
    l_elem *next_elem;
    printf("clear_elements: ");
    do 
    {
        next_elem = current->next;
        printf("%d ", current->value);
        free(current);
        current = next_elem;
    } 
    while (current != list_ptr->head);
    printf("\n");
    list_ptr->head = NULL;
    list_ptr->size = 0;
}

int get_by_index(list1 *list_ptr, int index)
{
    if (list_ptr->head == NULL) 
    {
        printf("get_by_index(%d): List is empty\n", index);
        return 0;
    }
    int original_index = index;
    if (index < 0) 
    {
        index = list_ptr->size + index;
    }
    if ( index < 0 || index >= list_ptr->size) 
    {
        printf("get_by_index(%d): Index out of range (size of list: %d)\n", original_index, list_ptr->size);
        return 0;
    }
    
    l_elem *current_elem = list_ptr->head;
    for (int i = 0; i < index; i++) 
    {
        current_elem = current_elem->next;
    }
    return current_elem->value;
}
void delete_by_index(list1 *list_ptr, int index) 
{
    if (list_ptr->head == NULL) 
    {
        return;
    }
    int original_index = index;
    int size = list_ptr->size;
    if (index < 0) 
    {
        index = size + index;
    }
    if (index < 0 || index >= size) 
    {
        printf("delete_by_index(%d): Index out of range\n", original_index);
        return;
    }
    l_elem *temp = list_ptr->head;
    l_elem *prev = NULL;
    if (index == 0) 
    {
        if (size == 1) 
        {
            free(temp);
            list_ptr->head = NULL;
        } 
        else 
        {
            l_elem *last = list_ptr->head;
            while (last->next != list_ptr->head) 
            {
                last = last->next;
            }
            list_ptr->head = list_ptr->head->next;
            last->next = list_ptr->head;
            free(temp);
        }
    } 
    else 
    {
        for (int i = 0; i < index; i++) 
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        free(temp);
    }
    list_ptr->size--;
}

void delete_all_odd(list1 *list_ptr) 
{
    if (list_ptr->head == NULL) 
    {
        return; 
    }
    l_elem *current = list_ptr->head;
    l_elem *prev = NULL;
    l_elem *start = NULL;
    int deleted = 0;
    while (current != NULL && current->value %2 != 0) 
    {
        l_elem *to_delete = current;
        if (current == list_ptr->head) 
        {
            list_ptr->head = current->next;
        }
        if (list_ptr->head == NULL) 
        {
            list_ptr->head = NULL;
        } 
        else 
        {
            l_elem *last = list_ptr->head;
            while (last->next != to_delete) 
            {
                last = last->next;
            }
            last->next = list_ptr->head;
        }
        current = current->next;
        free(to_delete);
        list_ptr->size--;
        deleted = 1;
    }
    if (list_ptr->head != NULL) 
    {
        prev = list_ptr->head;
        current = list_ptr->head->next;
    }
    while (current != list_ptr->head) 
    {
        if (current->value %2 != 0) 
        {
            l_elem *to_delete = current;
            prev->next = current->next;
            current = current->next;
            free(to_delete);
            list_ptr->size--;
            deleted = 1;
        } 
        else 
        {
            prev = current;
            current = current->next;
        }
    }
    if (deleted == 0) 
    {
        printf("delete_all_odd: No elements were deleted\n");
    }
}

void delete_all_even(list1 *list_ptr) 
{
    if (list_ptr->head == NULL) 
    {
        return; 
    }
    l_elem *current = list_ptr->head;
    l_elem *prev = NULL;
    l_elem *start = list_ptr->head;
    int deleted = 0;
    while (current != NULL && (current->value % 2 == 0)) 
    {
        l_elem *to_delete = current;
        if (current == list_ptr->head) 
        {
            list_ptr->head = current->next;
            if (list_ptr->head == to_delete) 
            {
                list_ptr->head = NULL;
            } 
            else 
            {
                l_elem *last = list_ptr->head;
                while (last->next != to_delete) 
                {
                    last = last->next;
                }
                last->next = list_ptr->head;
            }
            current = list_ptr->head;
        } 
        else 
        {
            prev->next = current->next;
            current = current->next;
        }
        free(to_delete);
        list_ptr->size--;
        deleted = 1;
    }

    if (list_ptr->head == NULL) 
    {
        return;
    }
    prev = list_ptr->head;
    current = list_ptr->head ? list_ptr->head->next : NULL;
    while (current != start) 
    {
        if (current->value % 2 == 0) 
        {
            l_elem *to_delete = current;
            prev->next = current->next;
            current = current->next;
            free(to_delete);
            list_ptr->size--;
            deleted = 1;
        } 
        else 
        {
            prev = current;
            current = current->next;
        }
    }
    if (deleted == 0) 
    {
        printf("delete_all_even: No elements were deleted\n");
    }
}



