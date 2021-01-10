#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void    ft_pipe(char **cmd1, char **cmd2)
{
    int fd[2];
    int f_pid;

    if(pipe(fd) == -1)
        strerror(errno);
    if((f_pid = fork()) == -1)
       strerror(errno);
    if(f_pid == 0) //In child
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execvp(cmd1[0], cmd1);
       
    }
    else //In parent
    {
        if((f_pid = fork()) == -1)
            strerror(errno);
        if(f_pid == 0) //In child
        {
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            execvp(cmd2[0], cmd2);
        }
        else
        {
            close(fd[1]);
            close(fd[0]);
            wait(NULL);
            wait(NULL);
        }
    }
    
}

char	*ft_redirection_left(char *line, char *replace)
{
	char	**stock;
	int		i;
	int		j;
	int		count;
	char *final;

	i = -1;
	while(line[++i])
		if(line[i] == '<')
			count++;
	stock = malloc(sizeof(char*) * count);
	i = -1;
	final = malloc(sizeof(char) *strlen(line));
	while(line[++i])
	{
		if(line[i] != '<')
			final[j++] = line[i];
	}
}

int main(int argc, char *argv[])
{
    int i;

    i = 0;
    /*char *list_cmd[5][4] = {{"echo", "abcdefg", NULL}, {"tr", "a", "1", NULL}, {"tr", "b", "2", NULL}, {"tr", "c", "3", NULL}, {"tr", "a", "1", NULL}};
    while(i < 5)
    {
        printf("TOTEM\n"); 
        ft_pipe(list_cmd[i], list_cmd[i + 1]);
        i++;
    }*/
    char str[] = "Ceci est un test";
    str[0] = (char)(-str[0]);
    printf("%d\n", str[0]);
}  