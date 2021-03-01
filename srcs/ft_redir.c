/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:54:01 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 02:46:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_redir_doubleright(t_envir *envir, t_token *token)
{
	envir->fdoutput = open(token->string, O_CREAT | O_WRONLY |
	O_APPEND, S_IRWXU);
	if (envir->fdoutput == -1)
	{
		ft_putstr_fd("Cant open file : ", 2);
		ft_putstr_fd(token->string, 2);
		ft_putchar_fd('\n', 2);
		envir->block_cmd = 1;
		envir->exit_code = 1;
	}
	dup2(envir->fdoutput, STDOUT_FILENO);
}

void		ft_redir_right(t_envir *envir, t_token *token)
{
	envir->fdoutput = open(token->string, O_CREAT | O_WRONLY |
	O_TRUNC, S_IRWXU);
	if (envir->fdoutput == -1)
	{
		ft_putstr_fd("Cant open file : ", 2);
		ft_putstr_fd(token->string, 2);
		ft_putchar_fd('\n', 2);
		envir->block_cmd = 1;
		envir->exit_code = 1;
	}
	dup2(envir->fdoutput, STDOUT_FILENO);
}

void		ft_redir_left(t_envir *envir, t_token *token)
{
	envir->fdinput = open(token->string, O_RDONLY, S_IRWXU);
	if (envir->fdinput == -1)
	{
		ft_putstr_fd("Cant open file : ", 2);
		ft_putstr_fd(token->string, 2);
		ft_putchar_fd('\n', 2);
		envir->block_cmd = 1;
		envir->exit_code = 1;
	}
	dup2(envir->fdinput, STDIN_FILENO);
}
