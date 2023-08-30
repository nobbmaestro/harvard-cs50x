#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool recorded = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            recorded = true;
            break;
        }
    }
    return recorded;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int winner, loser;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i != j)
            {
                winner = ranks[i];
                loser = ranks[j];
                preferences[winner][loser]++;
            }
        }
    }

}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] != 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    printf("\nUnsorted\n");
    for (int p = 0; p < pair_count; p++)
    {
        printf("i: %d \twinner: %d, loser: %d, votes: %d\n", p, pairs[p].winner, pairs[p].loser, preferences[pairs[p].winner][pairs[p].loser]);
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int high_votes, high_index;

    for (int i = 0; i < pair_count; i++)
    {
        high_votes = preferences[pairs[i].winner][pairs[i].loser];
        high_index = i;

        for (int j = i; j < pair_count; j++)
        {
            int curr_votes = preferences[pairs[j].winner][pairs[j].loser];

            if (curr_votes > high_votes)
            {
                high_votes = curr_votes;
                high_index = j;
            }
        }

        if (high_index != i)
        {
            pair tmp = pairs[high_index];
            pairs[high_index] = pairs[i];
            pairs[i] = tmp;
            printf("Swap index: %d <-> %d (%d > %d)\n", i, high_index, high_votes, preferences[pairs[i].winner][pairs[i].loser]);
        }
    }

    printf("\nSorted\n");
    for (int p = 0; p < pair_count; p++)
    {
        printf("i: %d \twinner: %d, loser: %d, votes: %d\n", p, pairs[p].winner, pairs[p].loser, preferences[pairs[p].winner][pairs[p].loser]);
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pairs_count; i++)
    {
        
    }
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}