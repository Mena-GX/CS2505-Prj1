#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//reads the entire file and spits it out as a string
char* readEntireFile(char* fileName);

//takes a string and gives a portion of it as requested
//Ex: "Hello World"
//substring ("Hello World", 0, 3)
//return -> Hel
char* substring(char * fullString, int start, int length);

//finds the difference between the days, minutes, and seconds of the two coordinates
//and returns it as the sum of seconds
int difference(char * coordPair);

//convert seconds to minutes and returns it as an integer
int secsToMins(int secs);

//converts minutes to days and returns it as an integer
int minsToDays(int mins);
