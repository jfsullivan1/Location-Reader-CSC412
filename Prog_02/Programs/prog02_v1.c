//  John Sullivan
//  CSC 412
//  Prof. Herve
//  Assignment 02

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This structure will hold all of the images, their x and y coordinate, name and index
typedef struct Location{
    int latitude;
    int longitude;
    char * name;
    int index;
} Location;

// Function definitions. 
int readArgs(int argc, char* argv[], Location * locationArray);
void printLocation(Location loc);
char* getQuery();
void processQuery(char* query, Location * locs, int sizeOfLocArray);

// In the main, we'll allocate memory for a list of images.
// This will call getQuery() and processQuery() over and over again until the user exits. 
int main(int argc, char* argv[]){
    int locationsListSize = argc / 3;
    Location * locs = (Location *)malloc(locationsListSize * sizeof(Location));

    // Not only does this function call read the arguments from stdin, but also will return the size of our images list.
    int sizeOfLocArray = readArgs(argc, argv, locs);

    // Get the first query, process it and then loop until the user stops the program. 
    char* query = getQuery();
    do{
        processQuery(query, locs, sizeOfLocArray);
    } while(query = getQuery());
    return 0;
}

/* processQuery will analyze the user query and decide what to do with it. 
 * @param query => this is what is read from the user. Something like -n Charleston could be an example of a valid query. 
 * @param locs  => this is the list of images that has been collected from the arguments. 
 * @param locArraySize => this is the size of the list of images. 
 */
void processQuery(char* query, Location * locs, int locArraySize){
    int queryLength = strlen(query);
    int index = 3;
    size_t size = 32;
    int i = 0;
    char* queryValue = (char*)malloc(size * sizeof(char));
    int foundVal = 0;
    
    // This loop will read everything after "-n " or "-x " or "-y " including the space. 
    while(index < queryLength){
        queryValue[i] = query[index];
        index++;
        i++;
    }

    // Decide which query to run
    if (query[1] == 'n'){ // Name query 
        queryValue[i-1] = 0;
        for(int j = 0; j < locArraySize; j++){
            if(strcmp(locs[j].name, queryValue) == 0){
                printLocation(locs[j]);
                foundVal = 1;
            }
        }
    }
    else if (query[1] == 'x'){ // Latitude query
        for(int j = 0; j < locArraySize; j++){
            if(locs[j].latitude == atoi(queryValue)){
                printLocation(locs[j]);
                foundVal = 1;
            }
        }
    }
    else if (query[1] == 'y'){ // Longitude query
        for(int j = 0; j < locArraySize; j++){
            if(locs[j].longitude == atoi(queryValue)){
                printLocation(locs[j]);
                foundVal = 1;
            }
        }
    }
    else if(query[1] == 'a' && query[2] == 'l' && query[3] == 'l'){ // -all query 
        for(int k = 0; k < locArraySize; k++){
            printLocation(locs[k]);
            foundVal = 1;
        }
    }
    else{ // Not a valid query
        printf("Invalid query. Usage: -n <name> OR -x <latitude> OR -y <longitude>\n");
    }
    if(!foundVal)
        printf("No images found at provided query location.\n");
    free(queryValue);
}

/* readArgs will take all of the arguments from stdin (console) user input and store them in appropriate locations and process them.  
 * @param argc => the number of arguments 
 * @param argv  => the list of arguments
 * @param locationArray => our allocated list of images
 */
int readArgs(int argc, char* argv[], Location * locationArray){
    int idx = 000;
    int i = 1;
    int locationIndex = 0;
    // We only want to read an x, y, and name value so we will loop until (amount of arguments - 2) and index appropriately.
    while(i < (argc - 2)){
        Location newLoc;
        newLoc.index = idx;
        newLoc.latitude = atoi(argv[i]);
        newLoc.longitude = atoi(argv[i+1]);
        newLoc.name = argv[i+2];
        locationArray[locationIndex] = newLoc;
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
char* getQuery(){
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
        exit(0);
    }
    if(strcmp(qryChecker, upperExitString) == 0){
        free(qryChecker);
        free(query);
        exit(0);
    } 
    if(strcmp(qryChecker, anotherExitString) == 0){
        free(qryChecker);
        free(query);
        exit(0);
    }
    return query;
}