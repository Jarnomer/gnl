# gnl

Read file descriptors with 🇨, one line at the time 📖.

## General

`gnl` aims to read file descriptors line by line and is meant to be integrated eventually into `libft`.

This project is completed using `linked list` where nodes include read content and address to next node.

```c
typedef struct s_gnl
{
  char         *content;
  struct s_gnl *next;
}  t_gnl;
```

`BUFFER_SIZE` defines how many characters are read each time. If not included during runtime, it is set by header.

```c
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
```

Function `clean_list` frees all nodes every time new line is build or everything if `malloc` fails or `EOF` is reached.

```c
char *clean_list(t_gnl **lst, char *line)
{
  t_gnl  *temp;

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
```

In `bonus`, multiple file descriptors must be supported which introduces some minor changes to `gnl` functions.

Project `passes` many of the 42 `testers`, including Franzinette `strict`, although timeout has to be modified.

For other information, please refer the main page.

### Cheers and good luck! 🥳