#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
char filename[256];
int recordCount = 0;
FITNESS_DATA *FITNESS_DATA_ARRAY;

void menu()
{
    printf("\nOptions Menu\n");
    printf("A: Enter filename to import\n");
    printf("B: Display total number of records\n");
    printf("C: Display date and time of timeslot with fewest steps\n");
    printf("D: Display date and time of timeslot with most steps\n");
    printf("E: Calculate mean step count of all given records\n");
    printf("F: Find longest continuous period where steps are greater than 500\n");
    printf("Q: Exit\n");
}

void import()
{
    printf("Filename: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        perror("Error: could not open file");
        exit(1);
    }
    int maxRecords = 500;
    FITNESS_DATA_ARRAY = (FITNESS_DATA *)malloc(maxRecords * sizeof(FITNESS_DATA)); //dynamic mem allocation for array!

    if (FITNESS_DATA_ARRAY == NULL)
    {
        perror("Error: allocation failed\n");
        exit(1);
    }

    char line[64];
    recordCount = 0;

    while(fgets(line, sizeof(line), file) != NULL && recordCount < maxRecords)
    {
        char date[11];
        char time[6];
        char steps[10];

        tokeniseRecord(line, ",", date, time, steps);

        strcpy(FITNESS_DATA_ARRAY[recordCount].date, date);
        strcpy(FITNESS_DATA_ARRAY[recordCount].time, time);
        FITNESS_DATA_ARRAY[recordCount].steps = atoi(steps);

        recordCount++;
    }
    fclose(file);
}

void totalRecords()
{
    if(FITNESS_DATA_ARRAY == NULL)
    {
        perror("No data has been imported yet.");
        return;
    }
    printf("Total records: %d\n", recordCount);
}

void findMinSteps()
{
    if(FITNESS_DATA_ARRAY == NULL)
    {
        perror("No data has been imported yet.");
        return;
    }

    int minSteps = FITNESS_DATA_ARRAY[0].steps;//min number
    int minIndex = 0;//location of the minimum

    for(int i = 1; i < recordCount; ++i)
    {
        if(FITNESS_DATA_ARRAY[i].steps < minSteps)
        {
            minSteps = FITNESS_DATA_ARRAY[i].steps;
            minIndex = i;
        }
    }

    printf("Fewest steps: %s %s\n", FITNESS_DATA_ARRAY[minIndex].date, FITNESS_DATA_ARRAY[minIndex].time);
}

void findMaxSteps()
{
    if(FITNESS_DATA_ARRAY == NULL)
    {
        perror("No data has been imported yet.");
        return;
    }

    int maxSteps = FITNESS_DATA_ARRAY[0].steps;
    int maxIndex = 0;

    for (int i = 1; i < recordCount; ++i) 
    {
        if (FITNESS_DATA_ARRAY[i].steps > maxSteps)
        {
            maxSteps = FITNESS_DATA_ARRAY[i].steps;
            maxIndex = i;
        }
    }

    printf("Largest steps: %s %s\n", FITNESS_DATA_ARRAY[maxIndex].date, FITNESS_DATA_ARRAY[maxIndex].time);
}

void findMeanSteps()
{
    if(FITNESS_DATA_ARRAY == NULL)
    {
        perror("No data has been imported yet.");
        return;
    }

    int totalSteps = 0;

    for(int i = 0; i < recordCount; ++i)
    {
        totalSteps += FITNESS_DATA_ARRAY[i].steps;
    }

    int meanSteps = totalSteps/recordCount;
    printf("Mean step count: %d\n", meanSteps);
}

void findLongestAbove500()
{
    if(FITNESS_DATA_ARRAY == NULL)
    {
        perror("No data has been imported yet.");
        return;
    }
    //find start and end index for where steps exceed 500, then iterate for every item between.
    int currentStartIndex = -1;
    int longestStartIndex = -1;
    int longestEndIndex = -1;
    int currentLength = 0;
    int longestLength = 0;

    for(int i = 0; i < recordCount; ++i)
    {
        if(FITNESS_DATA_ARRAY[i].steps > 500)
        {
            if(currentStartIndex == -1)
            {
                currentStartIndex = i;
            }
            currentLength++;
        }
        else
        {
            if(currentLength > longestLength)
            {
                longestStartIndex = currentStartIndex;
                longestEndIndex = i - 1;
                longestLength = currentLength;
            }
            currentStartIndex = -1; //reset the start
            currentLength = 0;  // reset the length
        }
    }

    if(currentLength > longestLength){//check for longest period at end
        longestStartIndex = currentStartIndex;
        longestEndIndex = recordCount -1;
        longestLength = currentLength;
    }

    if(longestStartIndex != -1){
        printf("Longest period start: %s %s\n", FITNESS_DATA_ARRAY[longestStartIndex].date, FITNESS_DATA_ARRAY[longestStartIndex].time);
        printf("Longest period end: %s %s\n", FITNESS_DATA_ARRAY[longestEndIndex].date, FITNESS_DATA_ARRAY[longestEndIndex].time);
    } 
    else 
    {
        printf("No continuous period with step count above 500 found.\n");
    }

}



// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() 
{
   char option;
   
   do
   {
        menu();
        printf("Enter your choice: ");
        scanf(" %c", &option);

        switch(option)
        {
            case 'A':
                import();
                break;
            case 'B':
                totalRecords();
                break;
            case 'C':
                findMinSteps();
                break;
            case 'D':
                findMaxSteps();
                break;
            case 'E':
                findMeanSteps();
                break;
            case 'F':
                findLongestAbove500();
                break;
            case 'Q':
                return 0;
                break;
            default:
                printf("Invalid entry. Please try again.\n");
        }
    } while(option != 'Q');//dont know why this was needed. but code doesnt compile without.

    return 0;
}






