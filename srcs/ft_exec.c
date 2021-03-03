/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:39:52 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 04:58:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_free_doubletab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void		ft_exec_cmd(t_envir *envir, t_token *token)
{
	char	**cmd;
	int		ret;

	ret = 0;
	cmd = ft_lst_to_path(token);
	if (cmd == NULL)
		return ;
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		ft_exit_cmd(envir, cmd);
		ft_free_token(envir->start);
		ft_free_doubletab(cmd);
		ret = envir->exit_code;
		ft_free_t_envir(envir);
		exit(ret);
	}
	if (ft_isbuiltin(cmd[0]))
		ft_exec_builtin(envir, cmd);
	else
		ft_exec_nonbuiltin(envir, cmd);
	ft_free_doubletab(cmd);
	envir->block_cmd = 1;
}

void		ft_exec_loop(t_envir *envir, t_token *token, int pid, int temp)
{
	while (token != NULL && g_ctrl_c_called == 0)
	{
		g_in_child = 0;
		envir->pipe_dad = 0;
		ft_dollar_until_next(envir, token);
		if (token->string && token->string[0])
			ft_exec(envir, token);
		ft_reset(envir);
		waitpid(-1, &pid, 0);
		if (WIFEXITED(pid))
			pid = WEXITSTATUS(pid);
		if (envir->pipe_dad == 1)
		{
			envir->exit_code = pid;
		}
		if (envir->child == 1)
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

void		ft_exec_set(t_envir *envir, t_token *token)
{
	int pid;
	int temp;

	temp = 0;
	pid = 0;
	token = ft_token_to_cmd(envir->start);
	if ((envir->start->type == LEFT || envir->start->type == RIGHT ||
	envir->start->type == DOUBLERIGHT))
		token = envir->start->next;
	ft_exec_loop(envir, token, pid, temp);
}

void		ft_exec(t_envir *envir, t_token *token)
{
	int		pid;
	t_token	*previous;
	t_token	*next;

	pid = 0;
	previous = ft_previous_sep(token);
	next = ft_next_sep(token);
	if (envir->block_cmd == 0 && previous && previous->type == RIGHT)
		ft_redir_right(envir, token);
	if (envir->block_cmd == 0 && previous && previous->type == LEFT)
		ft_redir_left(envir, token);
	if (envir->block_cmd == 0 && previous && previous->type == DOUBLERIGHT)
		ft_redir_doubleright(envir, token);
	if (envir->block_cmd == 0 && previous && previous->type == PIPE)
		pid = ft_pipe(envir);
	if (envir->block_cmd == 0 && next && next->type != NEXT && pid != 1)
		ft_exec(envir, next->next);
	if ((previous == NULL || previous->type == NEXT || previous->type == PIPE)
	&& pid != 1 && envir->block_cmd == 0)
		ft_exec_cmd(envir, token);
}
