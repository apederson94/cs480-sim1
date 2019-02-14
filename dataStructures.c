#include "dataStructures.h"
#include "booleans.h"
#include "errors.h"

//DATA STRUCTURE FUNCTIONS

//FREES ALL MEMORY ASSOCIATED WITH simActionS
void freeActions(struct simAction* head) 
{
    struct simAction *tmp;

    while (head) 
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

//PRINTS ALL RELEVANT simAction INFORMATION
void printSimAction(struct simAction *src) 
{
    printf("Op code letter: %c\n", src->commandLetter);
    printf("Op code name  : %s\n", src->operationString);
    printf("Op code value : %d\n", src->assocVal);
}

//PRINTS ALL ALL RELEVANT simAction INFORMATION FOR ALL simActionS
void printSimActions(struct simAction *head) 
{
    while (head->next) 
    {
        printSimAction(head);
        printf("\n");
        head = head->next;
    }
}

//PRINTS ALL INFORMATION FORM A configValues STRUCT
void printConfigValues(struct configValues *src) 
{
    printf("Version                : %f\n", src->ver);
    printf("Program file name      : %s\n", src->mdfPath);
    printf("CPU schedule selection : %s\n", src->cpuSched);
    printf("Quantum time           : %d\n", src->quantumTime);
    printf("Memory Available       : %d\n", src->memoryAvailable);
    printf("Process cycle rate     : %d\n", src->cpuCycleTime);
    printf("I/O cycle rate         : %d\n", src->ioCycleTime);
    printf("Log to selection       : %s\n", src->logTo);
    printf("Log file name          : %s\n", src->logPath);
}

//TURNS A COMMAND STRING INTO AN ACTION
int setActionData(char *command, struct simAction *action) 
{
    int cmdLength, pos, opFlag, opIter, value;
    char currentChar, opStr[40];

    cmdLength = strLen(command);
    pos = 0;
    value = 0;
    opIter = 0;
    opFlag = FALSE;
    currentChar = command[pos];

    if (!strContains(command, "(") 
    || !strContains(command, ")")
    || !strContains(command, ";")) 
    {
        return CORRUPTED_MDF_ERROR;
    }

    while (pos < cmdLength) 
    {
        if (!(currentChar == ' ') 
        && charIsUpper(currentChar)) 
        {
            action->commandLetter = command[pos];

        } 
        else if (currentChar == '(') 
        {
            opFlag = TRUE;

        } 
        else if (currentChar == ')') 
        {
            opStr[opIter] = '\0';

            if ((!strCmp(opStr, "start") 
            && !strCmp(opStr, "end")
            && (action->commandLetter == 'S' || action->commandLetter == 'A'))) 
            {
                return SA_OP_STRING_ERROR;

            } 
            else if (!strCmp(opStr, "run") && action->commandLetter == 'P') 
            {
                return P_OP_STRING_ERROR;

            } 
            else if (!strCmp(opStr, "hard drive")
            && !strCmp(opStr, "keyboard")
            && action->commandLetter == 'I') 
            {
                return I_OP_STRING_ERROR;
                
            } 
            else if (!strCmp(opStr, "hard drive") 
            && !strCmp(opStr, "printer")
            && !strCmp(opStr, "monitor") 
            && action->commandLetter == 'O') 
            {
                return O_OP_STRING_ERROR;

            } 
            else if (!strCmp(opStr, "allocate") 
            && !strCmp(opStr, "access") 
            && action->commandLetter == 'M') 
            {
                return M_OP_STRING_ERROR;
            }
            strCopy(opStr, action->operationString);
            opFlag = FALSE;
        } 
        else if (opFlag) 
        {
            opStr[opIter] = currentChar;
            opIter++;
        } 
        else if (!opFlag 
        && !(currentChar == ';') 
        && charIsNum(currentChar)) 
        {
            value *= 10;
            value += (currentChar - 48);
        }
        pos++;
        currentChar = command[pos];
    }
    if (value < 0) {
        return NEGATIVE_MDF_VALUE_ERROR;
    }
    action->assocVal = value;
    return 0;
}