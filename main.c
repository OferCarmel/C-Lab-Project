#include <stdio.h>

#include "macro_processor.h"



/* Main function to initiate the process */

int main() {

    const char* input_filename = "input.asm";

    const char* output_filename = "output.asm";

    process_file(input_filename, output_filename);

    return 0;

}
