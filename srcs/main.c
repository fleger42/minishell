/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:39:21 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 02:32:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_lst_to_path(t_token *start)
{
	t_token	*token;
	int		count;
	char	**cmd;

	count = 0;
	if (start == NULL)
		return (NULL);
	token = start;
	while (token && (token->type == ARG || token->type == CMD))
	{
		if (token->string && token->string[0])
			count++;
		token = token->next;
	}
	cmd = malloc(sizeof(char*) * (count + 1));
	count = 0;
	token = start;
	while (token && (token->type == ARG || token->type == CMD))
	{
		if (token->string && token->string[0])
			cmd[count++] = ft_strdup(token->string);
		token = token->next;
	}
	cmd[count] = NULL;
	return (cmd);
}

int		ft_pipe(t_envir *envir)
{
	int fd[2];
	int f_pid;

	if (pipe(fd) == -1)
		strerror(errno);
	if ((f_pid = fork()) == -1)
		strerror(errno);
	if (f_pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		envir->child = 1;
		envir->pipeinfd = fd[0];
		in_child = 1;
		return (2);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		envir->pipe_dad = 1;
		envir->pipeoutfd = fd[1];
		return (1);
	}
}

void	ft_reset(t_envir *envir)
{
	if (envir->fdinput != -1)
		close(envir->fdinput);
	if (envir->fdoutput != -1)
		close(envir->fdoutput);
	if (envir->pipeoutfd != -1)
		close(envir->pipeoutfd);
	if (envir->pipeinfd != -1)
		close(envir->pipeinfd);
	envir->fdoutput = -1;
	envir->pipeoutfd = -1;
	envir->pipeinfd = -1;
	envir->block_cmd = 0;
	dup2(envir->standardin, 0);
	dup2(envir->standardout, 1);
}

void	ft_prompt(t_envir *envir )
{
	if (ctrl_c_called == 1)
	{
		envir->exit_code = 130;
		ctrl_c_called = 0;
	}
	else
	{
		if (envir->exit_code == 0)
			write(STDERR_FILENO, BLUE"=> Minishell:"NORMAL, 25);
		else
		{
			write(STDERR_FILENO, RED"=> ", 10);
			write(STDERR_FILENO, BLUE"Minishell:"NORMAL, 22);
		}
	}
}

void	ft_ctrld(t_envir *envir, char *line)
{
	int		exit_value;

	free(line);
	exit_value = envir->exit_code;
	ft_free_t_envir(envir);
	exit(exit_value);
}

void	ft_minishell(t_envir *envir)
{
	char	*line;
	int		ret;

	line = NULL;
	ft_signal_init();
	while (1)
	{
		ft_prompt(envir);
		get_next_line(0, &line);
		ctrl_c_called = 0;
		if (line == NULL)
			ft_ctrld(envir, line);
		if ((ret = ft_check_quote(line)))
		{
			free(line);
			line = ft_strdup("\0");
			if (ret == 1)
				ft_putstr_fd("Syntax error, simple quote not closed\n", 2);
			if (ret == 2)
				ft_putstr_fd("Syntax error, double quote not closed\n", 2);
		}
		line = ft_add_spacesep(line);
		envir->start = ft_tokenize(line);
		if (ft_verif_syntax(envir) == 0)
		{
			ft_move_token(envir);
			in_loop = 1;
			if (envir->start)
				ft_exec_loop(envir, envir->start);
			in_loop = 0;
			free(line);
			ft_free_token(envir->start);
		}
		else
		{
			free(line);
			ft_free_token(envir->start);
		}
	}
}

int		main(int ac, char **av, char **envp)
{
	t_envir *envir;

	envir = ft_malloc_t_envir(envp, av);
	in_loop = 0;
	ft_set_env(envir->envp, envir->prog_name);
	ft_minishell(envir);
	(void)ac;
	return (1);
}
