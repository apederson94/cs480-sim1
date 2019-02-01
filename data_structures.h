#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

//DATA STRUCTURES AND THEIR RELATED FUNCTIONS

//HOLDS CONFIG FILE INFORMATION
struct config_values
{
    float ver;

    char *mdf_path;
    char *cpu_sched;
    char *log_path;
    char *log_to;

    int quantum_time;
    int memory_available;
    int cpu_cycle_time;
    int io_cycle_time;
};

//HOLDS ALL INFORMATION PERTAINING TO ONE ACTION
struct sim_action 
{
    char command_letter;
    char operation_string[20];
    int assoc_val;
    struct sim_action *next;
};

//FREES ALL MEMORY ASSOCIATED WITH SIM_ACTIONS
void free_actions(struct sim_action* head) 
{
    struct sim_action *tmp;

    while (head) 
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

//PRINTS ALL RELEVANT SIM_ACTION INFORMATION
void print_sim_action(struct sim_action *src) 
{
    printf("Op code letter: %c\n", src->command_letter);
    printf("Op code name  : %s\n", src->operation_string);
    printf("Op code value : %d\n", src->assoc_val);
}

//PRINTS ALL ALL RELEVANT SIM_ACTION INFORMATION FOR ALL SIM_ACTIONS
void print_sim_actions(struct sim_action *head) 
{
    while (head->next) 
    {
        print_sim_action(head);
        printf("\n");
        head = head->next;
    }
}

//PRINTS ALL INFORMATION FORM A CONFIG_VALUES STRUCT
void print_config_values(struct config_values *src) 
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
int set_action_data(char *command, struct sim_action *action) 
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
        return 18;
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
                return 12;

            } else if (!str_cmp(op_str, "run") && action->command_letter == 'P') 
            {
                return 13;

            } else if (!str_cmp(op_str, "hard drive") && !str_cmp(op_str, "keyboard")
            && action->command_letter == 'I') 
            {
                return 14;
                
            } else if (!str_cmp(op_str, "hard drive") && !str_cmp(op_str, "printer")
            && !str_cmp(op_str, "monitor") && action->command_letter == 'O') 
            {
                return 15;

            } else if (!str_cmp(op_str, "allocate") && !str_cmp(op_str, "access") 
            && action->command_letter == 'M') 
            {
                return 16;
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
        return 17;
    }
    action->assoc_val = value;
    return 0;
}

#endif