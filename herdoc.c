#include "minishell.h"
int    ft_herdoc(const char *del)
{
    char *line;
    char *fullline;
    char *tmp;
    int fd;

    fullline = NULL;
    fd = open("/tmp/lo.txt",O_CREAT|O_RDWR|O_TRUNC  ,0644);

    while(1)
    {
        // printf("%s",fullline);
        line = readline("heredoc> ");
        if(!line || ft_strncmp(line ,del,ft_strlen(del)) == 0)
            break;
        tmp = line;
        line =  ft_strjoin(line,"\n");

        // free(tmp);
        tmp = fullline;
        fullline =  ft_strjoin(fullline,line);
        free(tmp);
    }
    if (fullline)
    {
        if (write(fd, fullline, ft_strlen(fullline)) == -1)
        {
            perror("Error writing to file");
            free(fullline);
            close(fd);
            return -1;
        }
        free(fullline);
    }
    else
    {
        close(fd);
        return -1;
    }

    close(fd); // Close the file after writing

    // Reopen the heredoc file for reading
    fd = open("/tmp/lo.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error reopening heredoc file for reading");
        return -1;
    }

    return fd; // Return the file descriptor for input redirection

}
// int main(int ac, char **av)
// {

//     char buff[50];
//     char *file;
//     int l;
//     if(ac ==2)
//     {
//         int fd = ft_herdoc(av[1]);
//         l = read(fd,buff,50);
//             printf("%s",buff);
//         while(1)
//         {
//             l = read(fd,buff,50);
//             if(buff[0] == '\0' || l < 1)
//                 break;
//             printf("%s",buff);

//         }


//     }
// }