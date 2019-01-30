#include <stdio.h>
#include <stdlib.h>
#include "booleans.h"
#include "str_utils.h"
#include "file_utils.h"
#include "data_structures.h"

int main(int argc, char const *argv[]) {
    char file_ext[5];
    char *file_name = (char*) argv[1];
    struct config_values *settings = (struct config_values*) malloc(sizeof(struct config_values));
    struct sim_action *actions_head = (struct sim_action*) malloc(sizeof(struct sim_action));
    
    //check to make sure there are the correct number of inputs
    if (argc != 2) {
        fprintf(stderr, "ERROR: sim0x takes exactly one argument.\n");
        exit(1);
    }

    //check to make sure the inputs are of the correct format
    get_file_ext(file_name, file_ext);
    if (!str_cmp(file_ext, ".cnf")) {
        fprintf(stderr, "ERROR: sim0x can only read in .cnf files.\n");
        exit(1);
    }

    //opens the config file and checks to make sure it was opened correctly
    FILE *config_file = fopen(file_name, "r");
    if (!config_file) {
        fprintf(stderr, "ERROR: sim0x could not open the specified config file.");
        exit(1);
    }
    int config_value = read_config_file(config_file, settings);

    //checks the returned value by read_config_file to ensure that no errors occurred
    if (config_value > 0) {
        if (config_value == 1) {
            fprintf(stderr, "ERROR: Version/Phase must be between 0.0 and 10.0.\n");
            exit(1);
        } else if (config_value == 2) {
            fprintf(stderr, "ERROR: Chosen CPU scheduling time is not supported.\n");
            exit(1);
        } else if (config_value == 3) {
            fprintf(stderr, "ERROR: Quantum time must be between 0 and 100.\n");
            exit(1);
        } else if (config_value == 4) {
            fprintf(stderr, "ERROR: Memory available must be between 0 and 100MB.\n");
            exit(1);
        } else if (config_value == 5) {
            fprintf(stderr, "ERROR: Processor cycle time must be between 1 and 1000.\n");
            exit(1);
        } else if (config_value == 6) {
            fprintf(stderr, "ERROR: I/O cycle time must be between 1 and 10000.\n");
            exit(1);
        } else if (config_value == 7) {
            fprintf(stderr, "ERROR: Invalid  \"Log To\" option chosen.\n");
            exit(1);
        } else if (config_value == 8) {
            fprintf(stderr, "ERROR: Meta data file must be in the same directory as the simulator.");
            exit(1);
        }
    }

    //closing the config file as it is no longer needed;
    fclose(config_file);

    //opens the meta data file and checks to make sure it was opened correctly
    FILE* meta_data_file = fopen(settings->mdf_path, "r");
    if (!meta_data_file) {
        printf("ERROR: sim0x could not open the specified meta data file.");
        exit(1);
    }

    read_meta_data_file(meta_data_file, &actions_head);
    
    //UNCOMMENT THESE LINES IN ORDER TO PRINT THE ACTIONS
    while (actions_head->next) {
        print_sim_action(actions_head);
        actions_head = actions_head->next;
    }

    //TODO: error checking
    

    //closing the meta data file as it is no longer needed;
    fclose(meta_data_file);

    //freeing linked list acquired from meta-data file
    free_actions(actions_head);

    free(settings);

    //TODO: free linked list of actions
    return 0;
}
