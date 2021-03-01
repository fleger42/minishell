/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:53:40 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 02:51:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_refresh_type(t_token *start)
{
	t_token *token;

	token = start;
	while (token)
	{
		token->type = ft_get_type_token(token);
		token = token->next;
	}
}

int			ft_get_valid(t_token *token)
{
	t_token *prev;

	if (token == NULL || token->type == CMD || token->type == ARG)
	{
		prev = ft_previous_sep(token);
		if (prev == NULL || prev->type == PIPE || prev->type == NEXT)
			return (0);
		return (1);
	}
	return (1);
}

void		ft_replace_nullstart(t_envir *envir, t_token *token)
{
	token->prev = NULL;
	token->next = envir->start;
	envir->start->prev = token;
	envir->start = token;
}

int			ft_istype(t_token *token, char *str)
{
	if (ft_strchr(str, 'R') && token->type == RIGHT)
		return (1);
	if (ft_strchr(str, 'D') && token->type == DOUBLERIGHT)
		return (1);
	if (ft_strchr(str, 'L') && token->type == LEFT)
		return (1);
	if (ft_strchr(str, 'P') && token->type == PIPE)
		return (1);
	if (ft_strchr(str, 'A') && token->type == ARG)
		return (1);
	if (ft_strchr(str, 'C') && token->type == CMD)
		return (1);
	if (ft_strchr(str, 'N') && token->type == NEXT)
		return (1);
	return (0);
}

void		ft_move_token(t_envir *envir, t_token *dup, t_token *prev,
t_token *temp)
{
	t_token *token;

	token = envir->start;
	while (token)
	{
		prev = ft_previous_sep(token);
		if (token->type == ARG && (prev && (prev->type == RIGHT ||
		prev->type == LEFT || prev->type == DOUBLERIGHT)))
		{
			dup = ft_dup_token(token);
			temp = token->prev;
			ft_remove_token(envir, token);
			token = temp;
			while (ft_get_valid(token))
				token = token->prev;
			if (token)
				ft_insert_after(token, dup);
			else
				ft_replace_nullstart(envir, dup);
			token = envir->start;
		}
		else
			token = token->next;
	}
	ft_refresh_type(envir->start);
}
