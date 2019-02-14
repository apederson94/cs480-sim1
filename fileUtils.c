#include <stdio.h>
#include "str_utils.h"
#include "booleans.h"
#include "data_structures.h"

//ALL FILE-RELATED UTILITIES

//READS AND STORES ALL VALUES FROM CONFIG FILE
int read_config_file(char *fileName, struct configValues *settings) 
{
    char line[100];
    int pos;
    int len;
    int val_iter = 0;
    FILE *config = open(fileName, "r");

    while (fgets(line, 100, config)) 
    {
        char *value = (char*) malloc(sizeof(char) * 100);
        pos = sub_str_pos(line, ":"); 
        
        if (pos >= 0)
        { 
            len = str_len(line);
            sub_str(line, pos, len, value);

            if (str_contains(line, "Version/Phase")) 
            {
                remove_non_symbols(value);
                float ver = a2f(value);

                if (ver > 10.0f || ver < 0.0f) {
                    return 4;
                }

                settings->ver = ver;

            } else if (str_contains(line, "Log File")) 
            {
                remove_non_symbols(value);

                if (str_cmp(settings->log_to, "File") 
                || str_cmp(settings->log_to, "Both")) 
                {
                    settings->log_path = value;

                } else 
                {
                    settings->log_path = "N/A";
                }

            } else if (str_contains(line, "CPU Scheduling Code")) 
            {
                remove_non_symbols(value);

                if (str_cmp(value, "NONE")) 
                {
                    settings->cpu_sched = "FCFS-N";

                } else if (!check_cpu_sched(value)) 
                {
                    return 5;

                 } else 
                 {
                    settings->cpu_sched = value;
                 }

            } else if (str_contains(line, "Quantum Time")) 
            {
                remove_non_symbols(value);
                int num = a2i(value);

                if (num > 100 || num < 0) {
                    return 6;
                }

                settings->quantum_time = num;

            } else if (str_contains(line, "Memory Available")) 
            {
                if (!str_contains(line, "(KB)")) {
                    return 19;
                }

                remove_non_symbols(value);
                int num = a2i(value);

                if (num < 0 || num > 102400) 
                {
                    return 7;
                }

                settings->memory_available = a2i(value);

            } else if (str_contains(line, "Processor Cycle Time")) 
            {
                remove_non_symbols(value);
                int num = a2i(value);

                if (num < 1 || num > 1000) 
                {
                    return 8;
                }

                settings->cpu_cycle_time = num;

            } else if (str_contains(line, "I/O Cycle Time")) 
            {
                remove_non_symbols(value);
                int num = a2i(value);

                if (num < 1 || num > 10000) 
                {
                    return 9;
                }

                settings->io_cycle_time = num;

            } else if (str_contains(line, "Log To")) 
            {
                remove_non_symbols(value);

                if (!check_log_to(value)) 
                {
                    return 10;
                }
                settings->log_to = value;

            } else if (str_contains(line, "File Path:")) 
            {
                remove_non_symbols(value);

                if (str_contains(value, "/")) {
                    return 11;
                }

                settings->mdf_path = value;
            }
        }

        val_iter++;
    }

    return 0;
}

//READS ALL INFORMATION FROM META-DATA FILE
int read_metaDataFile(FILE *mdf, struct simAction *firstAction) 
{
    char line[100];
    int line_length, i, cmd_iter, set_data_result;
    cmd_iter = 0;
    char command[40];
    struct simAction *current = (struct simAction*) malloc(sizeof(struct simAction));

    current = firstAction;

    while (fgets(line, 100, mdf)) 
    {
        if (!str_contains(line, "Start Program Meta-Data") && !str_contains(line, "End Program Meta-Data")) 
        {
            line_length = str_len(line);

            for (i = 0; i < line_length; i++) 
            {
                command[cmd_iter] = line[i];
                cmd_iter++;

                if (line[i] == ';') 
                {
                    struct simAction *next = (struct simAction*) malloc(sizeof(struct simAction));
                    command[cmd_iter] = '\0';
                    cmd_iter = 0;

                    set_data_result = set_action_data(command, current);

                    if (set_data_result > 0) 
                    {
                        return set_data_result;
                    }

                    current->next = next;
                    current = next;
                }
            }
        }
    }
    return 0;
}