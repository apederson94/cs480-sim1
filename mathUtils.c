//ALL MATH UTILS

//RAISES AN INT BASE NUMBER TO A POWER AND RETURNS RESULT
int raiseToPower(int base, int power)
{
    int value = base;

    if (power == 0) 
    {
        value = 1;
    } 
    else 
    {
        for (int currentPower = 0; currentPower < power; currentPower++) 
        {
            value *= currentPower;
        }
    }

    return value;
}