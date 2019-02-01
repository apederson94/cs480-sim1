#include <stdio.h>
#include <stdlib.h>
#include "booleans.h"
#include "str_utils.h"
#include "file_utils.h"
#include "data_structures.h"

int main(int argc, char const *argv[]) {

    //VARIABLE DECLARATIONS
    char *file_ext;
    char *file_name = (char*) argv[1];
    struct config_values *settings = (struct config_values*) malloc(sizeof(struct config_values));
    struct sim_action *actions_head = (struct sim_action*) malloc(sizeof(struct sim_action));
    
    //CORRECT NUMBER OF INPUTS CHECK
    if (argc != 2) 
    {
        fprintf(stderr, "ERROR: sim0x takes exactly one argument.\n");
        exit(1);
    }

    //INPUT FORMAT CHECK
    file_ext = get_file_ext(file_name);
    if (!str_cmp(file_ext, ".cnf")) 
    {
        fprintf(stderr, "ERROR: sim0x can only read in .cnf files.\n");
        exit(2);
    }
	
    //OPEN CONFIG FILE AND ENSURES IT DID NOT FAIL
    FILE *config_file = fopen(file_name, "r");
    if (!config_file) 
    {
        fprintf(stderr, "ERROR: sim0x could not open the specified config file.\n");
        exit(3);
    }

	//READ IN CONFIG FILE VALUES
    int cfg_val = read_config_file(config_file, settings);

    //ERROR CHECKING FOR CONFIG FILE READING
    if (cfg_val > 0) 
    {
        if (cfg_val == 4) 
        {
            fprintf(stderr, "ERROR: Version/Phase must be between 0.0 and 10.0.\n");

        } else if (cfg_val == 5) {
            fprintf(stderr, "ERROR: Chosen CPU scheduling time is not supported.\n");

        } else if (cfg_val == 6) {
            fprintf(stderr, "ERROR: Quantum time must be between 0 and 100.\n");

        } else if (cfg_val == 7) {
            fprintf(stderr, "ERROR: Memory available must be between 0 and 100MB.\n");

        } else if (cfg_val == 8) {
            fprintf(stderr, "ERROR: Processor cycle time must be between 1 and 1000.\n");

        } else if (cfg_val == 9) {
            fprintf(stderr, "ERROR: I/O cycle time must be between 1 and 10000.\n");

        } else if (cfg_val == 10) {
            fprintf(stderr, "ERROR: Invalid  \"Log To\" option chosen.\n");

        } else if (cfg_val == 11) {
            fprintf(stderr, "ERROR: Meta data file must be in the same directory as the simulator.");

        } else if (cfg_val == 19) {
            fprintf(stderr, "ERROR: Memory Available must be measured in KB.\n");
        }

        exit(cfg_val);
    }

    fclose(config_file);
	
    //OPENS META-DATA FILE AND ENSURES IT DID NOT FAIL
    FILE* meta_data_file = fopen(settings->mdf_path, "r");
    if (!meta_data_file) 
    {
        printf("ERROR: sim0x could not open the specified meta data file.");
        exit(1);
    }
	
    int mdf_val = read_meta_data_file(meta_data_file, actions_head);
	
    //ERROR CHECKING FOR META-DATA FILE READING
    if (mdf_val > 0) {
        if (mdf_val == 12) 
        {
            fprintf(stderr, "ERROR: The \"S\" & \"A\" command letters can only be used with the \"start\" & \"end\" operation strings.\n");

        } else if (mdf_val == 13) 
        {
            fprintf(stderr, "ERROR: The \"P\" command letter can only be used with the \"run\" operation string.\n");

        } else if (mdf_val == 14) 
        {
            fprintf(stderr, "ERROR: The \"I\" command letter can only be used with the \"hard drive\"  && \"keyboard\" operation strings.\n");

        } else if (mdf_val == 15) 
        {
            fprintf(stderr, "ERROR: The \"O\" command letter can only be used with the \"hard drive\", \"printer\", & \"monitor\" operation strings.\n");

        } else if (mdf_val == 16) 
        {
            fprintf(stderr, "ERROR: The \"M\" command letter can only be used with the \"access\" & \"allocate\" operation strings.\n");

        } else if (mdf_val == 17) 
        {
            fprintf(stderr, "ERROR: all numerical values in the meta-data file must be positive.\n");

        } else if (mdf_val == 18) 
        {
            fprintf(stderr, "ERROR: Meta-Data File contains corrupted data. Please ensure the correctness of the file and then retry.\n");
        }

        exit(mdf_val);
    }
    
    
    //PRINTING RESULTS OF FILE READINGS
    printf("Config File Upload Component\n============================\n\n");
    printf("Config File Display\n===================\n\n");
    print_config_values(settings);
    printf("\n");
    printf("Meta-Data File Upload Component\n===============================\n\n");
    printf("Meta-Data File Display\n======================\n\n");
    print_sim_actions(actions_head);
    
    fclose(meta_data_file);

    //FREEING DATA STRUCTS USED TO STORE READ INFORMATION
    free_actions(actions_head);
    free(settings);

    return 0;
}
