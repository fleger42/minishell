/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 11:49:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/30 17:02:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_upgrade_shlv(char **envp)
{
	int i;

	i = 0;
	while(envp[i] != NULL)
	{
		if(envp[i][0] == 'S' && envp[i][1] == 'H' && envp[i][2] == 'L' && envp[i][3] == 'V' && envp[i][4] == 'L')
		{
			envp[i] = ft_catpy("SHLVL=", ft_itoa(ft_atoi(envp[i] + 6) + 1));
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_extract_builtin(char *str)
{
	int i;
	char *cmd;

	i = 0;
	if(str == NULL || str[0] == '\0')
		return (NULL);
	str = char_walk(str);
	while(str[i] && str[i] != ' ')
		i++;
	cmd = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while(str[i] && str[i] != ' ')
	{
		cmd[i] = str[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
	
}

int		ft_is_builtin(char *str)
{
	char *arg[] = {"pwd", "unset", "cd", "echo", "export", "env", NULL};
    int i;

	i = 0;
	while(arg[i] != NULL)
	{
		if (strcmp(arg[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_path(t_envir *envir, char *cmd)
{
	int i;
	char **all_bin;
	char *path;
	i = -1;

	path = NULL;	
	all_bin = ft_split(ft_get(envir->envp, "PATH"), ":");
	while(all_bin[++i] != NULL && path == NULL)
	{
		path = ft_search_dir(all_bin[i], cmd);
	}
	i = -1;
	while(all_bin[++i])
		free(all_bin[i]);
	free(all_bin);
	return (path);
}

char *ft_walk_until_equal(char *str, int *length)
{
	int i;

	i = 0;
	if(str[0] == '\0' || str == NULL)
		return (NULL);
	while(str[i] && str[i] != '=')
		i++;
	*length = i;
	return (str + i + 1);
}

int		ft_isalpha_min(char c)
{
	if(c >= 97 && c <= 122)
		return (1);
	return (0);
}

int		ft_isalpha_maj(char c)
{
	if(c >= 65 && c <= 90)
		return (1);
	return (0);
}

int	ft_verif_dollar(char *str1, char *str2)
{
	int i;

	i = 0;
	while(str1[i] != '=')
	{
		if(str1[i] != str2[i])
		{
			return (0);
		}
		i++;
	}
	if(!(ft_isdigit(str2[i]) || ft_isalpha_maj(str2[i]) || ft_isalpha_min(str2[i]) || str2[i] == '_'))
		return (1);
	return (0);
}


char	*ft_replace_dollar(t_envir *envir, char *str, int *length)
{
	int i;

	i = 0;
	while(envir->envp[i] != NULL)
	{
		if(ft_verif_dollar(envir->envp[i], str) == 1)
			return(ft_strdup(ft_walk_until_equal(envir->envp[i], length)));
		i++;
	}
	i = 0;
	if(str[i] == '?')
	{
		*length = 1;
		return(ft_itoa(envir->exit_code));
	}
	if(str[i] == ' ')
	{
		*length = -1;
		return(NULL);
	}
	if(ft_isdigit(str[i]))
	{
		*length = 1;
		return(NULL);
	}
	while(ft_isdigit(str[i]) || ft_isalpha_maj(str[i]) || ft_isalpha_min(str[i]) || str[i] == '_')
		i++;
	*length = i;
	return (NULL);	
}

char	*ft_dollar(t_envir *envir, char *str)
{
	int		i;
	char	*temp;
	char	*start;
	char	*temp2;
	int		j;
	int		length;
	i = 0;
	temp2 = NULL;
	temp = NULL;
	start = NULL;
	while(str[i])
	{
		if(str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ')
		{
			start = malloc(sizeof(char) * (i + 1));
			j = -1;
			while(++j<i)
				start[j] = str[j];
			start[j] = '\0';
			temp = ft_replace_dollar(envir, str + 1 + i, &length);
			if(temp != NULL)
			{
				temp2 = temp;
				temp = ft_catpy(start, temp2);
				free(temp2);
			}
			else
				temp = ft_strdup(start);
			free(start);
			start = ft_strdup(str + i + length + 1);
			free(str);
			str = ft_catpy(temp, start);
			if(temp != NULL)
				free(temp);
			free(start);
			i = -1;
		}
		i++;
	}
	return (str);
}

/*char	*ft_redirection_left(char *line, char *replace)
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
	final = malloc(sizeof(char) * ft_strlen(line));
	while(line[++i])
	{
		if(line[i] != '<')
			final[j++] = line[i];
	}
}*/
void		ft_print_list(t_token *list)
{
	while(list != NULL)
	{
		printf(GREEN"[%s] with type {%d}\n"NORMAL, list->string, list->type);
		list = list->next;
	}
}

int			ft_is_whitespace(char c)
{
	if(c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'  || c == '\f')
		return (1);
	return (0);
}

int			ft_char_tono_space(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0' && ft_is_whitespace(str[i]))
	{
		//printf("Boucle to space on char [%c] at length [%d]\n", str[i], i);
		i++;
	}
	return(i);
}

char		*ft_malloc_string_token(char *line, int i)
{
	int count;
	int	allow;
	char *ret;

	allow = 0;
	count = 0;
	//printf("Malloc string\n");
	//printf("Starting on char %c\n", line[i]);
	while(line[i] != '\0' && (line[i] != ' ' || allow == 1))
	{
		//printf("On char [%c]\n", line[i]);
		if((line[i] == '\'' || line[i] == '\"') && allow == 0)
			allow = 1;
		else if((line[i] == '\'' || line[i] == '\"') && allow == 1)
			allow = 0;
		else
			count++;
		i++;
	}
	//printf("End malloc string\n");
	return((ret = malloc(sizeof(char) * (count + 1))));
}

char		*ft_get_string_token(char *line, int *i)
{
	char	*string;
	int		allow;
	int		j;
	
	j = 0;
	allow = 0;
	*i += ft_char_tono_space(line + *i);
	string = ft_malloc_string_token(line, *i);
	//printf("Fill string\n");
	//printf("Starting on char %c\n", line[*i]);
	while(line[*i] && (line[*i] != ' ' || allow == 1))
	{
		//printf("On char [%c]\n", line[*i]);
		if((line[*i] == '\'' || line[*i] == '\"') && allow == 0)
			allow = 1;
		else if((line[*i] == '\'' || line[*i] == '\"') && allow == 1)
			allow = 0;
		else
			string[j++] = line[*i];
		(*i)++;
	}
	string[j] = '\0';
	//printf("End fill string\n");
	return (string);

}

void		ft_redir_doubleright(t_envir *envir, t_token *token)
{
	envir->fdoutput = open(token->string, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if(envir->fdoutput == -1)
	{
		ft_error("Cant open file");
	}
	dup2(envir->fdoutput, STDOUT_FILENO);
}
void		ft_redir_right(t_envir *envir, t_token *token)
{
	envir->fdoutput = open(token->string, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if(envir->fdoutput == -1)
		ft_error("Cant open file");
	dup2(envir->fdoutput, STDOUT_FILENO);
}

void		ft_redir_left(t_envir *envir, t_token *token)
{
	envir->fdinput = open(token->string, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if(envir->fdinput == -1)
		ft_error("Cant open file");
	dup2(envir->fdinput, STDIN_FILENO);
}

char		**ft_lst_to_path(t_token *start)
{
	t_token *token;
	int	count;
	char **cmd;

	count = 0;
	token = start;
	while(token && (token->type == ARG || token->type == CMD))
	{
		//printf("cmd to args = [%s]\n", token->string);
		token = token->next;
		count++;
	}
	//printf("counted [%d] dimension\n", count);
	cmd = malloc(sizeof(char*) * (count + 1));
	count = 0;
	token = start;
	while(token && (token->type == ARG || token->type == CMD))
	{
		//printf("cmd to args = [%s]\n", token->string);
		cmd[count++] = ft_strdup(token->string);
		token = token->next;
	}
	cmd[count] = NULL;
	return (cmd);
}

int			ft_isbuiltin(char *str)
{
	if(ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "env") == 0 || ft_strcmp(str, "export") == 0 
	|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "pwd") == 0) 
		return (1);
	return(0);
}

void		ft_exec_cmd(t_envir *envir, t_token *token)
{
	char	**cmd;
	int i;

	i = 0;
	cmd = ft_lst_to_path(token);
	if(ft_strcmp(cmd[0], "exit") == 0)
	{
		ft_free_token(envir->start);
		ft_free_t_envir(envir);
		while(cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		exit(envir->exit_code);
	}
	if(ft_isbuiltin(cmd[0]))
		ft_exec_builtin(envir, cmd);
	else
		ft_exec_nonbuiltin(envir, cmd);
	i = -1;
	while(cmd[++i])
		free(cmd[i]);
	free(cmd);
	envir->block_cmd = 1;
	(void)envir;
}

int		ft_pipe(t_envir *envir)
{
    int fd[2];
    int f_pid;

    if(pipe(fd) == -1)
        strerror(errno);
    if((f_pid = fork()) == -1)
       strerror(errno);
    if(f_pid == 0) //In child
    {
		close(fd[1]);
        dup2(fd[0], 0);
		envir->child = 1;
		envir->pipeinfd = fd[0];
		in_child = 1;
        return (2);
    }
    else //In parent
    {
        close(fd[0]);
        dup2(fd[1], 1);
		envir->pipe_dad = 1; 
		envir->pipeoutfd = fd[1];
        return (1);
    }
}

t_token		*ft_token_to_cmd(t_token *token)
{
	while(token && token->type != CMD)
	{
		token = token->next;
		if(token && token->type == CMD && token->prev->type != NEXT)
			token = token->next;
	}
	return(token);
}

void		ft_reset(t_envir *envir)
{
	if(envir->fdinput != -1)
		close(envir->fdinput);
	if(envir->fdoutput != -1)
		close(envir->fdoutput);
	if(envir->pipeoutfd != -1)
		close(envir->pipeoutfd);
	if(envir->pipeinfd != -1)
		close(envir->pipeinfd);
	envir->fdoutput = -1;
	envir->pipeoutfd = -1;
	envir->pipeinfd = -1;
	envir->block_cmd = 0;
	dup2(envir->standardin, 0);
	dup2(envir->standardout, 1);
}
void		ft_exec_loop(t_envir *envir, t_token *token)
{
	int pid;
	int temp;

	token = ft_token_to_cmd(token);
	temp = 0;
	pid = 0;
	while(token != NULL && ctrl_c_called == 0)
	{
		in_child = 0;
		envir->pipe_dad = 0;
		ft_exec(envir, token);
		ft_reset(envir);
		waitpid(-1, &pid, 0);
		if(WIFEXITED(pid))
			pid = WEXITSTATUS(pid);
		if(envir->pipe_dad == 1)
		{
			envir->exit_code = pid;
		}
		if(envir->child == 1)
		{
			ft_free_token(envir->start);
			temp = envir->exit_code;
			ft_free_t_envir(envir);
			exit(temp);
		}
		envir->child = 0;
		token = ft_token_to_cmd(token->next);
	}
}

t_token *ft_next_sep(t_token *token)
{
	while(token && (token->type == CMD || token->type == ARG))
	{
		token = token->next;
	}
	return(token);
}

t_token *ft_previous_sep(t_token *token)
{
	while(token && (token->type == CMD || token->type == ARG))
	{
		token = token->prev;
	}
	return(token);
}

void	ft_exec(t_envir *envir, t_token *token)
{
	int pid;

	pid = 0;
	t_token *previous;
	t_token *next;
	previous = ft_previous_sep(token);
	next = ft_next_sep(token);

	if(previous && previous->type == RIGHT)
		ft_redir_right(envir, token);
	if(previous && previous->type == LEFT)
		ft_redir_left(envir, token);
	if(previous && previous->type == DOUBLERIGHT)
		ft_redir_doubleright(envir, token);
	if(previous && previous->type == PIPE)
		pid = ft_pipe(envir);
	if(next && next->type != NEXT && pid != 1)
		ft_exec(envir, next->next);
	if((previous == NULL || previous->type == NEXT || previous->type == PIPE) && pid != 1 && envir->block_cmd == 0)
		ft_exec_cmd(envir, token);
}	

int			ft_get_type_token(t_token *token)
{
	if(ft_strcmp(token->string, "|") == 0)
		return (PIPE);
	if(ft_strcmp(token->string, ";") == 0)
		return (NEXT);
	if(ft_strcmp(token->string, "<") == 0)
		return (LEFT);
	if(ft_strcmp(token->string, ">>") == 0)
		return (DOUBLERIGHT);
	if(ft_strcmp(token->string, ">") == 0)
		return (RIGHT);
	if(token->prev == NULL || token->prev->type == RIGHT || token->prev->type == PIPE || token->prev->type == NEXT)
		return (CMD);
	else
		return (ARG);
	return(0);
}

t_token		*ft_get_actual_token(char *line, int *i)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	//printf("Get token string\n");
	token->string = ft_get_string_token(line, i);
	//printf("Tocken string acquired\n");
	return (token);
}

t_token		*ft_tokenize(char *line)
{
	t_token *elem2;
	t_token *elem1;
	int i;

	i = 0;
	elem2 = NULL;
	elem1 = NULL;
	while(line[i])
	{
		//printf("Get token\n");
		elem1 = ft_get_actual_token(line, &i);
		//printf("Tocken acquired\n"); 
		elem1->prev = elem2;
		if(elem2)
			elem2->next = elem1;
		elem2 = elem1;
		//printf("Get token type\n");
		elem2->type = ft_get_type_token(elem2);
		//printf("Tocken type acquired\n");
		i += ft_char_tono_space(line + i);
	}
	//printf("Reversing list in good order\n");
	if(elem1)
		elem1->next = NULL;
	if(elem1)
	while(elem1 && elem1->prev)
	{
		//printf("Reversing: On token %s\n", elem1->string);
		elem1 = elem1->prev;
	}
	//printf("Printing the created list:\n");
	//ft_print_list(elem1);
	return (elem1);
}

void	ft_free_token(t_token *token)
{
	t_token *temp;
	while(token)
	{
		temp = token->next;
		free(token->string);
		free(token);
		token = temp;
	}
}

int		ft_issep(char c)
{
	if(c == ';' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);

}

char	*ft_malloc_new_line(char *line)
{
	int i;
	int count;
	char *new_line;

	i = 0;
	count = 0;
	while(line[i])
	{
		if((i > 0 && ft_issep(line[i]) && line[i - 1] != ' ') || (i > 0 && ft_issep(line[i - 1]) && line[i] != ' '))
		{
			count++;
		}
		count++;
		i++;
	}
	new_line = malloc(sizeof(char) * (count + 1));
	return (new_line);
}

char	*ft_add_spacesep(char *line)
{
	int i;
	int j;
	char *new_line;
	i = 0;
	j = 0;
	new_line = ft_malloc_new_line(line);
	while(line[i])
	{
		if((i > 0 && ft_issep(line[i]) && line[i - 1] != ' ') || (i > 0 && ft_issep(line[i - 1]) && line[i] != ' '))
		{
			new_line[j++] = ' ';
		}
		new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

void	ft_prompt(t_envir *envir)
{
	char    *line;

	line = NULL;
	ft_signal_init();
	while(1)
	{
		if(ctrl_c_called == 1)
		{
			envir->exit_code = 130;
			ctrl_c_called = 0;
		}
		else
		{
			if(envir->exit_code == 0)
				write(STDERR_FILENO, BLUE"=> Minishell:"NORMAL, 25);
			else
			{
				write(STDERR_FILENO, RED"=> ", 10);
				write(STDERR_FILENO, BLUE"Minishell:"NORMAL, 22);
			}
		}
		//int fd = open("valgrind_cmd.txt", O_RDONLY);
		get_next_line(0, &line);
		ctrl_c_called = 0;
		if(line == NULL)
		{
			free(line);
			ft_free_t_envir(envir);
			exit(envir->exit_code);
		}
		line = ft_dollar(envir, line);
		line = ft_add_spacesep(line);
		envir->start = ft_tokenize(line);
		free(line);
		in_loop = 1;
		ft_exec_loop(envir, envir->start);
		in_loop = 0;
		ft_free_token(envir->start);
	}
}

int main(int ac, char **av, char **envp)
{
	t_envir *envir;
	envir = ft_malloc_t_envir(envp, av);
	in_loop = 0;
	ft_set_env(envir->envp, envir->prog_name);
	ft_prompt(envir);
	(void)ac;
	return (1);
}
