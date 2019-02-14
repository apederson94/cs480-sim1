#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

//DATA STRUCTURES AND THEIR RELATED FUNCTIONS

//HOLDS CONFIG FILE INFORMATION
struct configValues
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
struct simAction 
{
    char command_letter;
    char operation_string[20];
    int assoc_val;
    struct simAction *next;
};

//FREES ALL MEMORY ASSOCIATED WITH simActionS
void free_actions(struct simAction* head);

//PRINTS ALL RELEVANT simAction INFORMATION
void print_simAction(struct simAction *src);

//PRINTS ALL ALL RELEVANT simAction INFORMATION FOR ALL simActionS
void print_simActions(struct simAction *head);

//PRINTS ALL INFORMATION FORM A configValues STRUCT
void print_configValues(struct configValues *src);

//TURNS A COMMAND STRING INTO AN ACTION
int set_action_data(char *command, struct simAction *action);

#endif