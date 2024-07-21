#include <stdio.h>
#include "../HeaderFiles/macro_processor.h"
#include "../HeaderFiles/file_operations.h"




/* Main function to initiate the process */

int main() {

    char* input_filename = "../inputs_and_outputs/text.as";

 /* const char* output_filename = "../inputs_and_outputs/output.asm";  */
    
    char* line, *word;
    
    FILE* file;
    file = openFile(input_filename);

    if ((line = get_line(file)) != NULL)
    {
        while ((word = get_word(line)) != NULL)
        {
            printf("|%d| ", sizeof(word - 1));
            line+=sizeof(word-1);
            printf("%s ", word);
            free(word);
        }
    }
    
    /*
    process_file(input_filename, output_filename);
    */
    return 0;

}


