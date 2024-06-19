#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "package_and_pay.h"

Package addPackage(int shipping_cost, int value) {
    Package new_package;
    new_package.shipping_cost = shipping_cost;
    new_package.value = value;
    printf("...New package added\n");
    return new_package;
}

Person addPerson(const char* name, float pay) {
    Person new_person;
    strncpy(new_person.name, name, NAME_LENGTH);
    new_person.pay = pay;
    new_person.packages = NULL;
    new_person.package_count = 0;
    printf("...New person %s added\n,", name);
    return new_person;
}

void printPersonAndTheirInfo(Person* persons[], int count) {
    if(count == 0)
        printf("...File is blank\n");
    for (int i = 0; i < count; i++) {
         printf("-----------------------\n");
        printf("Name: %s\n", persons[i]->name);
        printf("Pay: %.2f\n", persons[i]->pay);
        printf("Packages:\n");
        for (int j = 0; j < persons[i]->package_count; j++) {
            printf("  Package %d: Cost = %d, Value = %d\n", j + 1, persons[i]->packages[j].shipping_cost, persons[i]->packages[j].value);
        }
        printf("-----------------------\n");
    }
}

Person addPackageToPerson(Person person, Package* package) {
    //I reallocate 'one Package more' of space
    // Add the new package to the end of the packages array
    person.packages = realloc(person.packages, (person.package_count + 1) * sizeof(Package));
    person.packages[person.package_count] = *package;
    
    // person increment his package count attribute
    // get person paid. Update the person's pay based on the value of the new package
    person.package_count++;
    accumulatePay(&person, *package);

    printf("...package successfully added to %s\n", person.name);
    return person;
}

void accumulatePay(Person* person, Package package) {
    person->pay += 0.2 * 0.2 * package.value;
}


void loadFromFile(Person* persons[], int* count) {
    FILE* file = fopen("persons.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    //first read person count
    printf("Number of persons: %d\n", *count);
    fscanf(file, "%d", count);
    //init person temp attribute
    char readName[50];
    float readPay;
    int readPackage_count;
    //init package temp attribute
    int readShipping_cost;
    int readValue;
    //load person{} struct and add person'spackage{} array with those packages.
    for (int i = 0; i < *count; i++) {
        //init that many 'person', according to count number we see in file
        persons[i] = malloc(sizeof(Person));

        fscanf(file, " Name:%s Pay:%f Packages:%d", readName, &readPay, &readPackage_count);
        printf("Person %d - Name: %s, Pay: %.2f, Packages: %d\n", i, readName, readPay, readPackage_count);

        //we should both accumulated attributes as zero, or it would conflict.
        *persons[i] = addPerson(readName, 0);
        persons[i]->package_count = 0;

        //init person's package
        persons[i]->packages = malloc(readPackage_count * sizeof(Package));

        for (int j = 0; j < readPackage_count; j++) {
        int tempIndex;
        fscanf(file, " Package %d: shipping cost:%d value:%d\n", &tempIndex, &readShipping_cost, &readValue);
        printf("Person %d - Package %d: Shipping Cost: %d, Value: %d\n", i, j, readShipping_cost, readValue);

        Package package = addPackage(readShipping_cost, readValue);
        *persons[i] = addPackageToPerson(*persons[i], &package);
        }
    }
    printf("...Loading persons.txt success!\n");

    fclose(file);
}

void saveToFile(Person* persons[], int count) {
    FILE* file = fopen("persons.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d\n", count);
    //for that many people and that many package, fprint it out.
    for (int i = 0; i < count; i++) {
        fprintf(file, "Name:%s Pay:%f Packages:%d\n", persons[i]->name, persons[i]->pay, persons[i]->package_count);
        for (int j = 0; j < persons[i]->package_count; j++) {
            fprintf(file, "Package %d: shipping cost:%d value:%d\n",j,persons[i]->packages[j].shipping_cost, persons[i]->packages[j].value);
        }
    }
    printf("...File output to persons.txt success!\n");
    fclose(file);
}
