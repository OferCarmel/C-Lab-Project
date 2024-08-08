

typedef struct Error {
    int error_id;     /* Unique id for the error */
    char* error_message;  /* Error message - details */
} Error;


/* Represents error codes for various types of errors */
typedef enum ERROR_CODES {
    /* The following errors are macro related or general */
    ERROR_CODE_0 = 0,
    ERROR_CODE_1,
    ERROR_CODE_2,
    ERROR_CODE_3,
    ERROR_CODE_4,
    ERROR_CODE_5,
    ERROR_CODE_6,
    ERROR_CODE_7,
    ERROR_CODE_8,
    ERROR_CODE_9,
    ERROR_CODE_10,
    ERROR_CODE_11,
    ERROR_CODE_12,
    ERROR_CODE_13,
    ERROR_CODE_14,
    ERROR_CODE_15,
    ERROR_CODE_16,
    ERROR_CODE_17,
    /* Enumeration skip for future macro related errors */
} ERROR_CODES;

/**
 * @brief Prints an external error message.
 *
 * This function prints to stdout an error that is related to an error in the source file
 * with error number and the error location in the source file
 * @param error_code error number
 * @param file a pointer to a struct which contains the source file name and line information
 */
void print_external_error(int error_code, location file);

/**
 * @brief Prints an internal error message.
 *
 * This function prints to stdout an error that is a result of an internal process and NOT an error in the source file
 * @param error_code error number
 */
void print_internal_error(int error_code);
