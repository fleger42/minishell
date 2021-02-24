/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:53:40 by user42            #+#    #+#             */
/*   Updated: 2021/02/24 01:56:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*ft_malloc_string_token(char *line, int i)
{
	int		count;
	int		allow;
	char	*ret;

	allow = 0;
	count = 0;
	while (line[i] != '\0' && (line[i] != ' ' || allow == 1))
	{
		if ((line[i] == '\'' || line[i] == '\"') && allow == 0)
		{
			count++;
			allow = 1;
		}
		else if ((line[i] == '\'' || line[i] == '\"') && allow == 1)
		{
			count++;
			allow = 0;
		}
		else
			count++;
		i++;
	}
	return ((ret = malloc(sizeof(char) * (count + 1))));
}

char		*ft_gst_add(char *line, char *string, int *i)
{
	int		allow;
	int		j;

	j = 0;
	allow = 0;
	while (line[*i] && (line[*i] != ' ' || allow == 1))
	{
		if (((*i > 0 && line[*i - 1] != '\\') &&
		(line[*i] == '\'' || line[*i] == '\"')) && allow == 0)
		{
			string[j++] = line[*i];
			allow = 1;
		}
		else if (((*i > 0 && line[*i - 1] != '\\') &&
		(line[*i] == '\'' || line[*i] == '\"')) && allow == 1)
		{
			string[j++] = line[*i];
			allow = 0;
		}
		else
			string[j++] = line[*i];
		(*i)++;
	}	
	string[j] = '\0';
	return (string);
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
	string = ft_gst_add(line, string, i);
	return (string);
}

t_token		*ft_token_to_cmd(t_token *token)
{
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev->type < NEXT)
			token = token->next;
	}
	return (token);
}

t_token		*ft_next_sep(t_token *token)
{
	while (token && (token->type == CMD || token->type == ARG))
		token = token->next;
	return (token);
}

t_token		*ft_previous_sep(t_token *token)
{
	while (token && (token->type == CMD || token->type == ARG))
		token = token->prev;
	return (token);
}

int			ft_get_type_token(t_token *token)
{
	if (ft_strcmp(token->string, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token->string, ";") == 0)
		return (NEXT);
	if (ft_strcmp(token->string, "<") == 0)
		return (LEFT);
	if (ft_strcmp(token->string, ">>") == 0)
		return (DOUBLERIGHT);
	if (ft_strcmp(token->string, ">") == 0)
		return (RIGHT);
	if (token->prev == NULL ||
	(token->prev->type != ARG && token->prev->type != CMD))
		return (CMD);
	else
		return (ARG);
	return (0);
}

t_token		*ft_get_actual_token(char *line, int *i)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->string = ft_get_string_token(line, i);
	return (token);
}

t_token		*ft_tokenize(char *line)
{
	t_token		*elem2;
	t_token		*elem1;
	int			i;

	i = 0;
	elem2 = NULL;
	elem1 = NULL;
	while (line[i])
	{
		elem1 = ft_get_actual_token(line, &i);
		elem1->prev = elem2;
		if (elem2)
			elem2->next = elem1;
		elem2 = elem1;
		elem2->type = ft_get_type_token(elem2);
		i += ft_char_tono_space(line + i);
	}
	if (elem1)
		elem1->next = NULL;
	if (elem1)
	{
		while (elem1 && elem1->prev)
			elem1 = elem1->prev;
	}
	return (elem1);
}

void		ft_free_token(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token->next;
		free(token->string);
		free(token);
		token = temp;
	}
}

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

void		ft_move_token(t_envir *envir)
{
	t_token *token;
	t_token *dup;
	t_token *prev;
	t_token *temp;

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
