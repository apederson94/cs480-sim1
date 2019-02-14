#include "booleans.h"
#include "mathUtils.h"
//ALL STRING-RELATED UTILITIES

//RETURNS STRING LENGTH
int str_len(const char* string) 
{
    char curr = string[0];
    int len = 0;
    while (curr != '\0') 
    {
        len += 1;
        curr = string[len];
    }

    return len;
}

//COPIES ONE STRING INTO ANOTHER
void str_copy(char *src, char *dest) 
{
    int len = str_len(src);
    int i;
    if (src && dest) 
    {
        for (i = 0; i < len; i++) 
        {
            dest[i] = src[i];
        }
        dest[i] = '\0';
    }
}

//READS THE LAST 4 OF A STRING TO DETERMINE THE EXTENSION
char* get_fileExt(char* src) 
{
    int len = str_len(src);
    char *ext = (char*) malloc(sizeof(char) * 5);
    ext[4] = '\0';

    for (int i = 4; i > 0; i--) 
    {
        ext[4-i] = src[len-i];
    }

    return ext;
}

//COMPARES TWO STRINGS
int str_cmp(const char* src, char* target) 
{
    int src_len = str_len(src);

    if (src_len != str_len(target)) 
    {
        return FALSE;
    }

    for (int i = 0; i < src_len; i++) 
    {
        if (src[i] != target[i])
        {
            return FALSE;
        }
    }

    return TRUE;
}

//CHECKS TO SEE IF STRING HAS SUBSTRING
int str_contains(char* src, char* substr) 
{
    int src_iter = 0;
    int subsr_iter = 0;
    char src_curr = src[0];
    char substr_char = substr[0];

    while (src_curr && substr_char) 
    {
        src_curr = src[src_iter];

        if (src_curr == substr_char) 
        {
            subsr_iter++;
            substr_char = substr[subsr_iter];
            src_iter++;

        } else 
        {
            if (subsr_iter == 0) 
            {
                src_iter++;
            }

            subsr_iter = 0;
            substr_char = substr[0];
        }
    
    }

    //IF SUBSTR_CHAR = NULL, RETURN TRUE
    if (!substr_char) 
    {
        return TRUE;
    }

    return FALSE;
}

//RETURNS END SYMBOL POSITION OF SUBSTRING IN STRING
int sub_str_pos(char *src, char *target) 
{
    int src_iter = 0;
    int target_iter = 0;
    char src_char = src[0];
    char target_char = target[0];

    if (!str_contains(src, target)) 
    {
        return -1;
    }

    while (src_char && target_char) 
    {
        src_char = src[src_iter];
        
        if (src_char == target_char) 
        {
            target_iter++;
            target_char = target[target_iter];
            src_iter++;

        } else 
        {
            if (target_iter == 0) 
            {
                src_iter++;
            }

            target_iter = 0;
            target_char = target[0];
        }
    }

    return src_iter;
}

//REVERSES A STRING IN PLACE
void rev_str(char *src) 
{
    char tmp;
    int len = str_len(src) - 1; //IGNORE NULL TERMINATOR
    int half_len = len / 2;

    if (len % 2 != 0) 
    {
        half_len++;
    }

    for (int i = 0; i < half_len; i++) 
    {
        tmp = src[len - i];
        src[len - i] = src[i];
        src[i] = tmp;
    }
}

//CREATES A SUBSTRING FROM INDEX START TO END AND STORES IT IN substr
void sub_str(char *src, int start, int end, char *substr) 
{
    int iter = 0;

    for (int i = start; i < end; i++) 
    {
        substr[iter] = src[i];
        iter++;
    }

    substr[iter] = '\0';
}

//REMOVES ALL NEWLINE CHARACTERS IN A STRING
void remove_newline(char *src) 
{
    int pos = sub_str_pos(src, "\n");
    int i;
    char *tmp = (char*) malloc(sizeof(char) * 100);

    pos--; //MOVE TO FRONT OF THE SUBSTR POS FOUND

    while (pos > 0) 
    {
        for (i = 0; i < pos; i++) 
        {
            tmp[i] = src[i];
        }

        tmp[i] = '\0';
        str_copy(tmp, src);
        pos = sub_str_pos(src, "\n");
    }

    free(tmp);
}

//REMOVES ALL NON_SYMBOL CHARACTERS
void remove_non_symbols(char *src) 
{
    int len = str_len(src);
    int iter = 0;
    int i;
    char sym;
    char *tmp = (char*) malloc(sizeof(char) * 100);

    for (i = 0; i < len; i++) 
    {
        sym = src[i];

        if (sym > 32 && sym < 127) 
        {
            tmp[iter] = sym;
            iter++;
        }
    }

    tmp[i] = '\0';
    str_copy(tmp, src);
    free(tmp);
}

//CONVERTS A STRING TO A FLOAT VALUE
float s2f(char *src) 
{
    int iter = 0;
    char curr_char = src[0];
    int decimal_pos = sub_str_pos(src, ".");
    int places = decimal_pos - 2; //SUBTRACT 2 IN ORDER TO GET TO ONE BEFORE THE TARGET CHAR
    float num = 0.0f;

    while (curr_char) 
    {
        if (curr_char - 48 >= 0 && curr_char - 48 < 10) 
        {
            num += (curr_char - 48) * raiseToPower(10, places);
            places--;
        }

        iter++;
        curr_char = src[iter];
        
    }

    return num;
}

//converts a string into an int value
int s2i(char *src) 
{
    int len = str_len(src);
    int num = 0;
    int currNum;
    for (int pos = 0; pos < len; pos++) 
    {
        num *= 10;
        currNum = cs2(src[pos]);

        if (currNum > 0 && currNum < 10) 
        {
            num += currNum;
        } else {
            return NON_NUMERIC_STRING_ERROR;
        }
    }

    return num;
}

//EVALUATES A SINGLE CHAR TO AN INT
int c2i(char src)
{
    int num;
    switch (src)
    {
        case '0':
            num = 0;
            break;
        case '1':
            num = 1;
            break;
        case '2':
            num = 2;
            break;
        case '3':
            num = 3;
            break;
        case '4':
            num = 4;
            break;
        case '5':
            num = 5;
            break;
        case '6':
            num = 6;
            break;
        case '7':
            num = 7;
            break;
        case '8':
            num = 8;
            break;
        case '9':
            num = 9;
            break;
        default:
            num = 
    }
}

//CHECKS PROVIDED STRING AGAINST COMPATIBLE SCHEDULER TYPES
int check_cpu_sched(char *src) 
{
    if (str_cmp(src, "FCFS-N")
    || str_cmp(src, "SJF-N")
    || str_cmp(src, "SRTF-P")
    || str_cmp(src, "FCFS-P") 
    || str_cmp(src, "RR-P")) 
    {
        return TRUE;
    }

    return FALSE;
}

//CHECKS STRING AGAINST COMPATIBLE LOG TO TYPES
int check_log_to(char *src) 
{
    if (str_cmp(src, "Monitor") 
    || str_cmp(src, "File") 
    || str_cmp(src, "Both")) 
    {
        return TRUE;
    }

    return FALSE;
}

//SETTS ALL VALUES IN A STRING TO NULL
void str_clear(char *src) {
    int len = str_len(src);

    for (int i = len; i > 0; i--) {
        src[i] = '\0';
    }
}

//REMOVES ALL NON-NUMBERS FROM A STRING
void str_rm_non_numbers(char *src) 
{
    int i, len, num;

    i = 0;
    len = str_len(src);

    for (i = 0; i < len; i++) 
    {
        num = src[i] - 48;

        if (num > 9 || num < 0) 
        {
            src[i] = src[i+1];
        }
    }
}

//CHECKS IF A CHARACTER IS A NUMBER
int char_is_num(char src) 
{
    return src >= '0' && src <= 58;
}

//CHECKS IF A CHARACTER IS UPPERCASE
int char_is_upper(char src) 
{
    return src >= 'A' && src <= 'Z';
}