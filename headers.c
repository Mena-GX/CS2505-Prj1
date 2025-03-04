#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//takes a string and gives a portion of it as requested
//Ex: "Hello World"
//substring ("Hello World", 0, 3)
//return -> Hel
char* substring(char * fullString, int start, int length){
    //allocate memory for the substring
    char* sub = (char*)malloc(sizeof(char) * (length + 1));

    //get the characters and add them to the substring one by one
    for(int i = 0; i < length; i++){
        sub[i] = fullString[start+i];
    }

    //remove any extraneous spaces
    sub[length] = '\0';

    return sub;
}

//reads the entire file and spits it out as a string
char* readEntireFile(char* fileName){
    //opens the file to read
    FILE* open;
    open = fopen(fileName, "r");

    //if the file is null, likely doesn't exist or couldn't find it
    //return error code
    if (open == NULL){
        printf("The file is not opened search c");
        exit(1);
    }

    char *file_content;
    long file_size;

    //Looks for the end of the file starting from the beginning
    fseek(open, 0, SEEK_END);
    //once the end of the file is found, it uses the position to store the size of the file
    file_size = ftell(open);

    //goes back to the beginning of the file
    rewind(open);

    //allocating memory for the file content
    file_content = (char*)malloc(file_size+1);

    //if file content is still null allocating memory has failed
    if(file_content == NULL){
        printf("Failed Memory");
    }

    //if the file can't be read return error
    if((long int)fread(file_content, 1, file_size, open) != file_size){
        perror("Error reading file");
        free(file_content);
    }

    file_content[file_size] ='\0';
    fclose(open);
    return file_content;
    

}

//finds the difference between the days, minutes, and seconds of the two coordinates
//and returns it as the sum of seconds
int difference(char * coordPair){
    char* day1W = substring(coordPair, 0, 3);
    char* day2W = substring(coordPair, 17, 3);
    char* day1N = substring(coordPair, 9, 2);
    char* day2N = substring(coordPair, 26, 2);

    char* min1W = substring(coordPair, 3, 2);
    char* min2W = substring(coordPair, 20, 2);
    char* min1N = substring(coordPair, 11, 2);
    char* min2N = substring(coordPair, 28, 2);

    char* sec1W = substring(coordPair, 5, 2);
    char* sec2W = substring(coordPair, 22, 2);
    char* sec1N = substring(coordPair, 13, 2);
    char* sec2N = substring(coordPair, 30, 2);

    int diffDayW = atoi(day1W) - atoi(day2W);
    int diffDayN = atoi(day1N) - atoi(day2N);

    int diffMinW = atoi(min1W) - atoi(min2W);
    int diffMinN = atoi(min1N) - atoi(min2N);

    int diffSecW = atoi(sec1W) - atoi(sec2W);
    int diffSecN = atoi(sec1N) - atoi(sec2N);

    if(diffDayN < 0){
        diffDayN*=-1;
        diffMinN*=-1;
        diffSecN*=-1;
    }

    if(diffDayW < 0){
        diffDayW*=-1;
        diffMinW*=-1;
        diffSecW*=-1;
    }

    if(diffMinN < 0){
        if(diffDayN == 0){
            diffMinN*=-1;
            diffSecN*=-1;
        } else {
            diffDayN--;
            diffMinN+=60;
        }
    }

    if(diffMinW < 0){
        if(diffDayW == 0){
            diffMinW*=-1;
            diffSecW*=-1;
        } else {
            diffDayW--;
            diffMinW+=60;
        }
    }

    if(diffSecN < 0){
        if(diffMinN == 0){
            diffSecN*=-1;
        } else {
            diffMinN--;
            diffSecN+=60;
        } 
    }

    if(diffSecW < 0){
        if(diffMinW == 0){
            diffSecW*=-1;
        } else{
            diffMinW--;
            diffSecW+=60;
        }
    }

    int sum = ((diffDayN+diffDayW)*360)+((diffMinN+diffMinW)*60)+diffSecN+diffSecW;

    return sum;
}

//convert seconds to minutes and returns it as an integer
int secsToMins(int secs){

    //if seconds are less than 60, you can't convert into any minutes
    //return 0
    if(secs < 60){
        return 0;
    }

    //if above 60, divide by 60
    double m = secs / 60.0;
    double part;


    //remove fractional part
    modf(m, &part);

    //return whole number
    return (int)part;

    
}

//converts minutes to days and returns it as an integer
int minsToDays(int mins){
    //if minutes are less than 60, you can't convert to days
    //return 0
    if(mins < 60){
        return 0;
    }

    //if above 60, divide by 60
    double d = mins / 60.0;
    double part;

    //remove fractional part
    modf(d, &part);

    //return whole number
    return part;
}