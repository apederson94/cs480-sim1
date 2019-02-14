#include <stdio.h>
#include "strUtils.h"
#include "booleans.h"
#include "dataStructures.h"
#include "errors.h"

//ALL FILE-RELATED UTILITIES

//READS AND STORES ALL VALUES FROM CONFIG FILE
int readConfigFile(char *fileName, struct configValues *settings) 
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
                    return VERSION_PHASE_VALUE_ERROR;
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
                    return UNSUPPORTED_CPU_SCHED_ERROR;

                 } else 
                 {
                    settings->cpu_sched = value;
                 }

            } else if (str_contains(line, "Quantum Time")) 
            {
                remove_non_symbols(value);
                int num = a2i(value);

                if (num > 100 || num < 0) {
                    return QUANTUM_TIME_VALUE_ERROR;
                }

                settings->quantum_time = num;

            } else if (str_contains(line, "Memory Available")) 
            {
                if (!str_contains(line, "(KB)")) {
                    return MDF_MEMORY_UNIT_ERROR;
                }

                remove_non_symbols(value);
                int num = a2i(value);

                if (num < 0 || num > 102400) 
                {
                    return MEMORY_AVAIL_VALUE_ERROR;
                }

                settings->memory_available = a2i(value);

            } else if (str_contains(line, "Processor Cycle Time")) 
            {
                remove_non_symbols(value);
                int num = a2i(value);

                if (num < 1 || num > 1000) 
                {
                    return CPU_CYCLE_TIME_VALUE_ERROR;
                }

                settings->cpu_cycle_time = num;

            } else if (str_contains(line, "I/O Cycle Time")) 
            {
                remove_non_symbols(value);
                int num = a2i(value);

                if (num < 1 || num > 10000) 
                {
                    return IO_CYCLE_TIME_VALUE_ERROR;
                }

                settings->io_cycle_time = num;

            } else if (str_contains(line, "Log To")) 
            {
                remove_non_symbols(value);

                if (!check_log_to(value)) 
                {
                    return INVALID_LOG_TO_ERROR;
                }
                settings->log_to = value;

            } else if (str_contains(line, "File Path:")) 
            {
                remove_non_symbols(value);

                if (str_contains(value, "/")) {
                    return MDF_LOCATION_ERROR;
                }

                settings->mdf_path = value;
            }
        }

        val_iter++;
    }

    fclose(config);

    return 0;
}

//READS ALL INFORMATION FROM META-DATA FILE
int readMetaDataFile(char *fileName, struct simAction *firstAction) 
{
    char line[100];
    int line_length, i, cmd_iter, set_data_result;
    cmd_iter = 0;
    char command[40];
    struct simAction *current = (struct simAction*) malloc(sizeof(struct simAction));
    FILE *mdf = open_memstream(fileName, 'r');

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

    fclose(mdf);

    return 0;
}