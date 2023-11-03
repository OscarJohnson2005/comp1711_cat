#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



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
int main() {
    /// read csv file
    /// store it in a structured array and typedef data structure
    /// write the number of lines to the screen in format: Number of records in file: xxx
    /// write to screen the first three lines with commas replaced with forward slashes.
    /// should be no whitespace before or after on any printed line

    FILE *file = fopen("FitnessData_2023.csv", "r"); // open the file, as read only since we shouldnt edit the data

    FITNESS_DATA fitDatArray[3];

    int buffer_size = 100;
    int totalRecords = 0;
    int recordCount = 0;
    char line_buffer[buffer_size];
    char date[11], time[6], steps[20];

    // count number of lines in csv. 
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) 
    {
        totalRecords++;
    }

    fseek(file, 0, SEEK_SET); // resets the reading position to zero

    // read data from csv lines 1, 2, 3, write this to fitDataArray.
    while(fgets(line_buffer, sizeof(line_buffer), file) != NULL && recordCount < 3)
    {
        tokeniseRecord(line_buffer, ",", date, time, steps);
        strncpy(fitDatArray[recordCount].date, date, sizeof(fitDatArray[recordCount].date) - 1); // assign date
        fitDatArray[recordCount].date[sizeof(fitDatArray[recordCount].date) - 1] = '\0'; // null termination prevents strange junk data injection in output.
        strncpy(fitDatArray[recordCount].time, time, sizeof(fitDatArray[recordCount].time) - 1); // assign time
        fitDatArray[recordCount].time[sizeof(fitDatArray[recordCount].time) - 1] = '\0';
        fitDatArray[recordCount].steps = atoi(steps); // assign steps, with changed datatype
        recordCount ++; // increment record count. make this a for loop later
    }

    fclose(file);

    // prints the number of records
    printf("Number of records in file: %d\n", totalRecords);

    // prints the first three lines with commas replaced by forward slashes
    for (int i = 0; i < 3; ++i)
    {
        printf("%s/%s/%d\n", fitDatArray[i].date, fitDatArray[i].time, fitDatArray[i].steps);
    }

    return 0;
}