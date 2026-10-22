#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 45
#define N 20000

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

node *table[N];

unsigned int word_count = 0;

bool check(const char *word)
{
    unsigned int index = hash(word);

    node *cursor = table[index];
    
    while (cursor != NULL)
    {
        if(stricmp(word, cursor->word) == 0){
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

unsigned int hash(const char *word)
{
    unsigned int hash_code = 0;

    for(unsigned int i = 0; word[i] != '\0'; i++){
        hash_code = (hash_code * 31) + toupper(word[i]);
    }

    return hash_code = hash_code % N;
}

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node* new_bucket = malloc(sizeof(node));

        if (new_bucket == NULL)
        {
            return false;
        }
        new_bucket->next = NULL;
        strcpy(new_bucket->word, word);
        unsigned int hash_code = hash(new_bucket->word);
        new_bucket->next = table[hash_code];
        table[hash_code] = new_bucket;
        word_count++;
    }
    fclose(file);
    return true;
}

unsigned int size(void)
{
    return word_count;
}

bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node* cursor = table[i];
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);    
        }
        
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    char *dictionary = (argc == 3) ? argv[1] : "dictionaries/large";
    char *text = (argc == 3) ? argv[2] : argv[1];

    printf("Loading dictionary %s...\n", dictionary);
    if (!load(dictionary))
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    printf("\nMISSPELLED WORDS\n\n");

    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];
    int c;

    while ((c = fgetc(file)) != EOF)
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;

            if (index > LENGTH)
            {
                while ((c = fgetc(file)) != EOF && isalpha(c));
                index = 0;
            }
        }
        else if (isdigit(c))
        {
            while ((c = fgetc(file)) != EOF && isalnum(c));
            index = 0;
        }
        else if (index > 0)
        {
            word[index] = '\0';
            words++;

            if (!check(word))
            {
                printf("%s\n", word);
                misspellings++;
            }
            index = 0;
        }
    }

    fclose(file);

    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %u\n", size());
    printf("WORDS IN TEXT:        %d\n", words);

    unload();

    return 0;
}