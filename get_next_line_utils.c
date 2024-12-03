/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:22:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 18:26:59 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	found_new_line(t_gnl *lst)
{
	int	i;

	if (!lst)
		return (false);
	i = 0;
	while (lst->content[i])
	{
		if (lst->content[i] == '\n')
			return (true);
		++i;
	}
	return (false);
}

int	get_line_len(t_gnl *lst)
{
	int		len;
	int		i;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i] && lst->content[i] != '\n')
			++i;
		len += i;
		if (lst->content[i] == '\n')
			return (++len);
		lst = lst->next;
	}
	return (len);
}

void	prep_next_iter(char *content)
{
	char	*temp;
	int		i;

	if (!content)
		return ;
	temp = content;
	while (*temp != '\n' && *temp)
		++temp;
	if (*temp == '\n')
		++temp;
	i = 0;
	while (temp[i])
	{
		content[i] = temp[i];
		++i;
	}
	content[i] = '\0';
}

void	append_list(t_gnl **lst, t_gnl *new, char *s)
{
	t_gnl	*temp;

	if (!lst || !new || !s)
		return ;
	new->content = s;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

char	*clean_list(t_gnl **lst, char *line)
{
	t_gnl	*temp;

	if (!lst || !*lst)
		return (NULL);
	while ((*lst)->next)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	if (line && *line)
		return (line);
	free((*lst)->content);
	free(*lst);
	free(line);
	*lst = NULL;
	return (NULL);
}
