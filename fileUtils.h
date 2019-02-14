#ifndef FILE_UTILS
#define FILE_UTILS

//ALL FILE-RELATED UTILITIES

//READS AND STORES ALL VALUES FROM CONFIG FILE
int read_config_file(char *fileName, struct configValues *settings);

//READS ALL INFORMATION FROM META-DATA FILE
int read_metaDataFile(FILE *mdf, struct simAction *firstAction);

#endif
