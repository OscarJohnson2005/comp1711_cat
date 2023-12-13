#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, const char *delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}
//function to check that a given line is valid
int isValidFormat(char *line)
{
    char date[11];
    char time[6];
    int steps;
    char dummy;

    tokeniseRecord(line, ",", date, time, &steps);

    if(sscanf(line, "%10[^,],%5[^,],%d%c", date, time, &steps, &dummy))
    {
        if(strchr(line, ',') == strrchr(line, ',') && strlen(date) == 10 && strlen(time) == 5)
        {
            return 1;
        }
    }
    else
    {
        return 0;//invalid format
    }
}
//quicksort algorithm
void quicksort(FitnessData *data, int low, int high);

//partitioning for quicksort
int partition(FitnessData *data, int low, int high)
{
    int pivot = data[high].steps;
    int i = low -1;

    for(int j = low; j <= high -1; j++)
    {
        if(data[j].steps >= pivot)
        {
            i++;
            FitnessData temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }

    FitnessData temp = data[i+1];
    data[i+1] = data[high];
    data[high] = temp;

    return i+1;
}

void quicksort(FitnessData *data, int low, int high)
{
    if(low < high)
    {
        int pivot = partition(data, low, high);
        quicksort(data, low, pivot -1);
        quicksort(data, pivot + 1, high);
    }
}


int main() 
{
    char filename[64];
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Error: invalid file\n");
        exit(1);
    }

    char line[100];
    int numRecords = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if(isValidFormat(line) != 1)
        {
            printf("Error: invalid line format");
            fclose(file);
            return 1;
        }
        numRecords++;
    }
    rewind(file); //moves cursor to the beginning

    FitnessData *data = malloc(numRecords * sizeof(FitnessData));
    if(data == NULL)
    {
        printf("Error: Memorry failed\n");
        fclose(file);
        return 1;
    }

    for(int i =0; i < numRecords; i++)
    {
        fgets(line, sizeof(line), file);
        char date[11];
        char time[6];
        int steps;
        tokeniseRecord(line, ",", date, time, &steps);
        strcpy(data[i].date, date);
        strcpy(data[i].time, time);
        data[i].steps = steps;
    }

    quicksort(data, 0, numRecords - 1);

    char newFilename[100];
    sprintf(newFilename, "%s.tsv", filename);
    FILE *newFile = fopen(newFilename, "w");
    if(newFile == NULL)
    {
        printf("Error: Could not make new file\n");
        fclose(file);
        free(data);
        return 1;
    }

    for (int i = 0; i < numRecords; i++)
    {
        fprintf(newFile, "\n%s\t%s\t%d", data[i].date, data[i].time, data[i].steps);
    }

    fclose(file);
    fclose(newFile);
    free(data);

    return 0;
}