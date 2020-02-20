//  John Sullivan
//  CSC 412
//  Prof. Herve
//  Assignment 02

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// This structure will hold all of the images, their x and y coordinate, name and index
typedef struct Location{
    int latitude;
    int longitude;
    char * name;
    int index;
} Location;

// This structure will hold a list of images, a name of a location, and a counter for how many images are in the structure.
typedef struct LocNameList{
    char* locName;
    Location ** images;
    int imagesCount;
} LocNameList;

// Function definitions. 
int readArgs(int argc, char* argv[], Location * locationArray, LocNameList * locNameList, int * nameListLength);
void printLocation(Location loc);
char* getQuery(Location * locs, LocNameList * locNameList);
void processQuery(char* query, Location * locs, int sizeOfLocArray, LocNameList * locNameList, int * nameListLength);
bool checkQuery(char* query);

// In the main, we'll allocate memory for a list of images, as well as a list of locations and their images.
// This will call getQuery() and processQuery() over and over again until the user exits. 
int main(int argc, char* argv[]){
    int locationsListSize = argc / 3;
    Location * locs = (Location *)malloc(locationsListSize * sizeof(Location));
    LocNameList * locNameList = (LocNameList *)malloc(locationsListSize * sizeof(LocNameList));
    int len = 0;
    int * nameListLength = &len;

    // Not only does this function call read the arguments from stdin, but also will return the size of our images list.
    int sizeOfLocArray = readArgs(argc, argv, locs, locNameList, nameListLength);

    // Get the first query, process it and then loop until the user stops the program. 
    char* query = getQuery(locs, locNameList);
    do{
        processQuery(query, locs, sizeOfLocArray, locNameList, nameListLength);
    } while(query = getQuery(locs, locNameList)); // had to pass parameters of structs so they could be freed at exit time. 

    return 0;
}

/* processQuery will analyze the user query and decide what to do with it. 
 * @param query => this is what is read from the user. Something like -n Charleston could be an example of a valid query. 
 * @param locs  => this is the list of images that has been collected from the arguments. 
 * @param locArraySize => this is the size of the list of images. 
 * @param locNameList  => this is the list of location names that holds lists of images associated with it. 
 * @param nameListLength => this is the length of my locNameList. (how many locations there are)
 */
void processQuery(char* query, Location * locs, int locArraySize, LocNameList * locNameList, int * nameListLength){
    int queryLength = strlen(query);
    int index = 3;
    size_t size = 32;
    int i = 0;
    int foundVal = 0;
    char* queryValue = (char*)malloc(size * sizeof(char));

    // This loop will read everything after "-n " or "-x " or "-y " including the space. 
    while(query[index] != '\0'){
            queryValue[i] = query[index];
            index++;
            i++;
    }

    // Decide which query to run
    switch(query[1]){ // Check the character after the '-'
        case 'n': // Name query 
            queryValue[i-1] = 0;
            for(int j = 0; j < *(nameListLength); j++){
                if(strcmp(locNameList[j].locName, queryValue) == 0){
                    for(int k = 0; k < locNameList[j].imagesCount; k++){
                        printLocation(*locNameList[j].images[k]);
                        foundVal = 1;
                    }
                }
            }
            break;
        case 'x': // Latitude query
            for(int j = 0; j < locArraySize; j++){
                if(locs[j].latitude == atoi(queryValue)){
                    printLocation(locs[j]);
                    foundVal = 1;
                }
            }
            break;
        case 'y': // Longitude query
            for(int j = 0; j < locArraySize; j++){
                if(locs[j].longitude == atoi(queryValue)){
                    printLocation(locs[j]);
                    foundVal = 1;
                }
            }
        default: // Not a valid query 
            printf("Invalid query. Usage: -n <name> OR -x <latitude> OR -y <longitude>\n");   
    }

    if(query[1] == 'a' && query[2] == 'l' && query[3] == 'l'){ // -all query
        for(int k = 0; k < locArraySize; k++){
            printLocation(locs[k]);
            foundVal = 1;
        }
    }

    // Do this if no images were found at a query. 
    if(!foundVal)
        printf("No images found at provided query location.\n");
    free(queryValue);
}

/* readArgs will take all of the arguments from stdin (console) user input and store them in appropriate locations and process them.  
 * @param argc => the number of arguments 
 * @param argv  => the list of arguments
 * @param locationArray => our allocated list of images
 * @param locNameList  => our allocated list of location names
 * @param nameListLength => this is the length of my locNameList. (how many locations there are)
 */
int readArgs(int argc, char* argv[], Location * locationArray, LocNameList * locNameList, int * nameListLength){
    int idx = 0;
    int i = 1;
    int locationIndex = 0;
    int locExists = 0;
    size_t size = 32;

    // We only want to read an x, y, and name value so we will loop until (amount of arguments - 2) and index appropriately.
    while(i < (argc - 2)){
        locExists = 0;
        Location newLoc; // makes a new instance of an image

        // We will assign values to our image. 
        newLoc.index = idx;
        newLoc.latitude = atoi(argv[i]);
        newLoc.longitude = atoi(argv[i+1]);
        newLoc.name = argv[i+2];
        locationArray[locationIndex] = newLoc;

        // Check if this location exists in our location array, if not we'll make space for it and increment our length. 
        for(int loc = 0; loc < *(nameListLength); loc++){
            if(locNameList[loc].locName == newLoc.name){
                locNameList[loc].images[locNameList[loc].imagesCount] = &locationArray[locationIndex];
                locNameList[loc].imagesCount += 1;
                locExists = 1;   
            }
        }
        if(locExists == 0){
            locNameList[*(nameListLength)].images = (Location **)malloc(size * sizeof(Location));
            locNameList[*(nameListLength)].locName = newLoc.name;
            locNameList[*(nameListLength)].imagesCount = 0;
            locNameList[*(nameListLength)].images[locNameList[*(nameListLength)].imagesCount] = &locationArray[locationIndex];
            locNameList[*(nameListLength)].imagesCount += 1;
            *nameListLength += 1;
        }
        idx++;
        locationIndex++;
        i+=3;
    }

    //This will return the size of the array. 
    return locationIndex;
}

/* printLocation will quite obviously print the passed image values. 
 * @param loc => this is the image information that we will print. 
 */
void printLocation(Location loc){
    printf("image %03d. location: %4d, %4d.  Name: %s\n", loc.index, loc.latitude, loc.longitude, loc.name);
}

/* getQuery will wait for a user to input a query, check if it's an exit query, if not return it. */
char* getQuery(Location * locs, LocNameList * locNameList){
    size_t size = 32;
    char* exitString = "exit";
    char* upperExitString = "EXIT";
    char* anotherExitString = "Exit";
    char* qryChecker =  (char*)malloc(32 * sizeof(char));
    char* query = (char*)malloc(size * sizeof(char));
    getline(&query, &size, stdin);
    int i = 0;
    while(query[i] != '\0'){
        qryChecker[i] = query[i];
        i++;
    }
    qryChecker[i-1] = 0;
    if(strcmp(qryChecker, exitString) == 0){
        free(qryChecker);
        free(query);
        free(locs);
        free(locNameList);
        exit(0);
    }
    if(strcmp(qryChecker, upperExitString) == 0){
        free(qryChecker);
        free(query);
        free(locs);
        free(locNameList);
        exit(0);
    } 
    if(strcmp(qryChecker, anotherExitString) == 0){
        free(qryChecker);
        free(query);
        free(locs);
        free(locNameList);
        exit(0);
    }
    return query;
}