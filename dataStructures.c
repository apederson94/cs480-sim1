#include "dataStructures.h"
#include "booleans.h"
#include "errors.h"

//DATA STRUCTURE FUNCTIONS

//FREES ALL MEMORY ASSOCIATED WITH simActionS
void free_actions(struct simAction* head) 
{
    struct simAction *tmp;

    while (head) 
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

//PRINTS ALL RELEVANT simAction INFORMATION
void print_simAction(struct simAction *src) 
{
    printf("Op code letter: %c\n", src->command_letter);
    printf("Op code name  : %s\n", src->operation_string);
    printf("Op code value : %d\n", src->assoc_val);
}

//PRINTS ALL ALL RELEVANT simAction INFORMATION FOR ALL simActionS
void print_simActions(struct simAction *head) 
{
    while (head->next) 
    {
        print_simAction(head);
        printf("\n");
        head = head->next;
    }
}

//PRINTS ALL INFORMATION FORM A configValues STRUCT
void print_configValues(struct configValues *src) 
{
    printf("Version                : %f\n", src->ver);
    printf("Program file name      : %s\n", src->mdf_path);
    printf("CPU schedule selection : %s\n", src->cpu_sched);
    printf("Quantum time           : %d\n", src->quantum_time);
    printf("Memory Available       : %d\n", src->memory_available);
    printf("Process cycle rate     : %d\n", src->cpu_cycle_time);
    printf("I/O cycle rate         : %d\n", src->io_cycle_time);
    printf("Log to selection       : %s\n", src->log_to);
    printf("Log file name          : %s\n", src->log_path);
}

//TURNS A COMMAND STRING INTO AN ACTION
int set_action_data(char *command, struct simAction *action) 
{
    int cmd_length, i, op_flag, op_iter, value;
    char current_char, op_str[20];

    cmd_length = str_len(command);
    i = 0;
    value = 0;
    op_iter = 0;
    op_flag = FALSE;
    current_char = command[i];

    if (!str_contains(command, "(") || !str_contains(command, ")")
    || !str_contains(command, ";")) 
    {
        return CORRUPTED_MDF_ERROR;
    }

    while (i < cmd_length) {
        if (!(current_char == ' ') 
        && char_is_upper(current_char)) 
        {
            action->command_letter = command[i];

        } else if (current_char == '(') 
        {
            op_flag = TRUE;

        } else if (current_char == ')') 
        {
            op_str[op_iter] = '\0';

            if ((!str_cmp(op_str, "start") && !str_cmp(op_str, "end")
            && (action->command_letter == 'S' || action->command_letter == 'A'))) 
            {
                return SA_OP_STRING_ERROR;

            } else if (!str_cmp(op_str, "run") && action->command_letter == 'P') 
            {
                return P_OP_STRING_ERROR;

            } else if (!str_cmp(op_str, "hard drive") && !str_cmp(op_str, "keyboard")
            && action->command_letter == 'I') 
            {
                return I_OP_STRING_ERROR;
                
            } else if (!str_cmp(op_str, "hard drive") && !str_cmp(op_str, "printer")
            && !str_cmp(op_str, "monitor") && action->command_letter == 'O') 
            {
                return O_OP_STRING_ERROR;

            } else if (!str_cmp(op_str, "allocate") && !str_cmp(op_str, "access") 
            && action->command_letter == 'M') 
            {
                return M_OP_STRING_ERROR;
            }
            str_copy(op_str, action->operation_string);
            op_flag = FALSE;
        } else if (op_flag) 
        {
            op_str[op_iter] = current_char;
            op_iter++;
        } else if (!op_flag 
        && !(current_char == ';') 
        && char_is_num(current_char)) 
        {
            value *= 10;
            value += (current_char - 48);
        }
        i++;
        current_char = command[i];
    }
    if (value < 0) {
        return NEGATIVE_MDF_VALUE_ERROR;
    }
    action->assoc_val = value;
    return 0;
}