#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum { EQ, GT, LT, GTE, LTE } Operation;

typedef struct {
    char *name;
    int values[10];
    int size;
} Domain;

typedef struct {
    char *first_domain;
    char *second_domain;
    Operation operation;
} Constraint;

bool compare(int d1, int d2, Operation op) {
    switch (op) {
        case EQ:  return d1 == d2;
        case GT:  return d1 > d2;
        case LT:  return d1 < d2;
        case GTE: return d1 >= d2;
        case LTE: return d1 <= d2;
    }
    return false;
}
bool any_match(int d1, int *d2, int d2_size, Operation op) {
    for (int j = 0; j < d2_size; j++) {
        if (compare(d1, d2[j], op))
            return true;
    }
    return false;
}

Domain* find_domain(Domain *domains, int domain_count, char *name) {
    for (int i = 0; i < domain_count; i++) {
        if (strcmp(domains[i].name, name) == 0)
            return &domains[i];
    }
    return NULL;
}

void filter(Domain *domains, int domain_count, Constraint *constraints, int constraint_count) {
    for (int i = 0; i < constraint_count; i++) {
        Domain *d1 = find_domain(domains, domain_count, constraints[i].first_domain);
        Domain *d2 = find_domain(domains, domain_count, constraints[i].second_domain);
        
        int new_size = 0;
        int temp[10];
        
        for (int j = 0; j < d1->size; j++) {
            if (any_match(d1->values[j], d2->values, d2->size, constraints[i].operation)) {
                temp[new_size++] = d1->values[j];
            }
        }
        
        d1->size = new_size;
        for (int j = 0; j < new_size; j++)
            d1->values[j] = temp[j];
    }
}

void print_domains(Domain *domains, int count) {
    printf("Domains: {");
    for (int i = 0; i < count; i++) {
        printf("%s: {", domains[i].name);
        for (int j = 0; j < domains[i].size; j++) {
            printf("%d%s", domains[i].values[j], j < domains[i].size - 1 ? ", " : "");
        }
        printf("}%s", i < count - 1 ? ", " : "");
    }
    printf("}\n");
}

int main() {
    Domain domains[] = {
        {"d_1", {0, 1, 2}, 3},
        {"d_2", {0, 1, 2}, 3},
        {"d_3", {0, 1, 2}, 3}
    };
    int domain_count = 3;
    
    Constraint constraints[] = {
        {"d_1", "d_2", GT},
        {"d_2", "d_1", LT},
        {"d_2", "d_3", EQ},
        {"d_3", "d_2", EQ}
    };
    int constraint_count = 4;
    
    filter(domains, domain_count, constraints, constraint_count);
    print_domains(domains, domain_count);
    return 0;
}