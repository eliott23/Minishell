#include "m_shell.h"
#include "include/parsing.h"

void    read_prompt(t_ev *ev_h, t_nread *nread)
{
    signal(SIGINT, parent_ctlC);
    if ((nread->str))
        free((nread->str));
    if ((nread->main_env))
        free_t_env((nread->main_env));
    if ((nread->env))
        freesplit((nread->env));
    if ((nread->pd))
        destory_data(&(nread->pd));
    (nread->str) = readline("Minishell>");
    while (!(nread->str) || !(nread->str)[0])
    {
        if (!(nread->str))
            exit(0);
        free((nread->str));
        (nread->str) = readline("Minishell>");
    }
    add_history((nread->str));
    (nread->main_env) = fill_env(ev_h);
    (nread->env) = ft_conv(ev_h);
    (nread->pd) = parse_line((nread->str), (nread->env), (nread->main_env));
    nread->t_errno = errno;
}