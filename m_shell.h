#ifndef M_SHELL_H
# define M_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct node{
    char *var;
    struct node *next;
}t_ev;

int	ft_strcmp(char *s1, char *s2);
int	ev_cmp(char *s1, char *s2);
char    *ft_strdup(const char *s1);
void    ev_alloc(t_ev *ev, char *var);

#endif
