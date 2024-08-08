#include <stdio.h>
#include "../HeaderFiles/macro_processor.h"
#include "../HeaderFiles/file_operations.h"


/* 
****** to test the macro_processor run this: ****************************
#include <stdio.h>
#include "macro_processor.h"

/* Main function to initiate the process */
int main() {

    const char* input_filename = "input.asm";

    const char* output_filename = "output.asm";

    process_file(input_filename, output_filename);

    return 0;
}
*/ 

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


