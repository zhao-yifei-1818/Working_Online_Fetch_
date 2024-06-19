#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "package_and_pay.h"

#define MAX_PERSONS 100



int main() {
    Person* persons[MAX_PERSONS];
    int person_count = 0;
    int choice;

    while (1) {
        printf("1. Print all persons\n");
        printf("2. Start\n");
        printf("3. Load from txt\n");
        printf("4. Save as txt\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        if (choice == 1) {
            printPersonAndTheirInfo(persons, person_count);
        } else if (choice == 2) {
            char name[NAME_LENGTH];
            printf("Who is working on a package? ");
            fgets(name, NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = '\0';  // remove newline character

            //Looking for existing person in Person persons[] array
                    //if found that person, lets use that index,
                    //and work with that person
            int person_index = -1;
            for (int i = 0; i < person_count; i++) {
                if (strcmp(persons[i]->name, name) == 0) {
                    person_index = i;
                    break;
                }
            }
            //if that person looks new, initial new person
                //that last pointer in array would dynamically handle this person
            if (person_index == -1) {
                persons[person_count] = malloc(sizeof(Person));
                *persons[person_count] = addPerson(name, 0.0);

                person_index = person_count;// get its index back to the right one after assign
                person_count++;
            }

            // get a number.
            int num_packages;
            printf("How many packages do you want to add? ");
            scanf("%d", &num_packages);
            getchar();  // consume newline

            //add that many packages to that person's packages array
            for (int i = 0; i < num_packages; i++) {
                int cost, value;
                printf("Enter package %d cost: ", i + 1);
                scanf("%d", &cost);
                printf("Enter package %d value: ", i + 1);
                scanf("%d", &value);
                getchar();

                Package package = addPackage(cost, value);
                *persons[person_index] = addPackageToPerson(*persons[person_index], &package);
            }
            printf("...Done adding %d packages!\n", num_packages);
        } else if (choice == 3) {
            loadFromFile(persons, &person_count);
        } else if (choice == 4) {
            saveToFile(persons, person_count);
        } else if (choice == 5) {
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    //free everthing
    for (int i = 0; i < person_count; i++) {
        free(persons[i]->packages);
        free(persons[i]);
    }

    return 0;
}

