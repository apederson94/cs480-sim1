#ifndef STR_UTILS
#define STR_UTILS

//ALL STRING-RELATED UTILITIES

//RETURNS STRING LENGTH
int str_len(const char* string);

//COPIES ONE STRING INTO ANOTHER
void str_copy(char *src, char *dest);

//READS THE LAST 4 OF A STRING TO DETERMINE THE EXTENSION
char* get_fileExt(char* src);

//COMPARES TWO STRINGS
int str_cmp(const char* src, char* target);

//CHECKS TO SEE IF STRING HAS SUBSTRING
int str_contains(char* src, char* substr);

//RETURNS END SYMBOL POSITION OF SUBSTRING IN STRING
int sub_str_pos(char *src, char *target);

//REVERSES A STRING IN PLACE
void rev_str(char *src);

//CREATES A SUBSTRING FROM INDEX START TO END AND STORES IT IN substr
void sub_str(char *src, int start, int end, char *substr);

//REMOVES ALL NEWLINE CHARACTERS IN A STRING
void remove_newline(char *src);

//REMOVES ALL NON_SYMBOL CHARACTERS
void remove_non_symbols(char *src);

//CONVERTS A STRING TO A FLOAT VALUE
float s2f(char *src);

//converts a string into an int value
int s2i(char *src);

//CHECKS PROVIDED STRING AGAINST COMPATIBLE SCHEDULER TYPES
int check_cpu_sched(char *src);

//CHECKS STRING AGAINST COMPATIBLE LOG TO TYPES
int check_log_to(char *src);

//SETTS ALL VALUES IN A STRING TO NULL
void str_clear(char *src);

//REMOVES ALL NON-NUMBERS FROM A STRING
void str_rm_non_numbers(char *src);

//CHECKS IF A CHARACTER IS A NUMBER
int char_is_num(char src);

//CHECKS IF A CHARACTER IS UPPERCASE
int char_is_upper(char src);

#endif