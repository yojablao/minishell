#include "../minishell.h"


int check_option(char **word,int *i)
{
    int     j;
    bool    flage;

    flage = false;
    if(!word[*i])
        return false;
    while(word[++(*i)])
    {
        if(word[*i][0] == '-')
        {
            j = 0;
            while(word[*i][++j])
            {
                if(word[*i][j] == 'n')
                    flage = true;
                else
                {
                    flage = false;
                    break;
                }
            }
        }
        else
            return(flage);
    }
    return (flage);
}
void print_echo(char **input, bool flage,int i)
{
    while (input[i])
    {
        printf("%s", input[i]);        
        if (input[i + 1])
            printf(" ");
        i++;
    }
    if (!flage)
        printf("\n");
}
void echo(char **input)
{
    int i = 0;
    bool option;



    if(!input || !*input)
        return;
    

    option = check_option(input, &i);

    if(!input[i] && option)
        return (exit(0));
    print_echo(input, option,i);
    return (exit(0));
}
