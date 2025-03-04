#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "headers.h"

int main(int argc, char* argv[]){

    if ( argc != 3 )
	{
		fprintf(stderr, "Usage: project1 <input-file> <output-file>\n");
		exit(1);
	}

    //Opens the file to read through
    FILE* in;
    in = fopen(argv[1], "r");

    //Opens the output file to write to
    FILE* out;
    out = fopen(argv[2], "w");

    //checks if the in file is null, check to make sure the file was actually opened or exists
    if(in == NULL){
        perror("Error opening file");
        return 0;
    }


    char firstnum[4];

    //scan the first line for the number of coordinate pairs
    fscanf(in, "%[^\n]", firstnum);

    //turns the string into an integer
    int size = atoi(firstnum);

    //makes an array according to the amount of coordinate pairs
    char *coordinates[size];

    //what we're breaking the string down by, in this case, newline characters
    char delimiter[] = "\n";

    char* token;

    //goes through the first line since we don't need it as it's just the amount of pairs
    token = strtok(readEntireFile(argv[1]), delimiter);

    token = strtok(NULL, delimiter);

    int i = 0;

    //storing the coordinate pairs in the array
    while(token != NULL){
        coordinates[i] = token;
        i++;
        token = strtok(NULL, delimiter);
    }

    fprintf(out, "First coordinate                Second coordinate               seconds          DMS\n");
    fprintf(out, "-----------------------------------------------------------------------------------------------------------\n");

    for(int i = 0; i < size; i++){
        //first W coordinate
        fprintf(out, "(%sd %sm %ss W,  ", substring(coordinates[i], 0, 3), substring(coordinates[i], 3, 2), substring(coordinates[i], 5, 2));

        //first N coordinate
        fprintf(out, "%sd %sm %ss N)   ", substring(coordinates[i], 9, 2), substring(coordinates[i], 11, 2), substring(coordinates[i], 13, 2));

        //second W coordinate
        fprintf(out, "(%sd %sm %ss W,  ", substring(coordinates[i], 17, 3), substring(coordinates[i], 20, 2), substring(coordinates[i], 22, 2));

        //second N coordinate
        fprintf(out, "%sd %sm %ss N)       ", substring(coordinates[i], 26, 2), substring(coordinates[i], 28, 2), substring(coordinates[i], 30, 2));

        int secs = difference(coordinates[i]);

        //print the seconds
        fprintf(out,"%d             ", secs);

        int mins = secsToMins(secs);

        int days = minsToDays(mins);

        //print out the days according to the seconds
        fprintf(out, "%dd ", days);
        
        //print out the minutes according to the seconds
        //if the minutes is ony one digit, add a zero for formatting reasons
        if(mins  - (days*60) < 10){
            fprintf(out, "0%dm ", mins - (days*60));
        } else{
            fprintf(out, "%dm ", mins  - (days*60));
        }

        //print out the seconds according to the seconds
        //if the seconds are only one digit, add a zero for formatting reasons
        if(secs  - (mins*60) < 10){
            fprintf(out, "0%ds\n", secs  - (mins*60));
        } else {
            fprintf(out, "%ds\n", secs - (mins*60));
        }

 
    }

    //close the in and out files
    fclose(in);
    fclose(out);

    return 0;
}