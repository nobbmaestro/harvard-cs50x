#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
    int data;
    struct node *next;
} node;

/* Helper(s) function prototypes */
void purge_list(node *list);
void printout_list(node *list);
node * prepend(node *list, int data);

int main(int argc, char *argv[])
{
    int status;

    if (argc <= 1)
    {
        printf("Usage: ./linked_list <any num of args>\n");
        status = 0;
    }
    else
    {
        node *list = NULL;
        for (int i = 1; i < argc; i++)
        {
            int arg = atoi(argv[i]);
            node *tmp = append(list, arg);

            /* Validate updated list */
            if (tmp == NULL)
            {
                status = 1;
                purge_list(list);
                break;
            }
            else
            {
                list = tmp;
                status = 0;
            }
        }
        printout_list(list);
        purge_list(list);
    }

    return status;
}

/* Helpers */
node * prepend(node *list, int data)
{
    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        list = NULL;
    }
    else
    {
        /* Append to list */
        n->data = data;
        n->next = NULL;

        n->next = list;
        list = n;
    }

    return list;
}

void purge_list(node *list)
{
    if (list != NULL)
    {
        node *ptr = list;
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    else
    {
        /* Do nothing */
    }
}

void printout_list(node *list)
{
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%d\n", ptr->data);
    }
}
