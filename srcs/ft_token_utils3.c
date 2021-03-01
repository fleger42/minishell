/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 02:50:50 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 02:51:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token		*ft_next_end(t_token *token)
{
	t_token *actual;

	actual = token;
	while (actual)
	{
		if (actual->type == NEXT)
			return (actual);
	}
	return (actual);
}

void		ft_insert_after(t_token *token, t_token *new)
{
	new->prev = token;
	if (token == NULL)
		return ;
	if (token->next == NULL)
		new->next = NULL;
	else
	{
		new->next = token->next;
		token->next->prev = new;
	}
	token->next = new;
}

void		ft_insert_before(t_envir *envir, t_token *token, t_token *new)
{
	new->next = token;
	if (token == NULL)
		return ;
	if (token->prev == NULL)
	{
		new->prev = NULL;
		envir->start = new;
	}
	else
	{
		new->prev = token->prev;
		token->prev->next = new;
	}
	token->prev = new;
}

void		ft_remove_token(t_envir *envir, t_token *to_supp)
{
	if (to_supp == NULL)
		return ;
	if (to_supp->prev == NULL)
		envir->start = to_supp->next;
	else
		to_supp->prev->next = to_supp->next;
	if (to_supp->next != NULL)
		to_supp->next->prev = to_supp->prev;
	free(to_supp->string);
	free(to_supp);
}

t_token		*ft_dup_token(t_token *token)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	new->string = ft_strdup(token->string);
	new->type = token->type;
	return (new);
}
