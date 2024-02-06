/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:22:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 18:38:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	found_new_line(t_gnl *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = -1;
	while (lst->content[++i])
		if (lst->content[i] == '\n')
			return (1);
	return (0);
}

int	get_line_len(t_gnl *lst)
{
	int		ln;
	int		i;

	if (!lst)
		return (0);
	ln = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i] && lst->content[i] != '\n')
			++i;
		ln += i;
		if (lst->content[i] == '\n')
			return (++ln);
		lst = lst->next;
	}
	return (ln);
}

void	prep_next_iter(char *content)
{
	char	*tmp;
	int		i;

	if (!content)
		return ;
	tmp = content;
	while (*tmp != '\n' && *tmp)
		++tmp;
	if (*tmp == '\n')
		++tmp;
	i = -1;
	while (tmp[++i])
		content[i] = tmp[i];
	content[i] = '\0';
}

void	append_list(t_gnl **lst, t_gnl *new, char *s, int fd)
{
	t_gnl	*tmp;

	if (!lst || !new || !s)
		return ;
	new->content = s;
	new->next = NULL;
	if (!lst[fd])
		lst[fd] = new;
	else
	{
		tmp = lst[fd];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*clean_list(t_gnl **lst, char *line, int fd)
{
	t_gnl	*tmp;

	if (fd < 0 || fd > FD_MAX - 1
		|| !lst || !lst[fd])
		return (NULL);
	while ((lst[fd])->next)
	{
		tmp = lst[fd]->next;
		free(lst[fd]->content);
		free(lst[fd]);
		lst[fd] = tmp;
	}
	if (line && *line)
		return (line);
	free(lst[fd]->content);
	free(lst[fd]);
	free(line);
	lst[fd] = NULL;
	return (NULL);
}
