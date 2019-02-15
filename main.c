#include <stdio.h>
#include <stdlib.h>
#include "booleans.h"
#include "strUtils.h"
#include "fileUtils.h"
#include "dataStructures.h"
#include "errors.h"

int main(int argc, char const *argv[]) {

    //VARIABLE DECLARATIONS
    char *fileExt;
    char *fileName = (char*) argv[1];
    struct configValues *settings = (struct configValues*) malloc(sizeof(struct configValues));
    struct simAction *actionsHead = (struct simAction*) malloc(sizeof(struct simAction));
    int cfgVal, mdfVal;
    
    //CORRECT NUMBER OF INPUTS CHECK
    if (argc != 2) 
    {
        displayError(NUM_ARGS_ERROR);
        return 1;
    }

    //INPUT FORMAT CHECK
    fileExt = getFileExt(fileName);
    if (!strCmp(fileExt, ".cnf")) 
    {
        displayError(FILE_TYPE_ERROR);
        return 1;
    }

    //STARTING FILE UPLOAD PROCESS
    printf("Begin %s upload...\n", fileName);

<<<<<<< HEAD
	//READ IN CONFIG FILE VALUES
    cfgVal = readConfigFile(fileName, settings);

    //ERROR CHECKING FOR CONFIG FILE READING
    if (cfgVal > 0) 
    {
        displayError(cfgVal);
        return 1;
=======
    print_config_values(settings);

    //closing the config file as it is no longer needed;
    fclose(config_file);

    //checks the returned value by read_config_file to ensure that no errors occurred
    if (cfg_val > 0) {
        if (cfg_val == 4) {
            fprintf(stderr, "ERROR: Version/Phase must be between 0.0 and 10.0.\n");
            exit(cfg_val);
        } else if (cfg_val == 5) {
            fprintf(stderr, "ERROR: Chosen CPU scheduling time is not supported.\n");
            exit(cfg_val);
        } else if (cfg_val == 6) {
            fprintf(stderr, "ERROR: Quantum time must be between 0 and 100.\n");
            exit(cfg_val);
        } else if (cfg_val == 7) {
            fprintf(stderr, "ERROR: Memory available must be between 0 and 100MB.\n");
            exit(cfg_val);
        } else if (cfg_val == 8) {
            fprintf(stderr, "ERROR: Processor cycle time must be between 1 and 1000.\n");
            exit(cfg_val);
        } else if (cfg_val == 9) {
            fprintf(stderr, "ERROR: I/O cycle time must be between 1 and 10000.\n");
            exit(cfg_val);
        } else if (cfg_val == 10) {
            fprintf(stderr, "ERROR: Invalid  \"Log To\" option chosen.\n");
            exit(cfg_val);
        } else if (cfg_val == 11) {
            fprintf(stderr, "ERROR: Meta data file must be in the same directory as the simulator.");
            exit(cfg_val);
        }
    }

    //opens the meta data file and checks to make sure it was opened correctly
    FILE* meta_data_file = fopen(settings->mdf_path, "r");
    if (!meta_data_file) {
        printf("ERROR: sim0x could not open the specified meta data file.");
        exit(1);
>>>>>>> master
    }

    //PRINTING SUCCESS MESSAGE
    printf("%s uploaded succesfully!\n", fileName);

<<<<<<< HEAD
    //PRINTING CONFIG FILE VALUES
    printConfigValues(settings, fileName);
    printf("\n");

    //BEGINNING MDF FILE UPLOAD
    printf("Begin %s file upload...\n", settings->mdfPath);
    //printf("Meta-Data File Display\n======================\n\n");

	
    mdfVal = readMetaDataFile(settings->mdfPath, actionsHead);
	
    //ERROR CHECKING FOR META-DATA FILE READING
    if (mdfVal > 0) 
    {
        displayError(mdfVal);
    }
    
    //PRINTING SUCCESS MESSAGE
    printf("%s uploaded succesfully!\n", settings->mdfPath);
    
    //PRINT TO LOGIC
    printSimActions(actionsHead, settings);
=======
    //closing the meta data file as it is no longer needed;
    fclose(meta_data_file);

    //error checking for data read from meta data file
    if (mdf_val == 12) {
        fprintf(stderr, "ERROR: The \"S\" & \"A\" command letters can only be used with the \"start\" & \"end\" operation strings.\n");
        exit(mdf_val);
    } else if (mdf_val == 13) {
        fprintf(stderr, "ERROR: The \"P\" command letter can only be used with the \"run\" operation string.\n");
        exit(mdf_val);
    } else if (mdf_val == 14) {
        fprintf(stderr, "ERROR: The \"I\" command letter can only be used with the \"hard drive\"  && \"keyboard\" operation strings.\n");
        exit(mdf_val);
    } else if (mdf_val == 15) {
        fprintf(stderr, "ERROR: The \"O\" command letter can only be used with the \"hard drive\", \"printer\", & \"monitor\" operation strings.\n");
        exit(mdf_val);
    } else if (mdf_val == 16) {
        fprintf(stderr, "ERROR: The \"M\" command letter can only be used with the \"access\" & \"allocate\" operation strings.\n");
    } else if (mdf_val == 17) {
        fprintf(stderr, "ERROR: all numerical values in the meta-data file must be positive.\n");
        exit(mdf_val);
    } else if (mdf_val == 18) {
        fprintf(stderr, "ERROR: Meta-Data File contains corrupted data. Please ensure the correctness of the file and then retry.\n");
        exit(mdf_val);
    }
    
    printf("Config File Upload Component\n============================\n\n");
    printf("Config File Display\n===================\n\n");

    print_config_values(settings);

    printf("\n");

    printf("Meta-Data File Upload Component\n===============================\n\n");
    printf("Meta-Data File Display\n======================\n\n");

    while (actions_head->next) {
        print_sim_action(actions_head);
        printf("\n");
        actions_head = actions_head->next;
    }
    //freeing linked list acquired from meta-data file
    free_actions(actions_head);
>>>>>>> master

    //FREEING DATA STRUCTS USED TO STORE READ INFORMATION
    freeActions(actionsHead);
    free(settings);

    return 0;
}
