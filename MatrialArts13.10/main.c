#include <stdio.h>
#include "StudioFile.h"
#include "General.h"

#define STUDIO_TEXT_FILE_NAME "studio.txt"
#define STUDIO_BINARY_FILE_NAME "studio.bin"

int initMenu(Studio* studio);
int initStudioFromBinaryFile(Studio* pStudio);
int initStudioFromTextFile(Studio* pStudio);
void printInitMenu();
void printGeneralMenu();
void printPrintSubMenu();
void printAddSubMenu();
void printSortSubMenu();
void printFindSubMenu();
int saveStudioToBinaryFile(Studio* pStudio);
int saveStudioToTextFile(Studio* pStudio);


int main()
{
    int generalChoice, subChoice;
    Studio studio;
    
    initMenu(&studio);// Initialize the studio
    do {
        printGeneralMenu();
        DROPPED_LINE
        scanf("%d", &generalChoice);
        switch (generalChoice) {
        case 1: // Printing
            printPrintSubMenu();
            printf("Enter your choice: \n");
            scanf("%d", &subChoice);
            DROPPED_LINE;
            switch (subChoice) {
            case 1:
                printStudio(&studio);
                break;
            case 2:
                printRooms(studio.roomManager);
                break;
            case 3:
                printTrainers(&studio);
                break;
            case 4:
                printTrainees(&studio);
                break;
            case 5:
                printMostSeniorTrainerDetails(&studio);
                break;
            case 6:
                printHighestSubscriptionTraineeDetails(&studio);
                break;
            default:
                printf("Invalid choice, please try again.\n");
            }
            break;
        case 2: // Adding
            printAddSubMenu();
            printf("Enter your choice: \n");
            scanf("%d", &subChoice);
            DROPPED_LINE
            switch (subChoice) {
            case 1:
            {
                addTrainer(&studio);
                break;
            }
            case 2:
            {
                addTrainee(&studio);
                break;
            }
            case 3:
            {
                addRoom(studio.roomManager);
                break;
            }
            case 4:
            {
                addTraining(&studio);
                break;
            }
            default:
                printf("Invalid choice, please try again.\n");
            }
            break;
        case 3: // Sorting
            printSortSubMenu();
            printf("Enter your choice: \n");
            scanf("%d", &subChoice);
            DROPPED_LINE
            switch (subChoice) {
            case 1:
                sortTrainees(&studio);
                break;
            default:
                printf("Invalid choice, please try again.\n");
            }
            break;
        case 4: // Finding
            printFindSubMenu();
            printf("Enter your choice: \n");
            scanf("%d", &subChoice);
            DROPPED_LINE
            switch (subChoice) {
            case 1:
                findTrainee(&studio);
                break;
            default:
                printf("Invalid choice, please try again.\n");
            }
            break;
        case 0:
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    } while (generalChoice != 0);

    
    if (!saveStudioToBinaryFile(&studio)) {
        printf("Failed to save studio data to binary file\n");
    }
    if (!saveStudioToTextFile(&studio)) {
        printf("Failed to save studio data to text file\n");
    }
    freeStudio(&studio);
    return 0;
}

int initMenu(Studio* studio) {
    int initChoice;
    do {
        printInitMenu();
        scanf("%d", &initChoice);
        switch (initChoice) {
        case 1:
            initStudioFromBinaryFile(studio);
            return 1;
        case 2:
            initStudioFromTextFile(studio);
            return 1;
        default:
            printf("Invalid choice, please try again.\n");
        }
    } while (1);
}


//initalize studio from binary file
int initStudioFromBinaryFile(Studio* pStudio)
{
    if (!initStudiofromFile(pStudio, STUDIO_BINARY_FILE_NAME))
        return 0;
    return 1;
}

//initalize studio from text file
int initStudioFromTextFile(Studio* pStudio)
{
    if (!loadStudioFromText(pStudio, STUDIO_TEXT_FILE_NAME))
        return 0;
    return 1;
}

//save studio to binary file
int saveStudioToBinaryFile(Studio* pStudio)
{
    if (!writeStudioToFile(pStudio, STUDIO_BINARY_FILE_NAME))
        return 0;
    return 1;
}

//save studio to text file
int saveStudioToTextFile(Studio* pStudio)
{
    if (!saveStudioToText(pStudio, STUDIO_TEXT_FILE_NAME))
        return 0;
    return 1;
}

void printInitMenu()
{
    printf("\n--- Init Menu ---\n");
    printf("1. Init From Binary file\n");
    printf("2. Init From Text file\n");
    printf("Please enter your choice: \n");

}

void printGeneralMenu() 
{
    printf("\n--- Studio Management System ---\n");
    printf("1. Print\n");
    printf("2. Add\n");
    printf("3. Sort\n");
    printf("4. Find\n");
    printf("0. Exit\n");
    printf("Please enter your choice: \n");
}

void printPrintSubMenu() 
{
    printf("\n--- Print Menu ---\n");
    printf("1. Print all studio data\n");
    printf("2. Print room data\n");
    printf("3. Print trainers\n");
    printf("4. Print trainees\n");
    printf("5. Print most senior trainer details\n"); 
    printf("6. Print highest subscription trainee details\n"); 
    printf("Please enter your choice: \n");
}

void printAddSubMenu() 
{
    printf("\n--- Add Menu ---\n");
    printf("1. Add trainer\n");
    printf("2. Add trainee\n");
    printf("3. Add room\n");
    printf("4. Add Training\n");
    printf("Please enter your choice: \n");
}

void printSortSubMenu() 
{
    printf("\n--- Sort Menu ---\n");
    printf("1. Sort trainees\n");
    printf("Please enter your choice: \n");
}

void printFindSubMenu()
{
    printf("\n--- Find Menu ---\n");
    printf("1. Find trainee\n");
    printf("Please enter your choice: \n");
}


