#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define MIN_NUM_ARGS 2 
typedef struct sllnode
{
    int data;
    struct sllnode *next;
} sllnode;

/* Helper(s) function prototypes */
sllnode *create(int value);
sllnode *prepend(sllnode *head, int value);
void append(sllnode *head, int value);
sllnode *insert(sllnode *head, int value);
sllnode *sorted_insert(sllnode *head, int value);
bool find(sllnode *head, int value);
void destroy(sllnode *head);
void printout_list(sllnode *head);

int main(int argc, char *argv[])
{
    int status;
    sllnode *list = NULL;

    if (argc <= (MIN_NUM_ARGS))
    {
        printf("Usage: ./linked_list <opr: (p)repend, (a)ppend or (s)orted insert> <any num of args>\n");
        status = 1;
    }
    else
    {
        char *opr = argv[1];
        for (int i = (MIN_NUM_ARGS); i < argc; i++)
        {
            int arg = atoi(argv[i]);
            if (i == (MIN_NUM_ARGS))
            {
                list = create(arg);
            }
            else
            {
                switch (*opr)
                {
                    case 'p':
                        list = prepend(list, arg);
                        status = 0;
                        break;
                    
                    case 'a':
                        append(list, arg);
                        status = 0;
                        break;
                    
                    case 's':
                        list = sorted_insert(list, arg);
                        status = 0;
                        break;
                    
                    default:
                        printf("Usage: ./linked_list <opr: (p)repend, (a)ppend or (s)orted insert> <any num of args>\n");
                        status = 1;
                        break;
                }
            }
        }

        if (status != 1)
        {
            printout_list(list);
        }
        destroy(list);
    }

    return status;
}

/* Helpers */
sllnode *create(int value)
{
    sllnode *new = malloc(sizeof(sllnode));
    if (new != NULL)
    {
        new->data = value;
        new->next = NULL;
    }
    return new;
}

sllnode *prepend(sllnode *head, int value)
{
    sllnode *new = create(value);
    if (new != NULL)
    {
        /* prepend at the beginning */
        new->data = value;
        new->next = head;
        head = new;
    }
    return head;
}

void append(sllnode *head, int value)
{
    if (head->next == NULL)
    {
        sllnode *new = create(value);
        if (new != NULL)
        {
            /* append at last node */
            new->data = value;
            new->next = NULL; 
            head->next = new; 
        }
    }
    else
    {
        append(head->next, value);
    }
}

sllnode *insert(sllnode *head, int value)
{
    sllnode *new = create(value);
    if (new != NULL)
    {
        new->data = value;
        new->next = head->next;
        head->next = new;
    }
    return head;
}

sllnode *sorted_insert(sllnode *head, int value)
{
    if ((value <= head->data))
    {
        head = prepend(head, value);
    }
    else if ((value > head->data) && (head->next == NULL))
    {
        append(head, value);
    }
    else if ((value >= head->data) && (value < head->next->data))
    {
        head = insert(head, value);
    }
    else
    {
        head->next = sorted_insert(head->next, value);
    }
    return head;
}

bool find(sllnode *head, int value)
{
    if (head->data == value)
    {
        return true;
    }
    else if (head->next == NULL)
    {
        return head->data == value;
    }
    else
    {
        return find(head->next, value);
    }
}

void destroy(sllnode *head)
{
    if (head->next == NULL)
    {
        free(head);
    }
    else
    {
        destroy(head->next);
        free(head);
    }
}

void printout_list(sllnode *head)
{
    bool first_entry = true;
    for (sllnode *ptr = head; ptr != NULL; ptr = ptr->next)
    {
        if (first_entry)
        {
            first_entry = false;
            printf("linked list: ");
        }

        if (ptr->next != NULL)
        {
            printf("%d -> ", ptr->data);
        }
        else
        {
            printf("%d\n", ptr->data);
        }
    }
}
