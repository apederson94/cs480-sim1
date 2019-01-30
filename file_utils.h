#include <stdio.h>
#include "str_utils.h"
#include "booleans.h"
#include "data_structures.h"
#ifndef FILE_UTILS
#define FILE_UTILS

//all file utilities created by me

//reads values in from config file 
int read_config_file(FILE* config, struct config_values *settings) {
    char line[100];
    int pos;
    int len;
    int val_iter = 0;
    while (fgets(line, 100, config)) {
        char *value = (char*) malloc(sizeof(char) * 100);
        //gets position of the termination of the line name
        pos = sub_str_pos(line, ":");
        //continues only if the line contains a ":" symbol
        if (pos > 0) {
            //gets the length of hte line
            len = str_len(line);
            //gets a sub string from the position of the line name end to the end of the line
            sub_str(line, pos, len, value);
            if (str_contains(line, "Version/Phase")) {
                remove_non_chars(value);
                float ver = a2f(value);
                //returns error code 1 if versioning is incorrect
                if (ver > 10.0f || ver < 0.0f) {
                    return 1;
                }
                settings->ver = ver;

            } else if (str_contains(line, "Log File")) {
                remove_non_chars(value);
                //stores log path value if File or Both is chosen, N/A otherwise
                if (str_cmp(settings->log_to, "File") 
                || str_cmp(settings->log_to, "Both")) {
                    settings->log_path = value;
                } else {
                    settings->log_path = "N/A";
                }

            } else if (str_contains(line, "CPU Scheduling Code")) {
                remove_non_chars(value);
                /*returns error code 2 if cpu scheduling code is incorrect
                FCFS-N is chosen if NONE was supplised by the config file*/
                if (str_cmp(value, "NONE")) {
                    settings->cpu_sched = "FCFS-N";
                } else if (!check_cpu_sched(value)) {
                    return 2;
                 } else {
                    settings->cpu_sched = value;
                 }

            } else if (str_contains(line, "Quantum Time")) {
                remove_non_chars(value);
                int num = a2i(value);
                //returns error code 3 if quantum time supplied is incorrect
                if (num > 100 || num < 0) {
                    return 3;
                }
                settings->quantum_time = num;

            } else if (str_contains(line, "Memory Available")) {
                remove_non_chars(value);
                int num = a2i(value);
                //returns error code 4 if too much or too little memory available
                if (num < 0 || num > 102400) {
                    return 4;
                }
                settings->memory_available = a2i(value);

            } else if (str_contains(line, "Processor Cycle Time")) {
                remove_non_chars(value);
                int num = a2i(value);
                //return error code 5 if processor cycle time too high or too low
                if (num < 1 || num > 1000) {
                    return 5;
                }
                settings->cpu_cycle_time = num;

            } else if (str_contains(line, "I/O Cycle Time")) {
                remove_non_chars(value);
                int num = a2i(value);
                //returns error code 6 if I/O cycle time too high or too low
                if (num < 1 || num > 10000) {
                    return 6;
                }
                settings->io_cycle_time = num;

            } else if (str_contains(line, "Log To")) {
                remove_non_chars(value);
                //returns error code 7 if log to line contains an unsupported option
                if (!check_log_to(value)) {
                    return 7;
                }
                settings->log_to = value;

            } else if (str_contains(line, "File Path:")) {
                remove_non_chars(value);
                //returns error code 8 if file path contains directories
                if (str_contains(value, "/")) {
                    return 8;
                }
                settings->mdf_path = value;
            }
        }
        val_iter++;
    }
    return 0;
}

//TODO: MINOR ERRORS STILL LEFT IN READING IN THE META-DATA

//sets action data based on provided string
void set_action_data(char *command, struct sim_action *action) {
    int cmd_length, i, op_flag, op_iter, value;
    char current_char, op_str[20];

    cmd_length = str_len(command);
    i = 0;
    value = 0;
    op_iter = 0;
    op_flag = FALSE;
    current_char = command[i];

    while (i < cmd_length) {
        if (!char_cmp(current_char, ' ') 
        && char_is_upper(current_char)) {
            action->command_letter = command[i];
        } else if (char_cmp(current_char, '(')) {
            op_flag = TRUE;
        } else if (char_cmp(current_char, ')')) {
            op_str[op_iter] = '\0';
            str_copy(op_str, action->operation_string);
            op_flag = FALSE;
        } else if (op_flag) {
            op_str[op_iter] = current_char;
            op_iter++;
        } else if (!op_flag 
        && !char_cmp(current_char, ';') 
        && char_is_num(current_char)) {
            value *= 10;
            value += (current_char - 48);
        }
        i++;
        current_char = command[i];
    }
    action->assoc_val = value;
}

//reads in all information from the meta data file
void read_meta_data_file(FILE *mdf, struct sim_action **first_action) {
    char line[100];
    int line_length, i, cmd_iter;
    cmd_iter = 0;
    char command[40];
    struct sim_action *current = (struct sim_action*) malloc(sizeof(struct sim_action));

    current = *first_action;

    //TODO: FIX OP STIRNG

    while (fgets(line, 100, mdf)) {
        //printf("COMMAND_ORIG:\n" );
        if (!str_contains(line, "Start Program Meta-Data") && !str_contains(line, "End Program Meta-Data")) {
            line_length = str_len(line);
            for (i = 0; i < line_length; i++) {
                command[cmd_iter] = line[i];
                cmd_iter++;
                if (char_cmp(line[i], ';')) {
                    struct sim_action *next = (struct sim_action*) malloc(sizeof(struct sim_action));
                    command[cmd_iter] = '\0';
                    cmd_iter = 0;
                    set_action_data(command, current);
                    current->next = next;
                    current = next;
                }
            }
        }
    }
}

#endif