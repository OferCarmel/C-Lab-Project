/* Here we will mange all of the errors for this project */

/* TBD - create .h file */

typedef struct Error {
    int error_id;     /* Unique id for the error */
    char* error_message;  /* Error message - details */
} Error;

/* The array specifies the error code number and the matching error message.
 * Missing/value "-1" lines are intentionally left blank for future error codes */

Error errors[] = {
        {ERROR_CODE_0,  "No Error"},
        {ERROR_CODE_1,  "Failed to allocate memory"},
        {ERROR_CODE_2,  "Illegal register name. only r1-r7 are allowed"},
        {ERROR_CODE_3,  "The file name is too long - exceed xxx character "}, /* TBD*/
        {ERROR_CODE_4,  "The provided file name does not exist"},
        {ERROR_CODE_5,  ".am file is missing"},
        {ERROR_CODE_6,  ".as files name is missing"},
        {ERROR_CODE_7,  "Failed to open new file for writing"},
        {ERROR_CODE_8,  "Failed to open file for reading"},
        {ERROR_CODE_9,  "Error - macro without name definition"},
        {ERROR_CODE_10, "Error - no text allowed after macro name definition"},
        {ERROR_CODE_12, "no extra text allowed for endmcro"},
        {ERROR_CODE_13, "Macro has more than one definition"},
        {ERROR_CODE_14, "Line is too long - exceed 81 characters"},
        {ERROR_CODE_15, "Illegal opcode"},
        {ERROR_CODE_16, "Macro call before declaration"},
        {ERROR_CODE_17, "Illegal name for a macro"},
        {ERROR_CODE_18, ""},
        {-1,            ""},
        {-1,            ""},
        {-1,            ""},
};