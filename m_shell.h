/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_shell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:30:21 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:48:36 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_SHELL_H
# define M_SHELL_H

# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h> 
# include <sys/stat.h>
# include "include/parsing.h"

typedef struct cmdl{
	char	**args;
}t_cmdl;

typedef struct node{
	char		*var;
	struct node	*next;
}t_ev;
typedef struct ncd{
	t_ev	**ev_h;
	t_ev	**x_ev_h;
	t_ev	*temp;
	char	*t_oldpwd;
	char	*t_pwd;
	char	**old_pwd;
	int		t;
	int		i;
}t_ncd;
typedef struct nx{
	char	*path;
	char	**paths;
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
}	t_nread;

int				fix_cd(t_ncd *ncd);
void			set_status(t_data *data, t_queue *limiter, char *s, char *res);
void			f_heredoc(t_data *data, t_queue *limiters, char *s, char *res);
void			i_heredoc(int *trigger, int *d, char **res);
void			error_one_cmd(t_nread *nread);
t_env			*fill_env(t_ev *ev);
int				n_fill_env(t_ev *ev);
void			free_t_env(t_env *ev);
char			*ft_get_data(char *str);
char			*ft_get_name(char *str);
void			zero_fill(t_env *t);
void			fdclose(int n, int *fd);
int				what_to_call(int v, t_ev **ev_h, t_ev **x_ev_h, char **args);
int				ft_execp(char **args, t_ev *ev);
int				exec(char **args, t_ev *ev);
void			w_resetsig(int *stat, int id);
char			*exec_h(t_ev *ev, char *com);
int				n2_exec_h(char *com);
int				n_exec_h(t_nx *nx);
int				nn_exec_h(t_nx *nx);
void			handle_errors(char *cmd);
int				echo(char **args);
int				is_an_option(char *str);
int				pwd(void);
int				cd(t_ev **ev_h, t_ev **x_ev_h, char **args);
int				n_cd(t_ncd *ncd, char **args);
int				cd_h(t_ev **ev_h, t_ev **x_ev_h);
int				n_cd_h(t_ncd *ncd);
int				nn_cd_h(t_ncd *ncd);
void			init(char **ev, t_ev **ev_h, t_ev **x_ev_h);
void			n_init(t_ev **temp, t_ev **temp2, t_ev **ev_h, t_ev **x_ev_h);
int				unset(t_ev **ev_h, t_ev **x_ev_h, char **args);
int				unset_h(t_ev **ev_h, char *str);
int				n_unset_h(t_ev **ev_h, char *str, t_ev *temp);
void			xprt_e(t_ev **ev_h, char **args, int *i);
int				xprt_hx(char *arg, t_ev *temp);
void			n_xprt_x(t_ev **x_ev_h, int *i, char **args);
void			xprt_x(t_ev **x_ev_h, char **args, int *i, int *r);
int				xprt(t_ev **ev_h, t_ev **x_ev_h, char **args);
char			**ft_conv(t_ev *ev);
int				ft_exit_status(int status);
int				env(t_ev *ev_h);
int				xprt_he(char *arg, t_ev *temp);
void			pre_exec(int hdoc, t_nread *nread);
void			p_quit(int i);
void			m_cmds(int v, int *id, t_cmd *head, t_nread *nread);
void			ft_close_pipes(int **pipes);
int				what_to_call(int v, t_ev **ev_h, t_ev **x_ev_h, char **args);
void			one_cmd(int v, int s0, int s1, t_nread *nread);
void			read_prompt(t_ev *ev_h, t_nread *nread);
char			**ft_conv(t_ev *ev);
void			freesplit(char **s);
void			free_t_env(t_env *ev);
t_env			*fill_env(t_ev *ev);
void			add_history(const char *line);
t_data			*parse_line(char *s, char **env, t_env *main_env);
size_t			mft_strlen(const char *s);
long long int	ft_atoi(const char *str);
int				myft_strcmp(char *s1, char *s2);
int				ev_cmp(char *s1, char *s2);
char			*mft_strdup(const char *s1);
void			ev_alloc(t_ev *ev, char *var);
int				ft_srch(char *s, char c);
int				v_exp(char *s, int caller);
int				unset_h(t_ev **ev_h, char *str);
char			*x_ev_join(char *s);
char			**ft_split(char const *s, char c);
int				m_parsing(char **av);
char			*myft_strjoin(char const *s1, char const *s2);
int				len(char *s);

#endif
