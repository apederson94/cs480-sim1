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
    FILE *metaDataFile;
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
    fileExt = get_fileExt(fileName);
    if (!str_cmp(fileExt, ".cnf")) 
    {
        displayError(FILE_TYPE_ERROR);
        return 1;
    }
	
    //OPEN CONFIG FILE AND ENSURES IT DID NOT FAIL
    FILE *config_file = fopen(fileName, "r");
    if (!config_file) 
    {
        displayError(CONFIG_FILE_OPEN_ERROR);
        return 1;
    }

	//READ IN CONFIG FILE VALUES
    cfgVal = read_config_file(config_file, settings);

    //ERROR CHECKING FOR CONFIG FILE READING
    if (cfgVal > 0) 
    {
        displayError(cfgVal);
        return 1;
    }

    fclose(config_file);
	
    //OPENS META-DATA FILE AND ENSURES IT DID NOT FAIL
    metaDataFile = fopen(settings->mdf_path, "r");
    if (!metaDataFile) 
    {
        displayError(MDF_OPEN_ERROR);
        return 1;
    }
	
    mdfVal = read_metaDataFile(metaDataFile, actionsHead);
	
    //ERROR CHECKING FOR META-DATA FILE READING
    if (mdfVal > 0) 
    {
        displayError(mdfVal)
    }
    
    
    //PRINTING RESULTS OF FILE READINGS
    printf("Config File Upload Component\n============================\n\n");
    printf("Config File Display\n===================\n\n");
    print_configValues(settings);
    printf("\n");
    printf("Meta-Data File Upload Component\n===============================\n\n");
    printf("Meta-Data File Display\n======================\n\n");
    print_simActions(actionsHead);
    
    fclose(metaDataFile);

    //FREEING DATA STRUCTS USED TO STORE READ INFORMATION
    free_actions(actionsHead);
    free(settings);

    return 0;
}
