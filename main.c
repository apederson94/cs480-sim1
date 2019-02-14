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
    FILE *metaDataFile, *configFile;
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
	
    //OPEN CONFIG FILE AND ENSURES IT DID NOT FAIL
    configFile = fopen(fileName, "r");
    if (!configFile) 
    {
        displayError(CONFIG_FILE_OPEN_ERROR);
        return 1;
    }

	//READ IN CONFIG FILE VALUES
    cfgVal = readConfigFile(configFile, settings);

    //ERROR CHECKING FOR CONFIG FILE READING
    if (cfgVal > 0) 
    {
        displayError(cfgVal);
        return 1;
    }

    fclose(configFile);
	
    //OPENS META-DATA FILE AND ENSURES IT DID NOT FAIL
    metaDataFile = fopen(settings->mdfPath, "r");
    if (!metaDataFile) 
    {
        displayError(MDF_OPEN_ERROR);
        return 1;
    }
	
    mdfVal = readMetaDataFile(metaDataFile, actionsHead);
	
    //ERROR CHECKING FOR META-DATA FILE READING
    if (mdfVal > 0) 
    {
        displayError(mdfVal)
    }
    
    
    //PRINTING RESULTS OF FILE READINGS
    printf("Config File Upload Component\n============================\n\n");
    printf("Config File Display\n===================\n\n");
    printConfigValues(settings);
    printf("\n");
    printf("Meta-Data File Upload Component\n===============================\n\n");
    printf("Meta-Data File Display\n======================\n\n");
    printSimActions(actionsHead);
    
    fclose(metaDataFile);

    //FREEING DATA STRUCTS USED TO STORE READ INFORMATION
    freeActions(actionsHead);
    free(settings);

    return 0;
}
