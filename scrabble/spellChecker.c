#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    static const char filename[] = "words.txt";

    /*if (argc != 2) {
        printf("Must provide ONE word as input.\n");
        return 0;
    }*/
    
    char* word = argv[1];
    FILE *file = fopen (filename, "r");
    
    if (file == NULL) {
        printf("Please place linux.words in the same folder this command is executed.");
        return 0;
    }
    
    char line [ 128 ];
    char *dictionary[50000];
    int dictionary_count = 0;
    
    //gets each word, converts it to lower case
    while ( fgets ( line, sizeof line, file ) != NULL ) {
        if (tolower(line[0]) == tolower(word[0])) {
            /*checks if the first character in both words are the same and 
            adds it to a dictionary list*/
            
            dictionary[dictionary_count] = malloc(strlen(line)+1);
            strcpy(dictionary[dictionary_count], line);
            dictionary_count++;
            
            /*breaks if the first letter of both words are not the same*/
        } else if (dictionary_count > 0 && tolower(line[0]) != tolower(word[0])) {
            break; 
        }
    }
    
    /*char* suggestions[10];
    int suggestion_count = 0, size_count = 0;
    
    for (size_count = 0; size_count < strlen(word); size_count++) {
        int i = 0;
        while(i < dictionary_count && suggestion_count < 10) {
        
            if (strlen(dictionary[i]) == (strlen(word) - size_count) && starts_with(dictionary[i], word) == 1) {
                suggestions[suggestion_count] = malloc(strlen(dictionary[i])+1);
                strcpy(suggestions[suggestion_count], dictionary[i]);
                suggestion_count += 1;
            }
            
            i++;
        }
    }
    
    if (suggestion_count == 0) {
        printf("No suggestions found for %s", word);
        exit(1);
    }
        
    printf("Printing suggestions\n");
    
    int j;
    
    for (j = 0; j < suggestion_count; j++) {
        printf("%d - %s", (j + 1), suggestions[j]);
    }
    
    exit(1);
}
*/

int starts_with(char *substring, char *string) {
    int i,
        substring_length = strlen(substring),
        string_length = strlen(string);
        
    if (substring_length > string_length) {
        return 0;
    }
    
    for (i = 0; i < substring_length - 1; i++) {
        if (tolower(substring[i]) != tolower(string[i])) {
            return 0;
        }
    }
    
    return 1;
}