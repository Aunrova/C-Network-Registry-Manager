//Tasguzen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Registration
{
    int regID;
    char name[30];
    char surname[30];
    char status[9];
    int year;
    char deviceMACAddress[18];
};
struct Registration* Load_RegistrationData(char *, int *);
void Display_RegistrationData(struct Registration *, int);
struct Registration* Add_Registration(struct Registration *, int *);
void Sort(struct Registration *, int);
void Statistics(struct Registration *, int);
void Menu();

int main()
{
    char fileName[100];
    FILE *inFile = NULL;
    int recordSize = 0;
    struct Registration *registrationData = NULL;

    do
    {
        printf("Please enter the registration data filename: ");
        scanf("%s", fileName);

        inFile = fopen(fileName, "r");
        if (inFile == NULL)
        {
            printf("File '%s' does not exist. ", fileName);
        }
    } while (inFile == NULL);
    fclose(inFile);

    registrationData = Load_RegistrationData(fileName, &recordSize);
    if (registrationData == NULL)
    {
        printf("Failed to load registration data.\n");
        return 1;
    }

    printf("The registration records file (%s) has been successfully loaded!\n", fileName);
    Display_RegistrationData(registrationData, recordSize);

    int choice = 0;
    while (choice != 4)
    {
        Menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                registrationData = Add_Registration(registrationData, &recordSize);
                break;
            case 2:
                Sort(registrationData, recordSize);
                break;
            case 3:
                Statistics(registrationData, recordSize);
                break;
            case 4:
                printf("Bye\n");
                break;
            default:
                printf("Wrong input!\n");
        }
    }

    free(registrationData);
    return 0;
}

struct Registration* Load_RegistrationData(char *fileName, int *recordSize)
{
    FILE *inFile = fopen(fileName, "r");
    if (inFile == NULL)
    {
        return NULL;
    }

    char line[256];
    fgets(line, sizeof(line), inFile);

    int count = 0;
    while (fgets(line, sizeof(line), inFile) != NULL)
    {
        count++;
    }

    struct Registration *registrationData = (struct Registration*)malloc(count * sizeof(struct Registration));
    if (registrationData == NULL)
    {
        fclose(inFile);
        return NULL;
    }

    rewind(inFile);
    fgets(line, sizeof(line), inFile);

    int i = 0;
    while (i < count && fscanf(inFile, "%d %s %s %s %d %s", &registrationData[i].regID, registrationData[i].name, registrationData[i].surname, registrationData[i].status, &registrationData[i].year, registrationData[i].deviceMACAddress) == 6)
        i++;

    fclose(inFile);
    *recordSize = count;
    return registrationData;
}

void Display_RegistrationData(struct Registration *registrationData, int recordSize)
{
    if (registrationData == NULL || recordSize == 0)
    {
        printf("No registration data to display.\n");
        return;
    }

    printf("\n REGID  NAME     SURNAME  STATUS    YEAR  DEVICEMACADDRESS\n");

    for (int i = 0; i < recordSize; i++)
    {
        printf(" %-5d  %-7s  %-7s  %-8s  %-4d  %-18s \n", registrationData[i].regID, registrationData[i].name, registrationData[i].surname, registrationData[i].status, registrationData[i].year, registrationData[i].deviceMACAddress);
    }
    printf("\n");
}

struct Registration* Add_Registration(struct Registration *registrationData, int *recordSize)
{
    struct Registration *newData = (struct Registration*)realloc(registrationData, (*recordSize + 1) * sizeof(struct Registration));
    if (newData == NULL)
    {
        printf("Memory allocation failed!\n");
        return registrationData;
    }

    printf("Please enter the name: ");
    scanf("%s", newData[*recordSize].name);

    printf("Please enter the surname: ");
    scanf("%s", newData[*recordSize].surname);

    int statusValid = 0;
    while (!statusValid)
    {
        printf("Please enter the status: ");
        scanf("%s", newData[*recordSize].status);

        if(strcmp(newData[*recordSize].status, "Approved") == 0 || strcmp(newData[*recordSize].status, "Blocked") == 0 || strcmp(newData[*recordSize].status, "Declined") == 0)
            statusValid = 1;
        if (!statusValid)
        {
            printf("This is not valid!\n");
        }
    }

    printf("Please enter the year: ");
    scanf("%d", &newData[*recordSize].year);

    int macValid = 0;
    while (!macValid)
    {
        printf("Please enter the mac address: ");
        scanf("%s", newData[*recordSize].deviceMACAddress);

        macValid = 1;

        if (strlen(newData[*recordSize].deviceMACAddress) != 17)
            macValid = 0;
        for (int i = 2; i < 17; i += 3)
        {
            if (newData[*recordSize].deviceMACAddress[i] != ':')
                macValid = 0;
        }

        if (!macValid)
        {
            printf("This is not valid!\n");
        }
    }

    newData[*recordSize].regID = newData[*recordSize - 1].regID + 1;

    (*recordSize)++;
    printf("It is recorded successfully!\n");

    return newData;
}

void Sort(struct Registration *registrationData, int recordSize)
{
    if (registrationData == NULL || recordSize == 0)
    {
        printf("No data to sort.\n");
        return;
    }

    int choice;
    printf("Which column (1: year, 2: surname)?:");
    scanf("%d", &choice);

    while (choice != 1 && choice != 2)
    {
        printf("Invalid choice!\n");
        printf("Which column (1: year, 2: surname)?:");
        scanf("%d", &choice);
    }

    for (int i = 0; i < recordSize - 1; i++)
    {
        for (int j = 0; j < recordSize - i - 1; j++)
        {
            int swap = 0;
            if (choice == 1)
            {
                if (registrationData[j].year > registrationData[j+1].year)
                {
                    swap = 1;
                }
            }
            else if (choice == 2)
            {
                if (strcmp(registrationData[j].surname, registrationData[j+1].surname) > 0)
                {
                    swap = 1;
                }
            }

            if (swap)
            {
                struct Registration temp = registrationData[j];
                registrationData[j] = registrationData[j+1];
                registrationData[j+1] = temp;
            }
        }
    }

    Display_RegistrationData(registrationData, recordSize);
}

void Statistics(struct Registration *registrationData, int recordSize)
{
    if (registrationData == NULL || recordSize == 0)
    {
        printf("No data for statistics.\n");
        return;
    }

    int approved = 0, blocked = 0, declined = 0;
    for (int i = 0; i < recordSize; i++)
    {
        if (strcmp(registrationData[i].status, "Approved") == 0)
        {
            approved++;
        }
        else if (strcmp(registrationData[i].status, "Blocked") == 0)
        {
            blocked++;
        }
        else if (strcmp(registrationData[i].status, "Declined") == 0)
        {
            declined++;
        }
    }

    printf("\nSummary:\n");
    printf("%d Blocked\n", blocked);
    printf("%d Approved\n", approved);
    printf("%d Declined\n\n", declined);
}

void Menu()
{
    printf("\nWhat would you like to do?\n");
    printf("1 - add\n");
    printf("2 - sort\n");
    printf("3 - statistics\n");
    printf("4 - exit\n");
}