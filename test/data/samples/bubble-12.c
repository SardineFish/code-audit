// https://github.com/contrapost/c_assignment_1/blob/master/assignment_1.c

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Created by Alexander Shipunov

#define LENGTH_OF_LINE 256

char** sort(char **array, int counter);

int main(int argc, char* argv[]){

	// ================== 1. dealing with file ==============================

	// Checks if there is no arguments (filename isn't mentioned)
	if(argc < 2) 
	{
		printf("%s\n", "You forgot to write a name of file as argument!");
		return -1;
	}

	FILE * file;
	
	// Checks if the file exists and opens it
	if(access(argv[1], F_OK ) != -1)
	{
    	file = fopen(argv[1], "r");
	} 
	else 
	{
   	 	printf("%s\n", "There is no file with such name!");
		return -1;
	}
	
	// ================== 2. populating the array ===========================
	
	char **lines; // Pointer to pointers to a number of characters
	int sizeOfArray = 20; // Original number of strings 
	int counter = 0; // Counts number of actual strings
	char line[LENGTH_OF_LINE]; // Default string with default length
	
	// Allocate memory for array of strings
	lines = malloc(sizeOfArray * sizeof(char*));
	
	// Allocate array of chars (representing string) on each index of
	// the original array (lines)
	for(int i = 0; i < sizeOfArray; i++)
	{
		lines[i]=malloc(LENGTH_OF_LINE * sizeof(char));
	}
	
	// Iterates through all lines in file and reallocates memory when necessary
	while (fgets(line, LENGTH_OF_LINE, file)) 
	{
        // Populates the array with lines from file untill the array isn't full.
        if (sizeOfArray > counter) 
        {
        	strcpy(lines[counter++], line);
		} 
		else // When array is full(sizeOfArray == counter), enlarges the array.
		{    
			int sizeOfPrevious = sizeOfArray;
			
			// If the number of strings is equal to the length of the array, 
			// the program doubles the size of the array.
			sizeOfArray *= 2;
			
			// Reallocates memory for the enlarged array.
			lines = realloc(lines, sizeof(char*)*sizeOfArray);
			if (lines == NULL) {
				printf("Can't allocate memory\n");
		  		return -1;
			}
			
			// (Re)allocates memory for strings.
			for(int i = 0; i < sizeOfArray; i++)
			{
				// Reallocates memory for the existing strings.
				if(i < sizeOfPrevious) 
				{
					lines[i]=realloc(lines[i], LENGTH_OF_LINE * sizeof(char));
					if (lines[i] == NULL) 
					{
						printf("Can't allocate memory\n");
				  		return -1;
					}
				}
				//Allocates memory for new strings.
				else
				{
					lines[i]=malloc(LENGTH_OF_LINE * sizeof(char));
				}
			}
			// Copies the last line that was read from file to the first empty
			// index in the array.
			strcpy(lines[counter++], line);
		}
    }
	
	// Closes the file.
	fclose(file);
	
	// ============ 3. sorting and printing the array =======================
	
	// Calls sort function.
	lines = sort(lines, counter);
	
	// Prints the result.
	for(int i = 0; i < counter; i++) {
		printf("%d. %s", i + 1, lines[i]);
	}
	
	// =================== 4. freeing the memory ============================
	for(int i = 0; i < sizeOfArray; i++) {
		free(lines[i]);
	}

	free(lines);
	
	return 0;
} 

char** sort(char **array, int length){
	int comparisionResult;
    char tmpLine[LENGTH_OF_LINE];

	// Checks if there is only one element in the array so it's unnecessary
	// to sort it.
    if (length <= 1)
    {
        return array;
	}
	
	// Iterates through the array until it's sorted.
    for (int i = 0; i < length - 1; i++)
    {
    	int swapped = 0;
    	// Compares each neighboring pair of elements.
        for (int j = 0; j < length - i - 1; j++)
        {
            comparisionResult = strcmp(array[j], array[j+1]);
			
			// Swaps the elements if they are in wrong order.
            if (comparisionResult > 0)
            {
                strcpy(tmpLine, array[j+1]);
                strcpy(array[j+1], array[j]);
                strcpy(array[j], tmpLine);
                swapped = 1;
            }
        }
        
        // If swapped hasn't been change, it means that array is already sorted.
        if(swapped == 0)
        {
        	break;
        }
    }

	return array;
}

