// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
	char word[LENGTH + 1];
	struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define NUM_IN_ALPH 26
#define NUM_HASH_CHAR 3
const unsigned int N = 17576 /* NUM_IN_ALPH ^ NUM_HASH_CHAR */;

// Hash table
struct Table
{
	node *table[N];
	unsigned int word_count;
};
struct Table t;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
	bool exists = false;

	unsigned int hash_value = hash(word);

	if (t.table[hash_value] != NULL)
	{
		for (node *ptr = t.table[hash_value]; ptr != NULL; ptr = ptr->next)
		{
			if (strcasecmp(word, ptr->word) == 0)
			{
				exists = true;
				break;
			}
			else
			{
				/* Do nothing, keep searching */
			}
		}
	}
	else
	{
		exists = false;
	}

	return exists;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
	int value, offset;
	unsigned int hash_value = 0;

	unsigned int len = strlen(word);

	for (int i = 0; i < NUM_HASH_CHAR; i++)
	{
		if (i < len)
		{
			value = toupper(word[i]) - 'A';
			value = (value < 0) || (value > NUM_IN_ALPH) ? 0 : value;
			offset = (int)powf((float)26, (float)i);

			hash_value += value * offset;
		}
	}

	return hash_value;
}

node *create(const char *word)
{
	node *new = malloc(sizeof(node));
	if (new != NULL)
	{
		t.word_count++;
		strcpy(new->word, word);
		new->next = NULL;
	}
	return new;
}

void append(node *head, const char *word)
{
	if (head->next == NULL)
	{
		node *new = create(word);
		if (new != NULL)
		{
			head->next = new;
		}
	}
	else
	{
		append(head->next, word);
	}
}

void load_word(const char *word)
{
	if (!check(word))
	{
		unsigned int hash_value = hash(word);

		/* populate the new node */
		if (t.table[hash_value] == NULL)
		{
			/* append to the table */
			node *new = create(word);
			if (new != NULL)
			{
				t.table[hash_value] = new;
			}
		}
		else
		{
			/* loop through until NULL is found */
			append(t.table[hash_value], word);
		}
	}
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
	bool status;
	char buffer[100];
	FILE *p_file;

	p_file = fopen(dictionary, "r");
	if (p_file != NULL)
	{
		while (fgets(buffer, 100, p_file))
		{
			/* remove tailing newline signs */
			buffer[strcspn(buffer, "\r\n")] = 0;
			load_word(buffer);
		}
		status = true;
	}
	else
	{
		status = false;
	}
	fclose(p_file);

	return status;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
	return t.word_count;
}

void destroy(node *head)
{
	if (head->next == NULL)
	{
		t.word_count--;
		free(head);
	}
	else
	{
		destroy(head->next);
		t.word_count--;
		free(head);
	}
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
	for (int i = 0; i < N; i++)
	{
		if (t.table[i] != NULL)
		{
			destroy(t.table[i]);
		}
	}

	return size() == 0;
}
