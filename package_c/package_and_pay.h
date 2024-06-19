#ifndef PACKAGE_AND_PAY_H
#define PACKAGE_AND_PAY_H

#define NAME_LENGTH 50


typedef struct {
    int shipping_cost;
    int value;
} Package;

typedef struct {
    char name[NAME_LENGTH];
    float pay;
    Package* packages;
    int package_count;
} Person;
void loadFromFile(Person* persons[], int* count);
void saveToFile(Person* persons[], int count);
//Create a Package struct with shipping cost and value
Package addPackage(int shipping_cost, int value);
//Create a Person struct with name array and pay
Person addPerson(const char* name, float pay);
//Access every person in person array and print them
void printPersonAndTheirInfo(Person* persons[], int count);

//add existing package to a person
Person addPackageToPerson(Person person, Package* package);
// take package value, calculate and add to person's pay
void accumulatePay(Person* person, Package package);

#endif // PACKAGE_AND_PAY_H
