/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 21:12:56 by user42            #+#    #+#             */
/*   Updated: 2021/02/24 01:56:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
	|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int		ft_char_tono_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_is_whitespace(str[i]))
		i++;
	return (i);
}

int		ft_is_onlynumber(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

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
