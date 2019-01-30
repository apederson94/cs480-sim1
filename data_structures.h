#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

//all data structures created by me

//stores all of the config values provided by the configuration file
struct config_values{
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

//stores an action specified in the meta data file as well as the action after it
struct sim_action{
    char command_letter;
    char operation_string[20];
    int assoc_val;
    struct sim_action *next;
};

//frees all memory associated with sim_action linked list
void free_actions(struct sim_action* head) {
    struct sim_action *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

//prints all relevant sim_action info.
//useful for debugging
void print_sim_action(struct sim_action* src) {
    printf("Command: %c, op_str: %s, assoc_val: %d\n", src->command_letter, src->operation_string, src->assoc_val);
}

#endif