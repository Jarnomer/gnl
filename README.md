<h1 align="center">
  <b>get_next_line</b>
</h1>

<p align="center">
	<b><i>Read file descriptors 📖 one line at the time.</i></b><br>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-125%2F100-lightgreen?style=for-the-badge" alt="score">
  <img src="https://img.shields.io/github/languages/top/Jarnomer/gnl?style=for-the-badge&logo=c&label=%20&labelColor=gray&color=lightblue" alt="GitHub top language">
	<img src="https://img.shields.io/github/languages/code-size/Jarnomer/gnl?style=for-the-badge&color=lightyellow" alt="GitHub code size in bytes">
  <img src="https://img.shields.io/github/directory-file-count/Jarnomer/gnl/sources?style=for-the-badge&color=pink" alt="GitHub repo file or directory count (in path)">
</p>

<p align="center">
    <img src="https://img.shields.io/badge/Type-Solo-violet?style=for-the-badge" alt="type">
  <img src="https://img.shields.io/github/last-commit/Jarnomer/gnl/main?style=for-the-badge&color=red" alt="GitHub last commit (branch)">
</p>


## 📝 General

Goal of the project is create a function to read file descriptors line by line and it is meant to be integrated into [libft](https://github.com/Jarnomer/libft).

Project uses `linked list` where nodes include read content and address to next node.

```c
typedef struct s_gnl
{
  char         *content;
  struct s_gnl *next;
}  t_gnl;
```

`BUFFER_SIZE` defines how many characters are read each time. If not included during compilation, it is defined by header.

```c
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
```

## 🛠️ Build

GNU `gcc` is required to compile the project.

## ⚡ Usage

`gnl` has to be compiled with your `main`. Here is an example that takes a file name.

```bash
cc -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
```

```bash
./gnl <file_name>
```

```c
#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char **argv) {
  char *line;
  int fd;

  if (argc != 2)
    return 1;
  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    return 1;
  while (1) {
      line = get_next_line(fd);
      if (line == NULL)
          break;
      printf("%s", line);
      free(line);
  }
  close(fd);
  return 0;
}
```

You can also read from `STDIN` and end the input with `Crtl + D`.

```c
#include "get_next_line.h"

int main(void) {
  char *line;

  while (1) {
      line = get_next_line(STDIN_FILENO);
      if (line == NULL)
          break;
      printf("%s", line);
      free(line);
  }
  return 0;
}
```

## 🚀 Functions

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