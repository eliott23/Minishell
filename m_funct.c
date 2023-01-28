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

void    one_cmd(int v, int s0, int s1, t_nread *nread)
{
      if (!(nread->pd)->commands->error_file)
            {
                v = m_parsing((nread->pd)->commands->main_args);
                if ((nread->pd)->commands->infile || (nread->pd)->commands->has_heredoc)
                {
                    dup2((nread->pd)->commands->read_end, 0);
                    close((nread->pd)->commands->read_end);
                }
                if ((nread->pd)->commands->outfile)
                {
                    dup2((nread->pd)->commands->write_end, 1);
                    close((nread->pd)->commands->write_end);
                }
                gv.e_s = what_to_call(v, &(nread->ev_h), &(nread->x_ev_h), (nread->pd)->commands->main_args);
                dup2(s0, 0);
                dup2(s1, 1);
            }
            else
            {
                fprintf(stderr, "%s : %s errno==%d\n", (nread->pd)->commands->error_file, strerror((nread->t_errno)), (nread->t_errno));
                gv.e_s = 1;
            }
            fprintf(stderr, "exit status==%d\n", gv.e_s);
}