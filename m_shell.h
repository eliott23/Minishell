#ifndef M_SHELL_H
# define M_SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h> 

typedef struct node{
    char *var;
    struct node *next;
}t_ev;

int		myft_strcmp(char *s1, char *s2);
int		ev_cmp(char *s1, char *s2);
char    *ft_strdup(const char *s1);
void    ev_alloc(t_ev *ev, char *var);
int		ft_srch(char *s, char c);
int		v_exp(char *s, int caller);
int		unset_h(t_ev **ev_h, char *str);
char	*x_ev_join(char *s);
char    **ft_split(char const *s, char c);
int		m_parsing(char **av);
char    *myft_strjoin(char const *s1, char const *s2);

#endif
