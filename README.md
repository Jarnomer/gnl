<h1 align="center">
  <img src="assets/gnl.png" alt="get_next_line" width="400">
</h1>

<p align="center">
	<b><i>Read file descriptors 📖 one line at the time.</i></b><br>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-125%2F100-lightgreen?style=for-the-badge" alt="score">
  <img src="https://img.shields.io/github/languages/top/Jarnomer/gnl?style=for-the-badge&logo=c&label=%20&labelColor=gray&color=lightblue" alt="GitHub top language">
	<img src="https://img.shields.io/github/languages/code-size/Jarnomer/gnl?style=for-the-badge&color=lightyellow" alt="GitHub code size in bytes">
  <img src="https://img.shields.io/github/directory-file-count/Jarnomer/gnl?type=file&extension=c&style=for-the-badge&label=sources&color=pink" alt="GitHub repo file or directory count">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Type-Solo-violet?style=for-the-badge" alt="type">
  <img src="https://img.shields.io/github/last-commit/Jarnomer/gnl/main?style=for-the-badge&color=red" alt="GitHub last commit (branch)">
</p>

<div align="center">

## Table of Contents
[📝 General](#-general)
[🛠️ Build](#️-build)
[⚡ Usage](#-usage)
[🚀 Details](#-details)
[♻️ Resources](#️-resources)

</div>

## 📝 General

Goal of the project is to create a function `get_next_line` to read file descriptors line by line.

Files with `_bonus` suffix support reading `multiple` file descriptors in `parallel`.

Project `passes` many of the 42 `testers`, including [franzinette](https://github.com/xicodomingues/francinette) `strict`, although timeout has to be modified.

Project uses `linked list` where nodes include read content and address to next node.

```c
typedef struct s_gnl
{
  char         *content;
  struct s_gnl *next;
}  t_gnl;
```

`BUFFER_SIZE` defines the amount of characters read. If not included during compilation, it is defined by header.

```c
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
```

## 🛠️ Build

GNU `gcc` is required to compile the project.

```bash
git clone https://github.com/Jarnomer/gnl.git
```

## ⚡ Usage

`gnl` has to be compiled with your `main`. Here is an example that takes a file name.

You can also read from `STDIN_FILENO` and end the input with `Crtl + D`.

```bash
gcc -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
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

## 🚀 Details

`clean_list` frees all `unneeded` nodes every time and moves `head` to `last` node created.

Returns read `line` unless `malloc` fails or `EOF` is reached, then whole list is freed and `NULL` is returned.

Before this `every` node's content is `joined` and last node's content gets shifted by `prep_next_iter`.

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

## ♻️ Resources

[franzinette](https://github.com/xicodomingues/francinette) amazing unit test framework for `gnl` and other 42 projects.

## 4️⃣2️⃣ Footer

For my other 42 projects and general information, please refer the [Hive42](https://github.com/Jarnomer/Hive42) page.

I have also created error handling [unit testers](https://github.com/Jarnomer/42Testers) for `pipex`, `so_long` and `cub3D`.

### Cheers and good luck! 🥳