#ifndef M_SHELL_H
# define M_SHELL_H

#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h> 
#include <sys/stat.h>
#include "include/parsing.h"

typedef struct cmdl{
	char	**args;
}t_cmdl;

typedef struct node{
    char *var;
    struct node *next;
}t_ev;
typedef struct ncd{
	t_ev	**ev_h;
	t_ev	**x_ev_h;
	t_ev    *temp;
    char    *t_OLDPWD;
    char    *t_PWD;
    char    **OLD_PWD;
    int     t;
    int     i;
}t_ncd;
typedef struct nx{
	char	*PATH;
	char	**PATHS;
	int		i;
	t_ev	*ev;
	char	*com;
}t_nx;

typedef struct nread{
	char	*str;
	t_env	*main_env;
	char	**env;
	t_data	*pd;
	int		t_errno;	
	t_ev	*ev_h;
	t_ev	*x_ev_h;
} t_nread;

void	pre_exec(int hdoc, t_nread *nread);
void    p_quit();
void    m_cmds(int v, int *id, t_cmd *head, t_nread  *nread);
void	ft_close_pipes(int **pipes);
int		what_to_call(int v, t_ev **ev_h, t_ev **x_ev_h, char **args);
void	one_cmd(int v, int s0, int s1, t_nread *nread);
void	read_prompt(t_ev *ev_h, t_nread *nread);
char	**ft_conv(t_ev *ev);
void	freesplit(char **s);
void	free_t_env(t_env *ev);
t_env	*fill_env(t_ev  *ev);
//void	add_history(const char *line);
t_data	*parse_line(char *s, char **env, t_env *main_env);
size_t	mft_strlen(const char *s);
long long int   ft_atoi(const char *str);
int		myft_strcmp(char *s1, char *s2);
int		ev_cmp(char *s1, char *s2);
char    *mft_strdup(const char *s1);
void    ev_alloc(t_ev *ev, char *var);
int		ft_srch(char *s, char c);
int		v_exp(char *s, int caller);
int		unset_h(t_ev **ev_h, char *str);
char	*x_ev_join(char *s);
char    **ft_split(char const *s, char c);
int		m_parsing(char **av);
char    *myft_strjoin(char const *s1, char const *s2);
int		len(char *s);

#endif
