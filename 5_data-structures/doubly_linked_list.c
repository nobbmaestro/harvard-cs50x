#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define MIN_NUM_ARGS 2
typedef struct dllnode
{
    int data;
    struct dllnode *prev;
    struct dllnode *next;
} dllnode;

/* Helper(s) function prototypes */
bool find(dllnode *head, int value);
dllnode *create(int value);
dllnode *insert(dllnode *head, int value);
dllnode *prepend(dllnode *head, int value);
dllnode *sorted_insert(dllnode *head, int value);
void append(dllnode *head, int value);
void delete(dllnode *target);
void destroy(dllnode *head);
void printout_list(dllnode *head);
void swap(dllnode *a, dllnode *b);

int main(int argc, char *argv[])
{
    int status;
    dllnode *list = NULL;

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
            dllnode *tmp = list;
            while ((tmp->next != NULL) && (tmp->data != 5))
            {
                tmp = tmp->next;
            }
            delete (tmp);
            printout_list(list);
        }
        destroy(list);
    }

    return status;
}

/* Helpers */
dllnode *create(int value)
{
    dllnode *new = malloc(sizeof(dllnode));
    if (new != NULL)
    {
        new->data = value;
        new->prev = NULL;
        new->next = NULL;
    }
    return new;
}

void swap(dllnode *a, dllnode *b)
{
    int tmp = b->data;
    b->data = a->data;
    a->data = tmp;
}

void delete(dllnode *target)
{
    /* Check if target is root node. If true, swap target node with next node */
    if ((target->prev == NULL) && (target->next != NULL))
    {
        swap(target, target->next);
        delete (target->next);
    }
    else
    {
        if (target->prev != NULL)
        {
            if (target->next != NULL)
            {
                target->prev->next = target->next;
            }
            else
            {
                target->prev->next = NULL;
            }
        }

        if (target->next != NULL)
        {
            if (target->prev != NULL)
            {
                target->next->prev = target->prev;
            }
            else
            {
                target->next->prev = NULL;
            }
        }
        free(target);
    }
}

dllnode *prepend(dllnode *head, int value)
{
    dllnode *new = create(value);
    if (new != NULL)
    {
        /* prepend at the beginning */
        new->data = value;
        new->prev = NULL;
        new->next = head;

        head->prev = new;
        head = new;
    }
    return head;
}

void append(dllnode *head, int value)
{
    if (head->next == NULL)
    {
        dllnode *new = create(value);
        if (new != NULL)
        {
            /* append at last node */
            new->data = value;
            new->prev = head;
            new->next = NULL;

            head->next = new;
        }
    }
    else
    {
        append(head->next, value);
    }
}

dllnode *insert(dllnode *head, int value)
{
    dllnode *new = create(value);
    if (new != NULL)
    {
        new->data = value;
        new->prev = head;
        new->next = head->next;

        /* Update prev ptr of next node */
        if (head->next != NULL)
        {
            head->next->prev = new;
        }

        head->next = new;
    }
    return head;
}

dllnode *sorted_insert(dllnode *head, int value)
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

bool find(dllnode *head, int value)
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

void destroy(dllnode *head)
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

void printout_list(dllnode *head)
{
    bool first_entry = true;
    for (dllnode *ptr = head; ptr != NULL; ptr = ptr->next)
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

    /* get last node */
    dllnode *last_node = head;
    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }

    first_entry = true;
    for (dllnode *ptr = last_node; ptr != NULL; ptr = ptr->prev)
    {
        if (first_entry)
        {
            first_entry = false;
            printf("linked list: ");
        }

        if (ptr->prev != NULL)
        {
            printf("%d -> ", ptr->data);
        }
        else
        {
            printf("%d\n", ptr->data);
        }
    }
}
