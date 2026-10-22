#include <stdio.h>
#include <stdlib.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[3];
}person;

char random_allele() {
    return "ABC"[rand() % 3];
}

person* create_family(int generations){
    person *new_person = malloc(sizeof(person));

    if(generations > 1){
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Set parent pointers for current person
        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        // Randomly assign current person's alleles based on the alleles of their parents
        new_person->alleles[0] = parent0->alleles[rand() % 2];
        new_person->alleles[1] = parent1->alleles[rand() % 2];
        new_person->alleles[2] = '\0';
    }
    else{
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        // Randomly assign alleles
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
        new_person->alleles[2] = '\0';
    }
    return new_person;
}

void free_family(person *p)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free child
    free(p);
}

char* get_tabs(int generations){
    char* result = malloc(sizeof(char)*(generations + 1));
    for(int i = 0; i < generations; i++){
        result[i]='\t';
    }
    result[generations] = '\0';
    return result;
}

void print_family(person* p, int generations)
{
    if (p == NULL)
    {
        return;
    }
    printf("%sGeneration %i: %s\n", get_tabs(generations), generations + 1, p->alleles);
    print_family(p->parents[0], generations + 1);
    print_family(p->parents[1], generations + 1);
}

int main(int argc, char *argv[]) {
    int generations = 3;
    srand(time(0));
    person *p = create_family(generations);
    print_family(p, 0);
    free_family(p);

    return 0;
}