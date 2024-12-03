/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:22:10 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 18:29:12 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_FD	1024

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}	t_gnl;

char	*get_next_line(int fd);
bool	found_new_line(t_gnl *lst);
int		get_line_len(t_gnl *lst);
void	prep_next_iter(char *content);
void	append_list(t_gnl **lst, t_gnl *new, char *s, int fd);
char	*clean_list(t_gnl **lst, char *line, int fd);

#endif
