#include "m_shell.h"
#include "include/parsing.h"

char    **ft_conv(t_ev *ev)
{
    char    **env;
    t_ev    *temp;
    int     i;

    temp = ev;
    i = 0;
    while (temp)
    {
        temp = temp->next;
        i++;
    }
    env = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (ev)
    {
        env[i] = mft_strdup(ev->var);
        i++;
        ev = ev->next;
    }
    env[i] = 0;
    return (env);
}
int ft_exit_status(int status)
{
    if (WIFEXITED(status))
    {
        e_s = WEXITSTATUS(status);
        return (e_s);
    }
    else if (WIFSIGNALED(status))
    {
        e_s = status + 128;
        return (e_s);
    }
    return (e_s);
}

int env(t_ev *ev_h)
{
    if (ev_h)
    {
        while (ev_h)
        {
            printf("%s\n", ev_h->var);
            ev_h = ev_h->next;
        }
    }
    return (0);
}

int     xprt_he(char *arg, t_ev *temp)
{
    while (temp)
    {
        if (ev_cmp(temp->var, arg) && ft_srch(arg, '='))
        {
            free(temp->var);
            temp->var = mft_strdup(arg);
            return (0);
        }
        if (!temp->next && ft_srch(arg, '='))
        {
            ev_alloc(temp,arg);
            temp->next->next = NULL;
            return (0);
        }
        temp = temp->next;
    }
    return (1);
}
void    xprt_e(t_ev **ev_h, char **args, int *i)
{
    t_ev    *temp;

    while (args[(*i)] && !v_exp(args[(*i)], -1))
        (*i)++;
    if (args[(*i)] && !(*ev_h))
        {
            *ev_h = malloc(sizeof(t_ev));
            (*ev_h)->var = mft_strdup(args[(*i)]);
            (*ev_h)->next = NULL;
            (*i)++;
        }
        if (args[(*i)])
        {
            if (v_exp(args[(*i)], -1))
            {
                temp = *ev_h;
                xprt_he(args[(*i)], temp);
            }
            (*i)++;
        }
}

int     xprt_hx(char *arg, t_ev *temp)
{
    while (temp)
    {
        if (ev_cmp(temp->var + 11, arg))
        {
            if (ft_srch(arg, '='))
            {
                free(temp->var);
                temp->var = x_ev_join(arg);
            }
            return (0);
        }
        if (!temp->next)
        {
            temp->next = malloc(sizeof(t_ev));
            temp->next->var = x_ev_join(arg);
            temp->next->next = NULL;
            return (0);
        }
        temp = temp->next;
    }
    return (1);
}
void    xprt_x(t_ev **x_ev_h, char **args, int *i, int *r)
{
    t_ev    *temp;
    int     t;

    t = *i;
    while (args[(*i)] && !v_exp(args[(*i)], 0))
        (*i)++;
    if (t != (*i))
        *r = 1;
    if (args[(*i)] && !(*x_ev_h))
    {
        *x_ev_h = malloc(sizeof(t_ev));
        (*x_ev_h)->var = x_ev_join(args[(*i)]);
        (*x_ev_h)->next = NULL;
        (*i)++;
    }
    if (args[(*i)])
    {
        if (v_exp(args[(*i)], 0))
        {
            temp = *x_ev_h;
            xprt_hx(args[(*i)], temp);
        }
        else
            *r = 1;
        (*i)++;
    }
}

int xprt(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
    int t;
    int i;
    int r;

    r = 0;
    i = 0;
    while (args[i] != NULL)
    {
        if (ft_srch(args[i], '='))
        {
            t = i;
            xprt_x(x_ev_h, args, &i, &r);
            i = t;
            xprt_e(ev_h, args, &i);
        }
        else
            xprt_x(x_ev_h, args, &i, &r);
    }
    if (i == 0)
        env (*x_ev_h);
    return (r);
}

int n_unset_h(t_ev **ev_h, char *str, t_ev *temp)
{
        if (ev_cmp(temp->var, str))
        {
            *ev_h = (*ev_h)->next;
            free(temp->var);
            free(temp);
            return (0);
        }
        return (1);
}
int unset_h(t_ev **ev_h, char *str)
{
    t_ev    *temp;
    t_ev    *temp2;

    temp = *ev_h;
    if (temp)
    {
        if (!n_unset_h(ev_h, str, temp))
            return (0);
        while (temp->next)
        {
            if (ev_cmp(temp->next->var, str))
            {
                temp2 = temp->next;
                temp->next = temp->next->next;
                free(temp2->var);
                free(temp2);
                return (0);
            }
            temp = temp->next;
        }
    }
    return (0);
}
int unset(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
    int     i;
    int     v;
    char    *temp;
    int     r;

    i = 0;
    r = 0;
    if (args)
    {
        while (args[i])
        {
            v = v_exp(args[i], 1);
            if (v == 1)
            {
                unset_h(ev_h, args[i]);
                temp = x_ev_join(args[i]);
                unset_h(x_ev_h, temp);
                free(temp);
            }
            else
                r = 1;
            i++;
        }
    }
    return (r);
}

void    n_init(t_ev **temp, t_ev **temp2, t_ev **ev_h, t_ev **x_ev_h)
{
    *ev_h = malloc(sizeof(t_ev));
    *x_ev_h = malloc(sizeof(t_ev));
    *temp = *ev_h;
    *temp2 = *x_ev_h;
}
void    init(char **ev, t_ev **ev_h, t_ev **x_ev_h)
{
    int     i;
    t_ev    *temp;
    t_ev    *temp2;
    char    *OLDPWD[] = {"OLDPWD", 0};

    if (ev && ev[0] && ev_h)
    {
        i = 1;
        n_init(&temp, &temp2, ev_h, x_ev_h);
        temp->var = mft_strdup(ev[0]);
        temp2->var = x_ev_join(ev[0]);
        while (ev[i])
        {
            ev_alloc(temp, ev[i]);
            temp2->next = malloc(sizeof(t_ev));
            temp2->next->var = x_ev_join(ev[i]);
            temp = temp->next;
            temp2 = temp2->next;
            i++;
        }
        temp->next = NULL;
        temp2->next = NULL;
    }
    unset(ev_h, x_ev_h, OLDPWD);
    xprt(ev_h, x_ev_h, OLDPWD);
}
void    freesplit(char **s)
{
    int i;

    i = 0;
    if (s)
    {
        while (s[i])
        {
            free(s[i]);
            i++;
        }
        free(s);
    }
}
// int    ft_expand(char **args, t_ev *ev_h)
// {
//     int i;
//     int j;

//     i = 1;
//     j = 0;
//     if (args)
//     {
//         while (args[i])
//         {
//             if (args[i][0] == '$')
//             {
//                 while (ev_h)
//                 {
//                     if (ev_cmp(ev_h->var, &args[i][1]))
//                     {
//                         free(args[i]);
//                         j = 0;
//                         while ((ev_h->var)[j])
//                         {
//                             if ((ev_h->var)[j] == '=')
//                             {
//                                 args[i] = mft_strdup(&(ev_h->var)[j + 1]);
//                                 return (0);
//                             }
//                             j++;
//                         }
//                         args[i] = mft_strdup("");
//                     }
//                     ev_h = ev_h->next;
//                 }
//             }
//             i++;
//         }
//     }
// }
int nn_cd_h(t_ncd *ncd)
{
    if ((ncd->t) == -1)
	{
        printf("cd : %s: %s\n", &(ncd->temp)->var[(ncd->i) + 1], strerror(errno));
        free((ncd->t_OLDPWD));
        return (0);
	}
    return (1);
}

int n_cd_h(t_ncd *ncd)
{
    if (ev_cmp((ncd->temp)->var, "HOME"))
        {
            while ((ncd->temp)->var[ncd->i])
            {
                if ((ncd->temp)->var[ncd->i] == '=')
                {
                    (ncd->t_OLDPWD) = getcwd((ncd->t_OLDPWD), 0);
					(ncd->t) = chdir(&(ncd->temp)->var[(ncd->i) + 1]);
                    if (!nn_cd_h(ncd))
                        return (0);
					(ncd->OLD_PWD) = malloc(sizeof(char *) * 3);
					(ncd->OLD_PWD)[0] = myft_strjoin("OLDPWD=",(ncd->t_OLDPWD));
                    free((ncd->t_OLDPWD));
                    (ncd->t_PWD) = getcwd((ncd->t_PWD), 0);
					(ncd->OLD_PWD)[1] = myft_strjoin("PWD=",(ncd->t_PWD));
                    free((ncd->t_PWD));
					(ncd->OLD_PWD)[2] = 0;
					xprt((ncd->ev_h), (ncd->x_ev_h), (ncd->OLD_PWD));
                    freesplit((ncd->OLD_PWD));
					return (0);
				}
                (ncd->i)++;
            }
        }
        return (1);
}
int    cd_h(t_ev **ev_h, t_ev **x_ev_h)
{
    t_ncd   ncd;

    ncd.t_OLDPWD = NULL;
    ncd.t_PWD = NULL;
    ncd.i = 0;
    ncd.temp = *ev_h;
    ncd.ev_h = ev_h;
    ncd.x_ev_h = x_ev_h;
    while (ncd.temp)
    {
        if (!n_cd_h(&ncd))
            return (0);  
        ncd.temp = ncd.temp->next;
    }
    printf("cd: HOME not set\n");
    return (0);
}

int n_cd(t_ncd *ncd, char   **args)
{
        if (args[1]) 
        {
           (ncd->t_OLDPWD) = getcwd((ncd->t_OLDPWD), 0);
           (ncd->t) = chdir(args[1]);
           if ((ncd->t) == -1)
           {
                printf("cd : %s: %s\n", args[1] , strerror(errno));
                free((ncd->t_OLDPWD)); 
                return (0);
           }
           (ncd->OLD_PWD) = malloc(sizeof(char *) * 3);
           (ncd->OLD_PWD)[0] = myft_strjoin("OLDPWD=",(ncd->t_OLDPWD));
           free((ncd->t_OLDPWD));
           (ncd->t_PWD) = getcwd((ncd->t_PWD), 0);
           (ncd->OLD_PWD)[1] = myft_strjoin("PWD=", (ncd->t_PWD));
           free((ncd->t_PWD));
           (ncd->OLD_PWD)[2] = 0;
           xprt(ncd->ev_h, ncd->x_ev_h, (ncd->OLD_PWD));
           freesplit((ncd->OLD_PWD));
        }
        else
            cd_h(ncd->ev_h, ncd->x_ev_h);
        return (1);
}

int cd(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
    t_ncd   ncd;

    ncd.t_OLDPWD = NULL;
    ncd.t_PWD = NULL;
    ncd.ev_h = ev_h;
    ncd.x_ev_h = x_ev_h;
    if (args && args[0])
    {
        if (!n_cd(&ncd, args))
            return (1);
    }
    return (0);
}
int pwd()
{
    char    *PWD;

    PWD = NULL;
    PWD = getcwd(PWD, 0);
    printf("%s\n", PWD);
    free(PWD);
    return (0);
}
int is_an_option(char *str)
{
    int i;

    if (!str)
        return (0);
    i = 1;
    if (str[0] != '-')
        return (0);
    while (str[i] == 'n')
        i++;
    if (!str[i] && i > 1)
        return (1);
    return (0);
}
int echo(char **args)
{
    int i;
    int n_l;

    i = 0;
    n_l = 1;
    if (args)
    {
        while (args[i] && is_an_option(args[i]))
        {
            n_l = 0;
            i++;
        }
        while (args[i])
        {
            printf("%s", args[i]);
            i++;
            if (args[i])
                printf(" ");    //weirdoooooooo
        }
        if (n_l)
            printf("\n");
    }
    return (0);
}
void    handle_errors(char *cmd)
{
    int fd;

    if (!cmd)
        exit(0);
    fd = open(cmd, O_RDWR);     //careful!!!!;
    if (fd < 0 && ft_srch(cmd, '/'))
    {
        fprintf(stderr, "%s : %s\n", cmd, strerror(errno));
        close(fd);
    }
    else if (ft_srch(cmd, '/'))
        fprintf(stderr, "%s : Command not found\n", cmd); //check
    exit(126);
}
int nn_exec_h(t_nx *nx)
{
            while ((nx->PATHS)[(nx->i)])
            {
                (nx->PATH) = myft_strjoin((nx->PATHS)[(nx->i)], (nx->com));
                if (!access((nx->PATH), F_OK))
                {
                    freesplit((nx->PATHS));
                    if (!access((nx->PATH), X_OK))
                        return (1);
                    else
                    {
                        free((nx->PATH));
                        e_s = 126;
                        return (0);
                    }
                }
                (nx->i)++;
                free((nx->PATH));
            }
            return (-1);
}
int n_exec_h(t_nx *nx)
{
    int i;

    while ((nx->ev) && !ft_srch((nx->com) + 1, '/'))
    {
        if (ev_cmp((nx->ev)->var, "PATH")) 
        {
            (nx->PATH) = mft_strdup((nx->ev)->var + 5);
            (nx->PATHS) = ft_split((nx->PATH), ':');
            free((nx->PATH));
            i = nn_exec_h(nx);
            if (i != -1)
                return (i);
        }
        (nx->ev) = (nx->ev)->next;
    }
    return (-1);
}
int n2_exec_h(char  *com)
{
            if (access(com + 1, F_OK))
            {
                fprintf(stderr, "minishell: %s: no such file or directory\n", com + 1);
                e_s = 127;
                return (0);
            }
            if (access(com + 1, X_OK))
            {
                fprintf(stderr, "%s: %s\n", com + 1, strerror(errno));
                e_s = 126;  //check the exist status of execve in this case;
                return (0);
            }
            return (1);
}
char *exec_h(t_ev *ev, char *com)
{
    t_nx    nx;
    int     r;

    nx.i = 0;
    nx.PATHS = NULL;
    nx.ev = ev;
    nx.com = com;
    r = n_exec_h(&nx);
    if (!r)
        return (0);
    else if (r == 1)
        return (nx.PATH);
    if (nx.PATHS)
        freesplit(nx.PATHS);
    if (ft_srch(com + 1, '/'))
        {
            if (!n2_exec_h(com))
                return (0); 
            else
                return (mft_strdup(com + 1));
        }
    fprintf(stderr, "minishell: %s: command not found\n", com + 1);
    return (0);
}
int exec(char **args, t_ev *ev)
{
    char    *path;
    char    *com;
    int     id;
    int     stat;

    com = myft_strjoin("/", args[0]);
    if (!com)
        return (0);
    path = exec_h(ev, com);
    free(com);
    if (!path)
    {
        // printf("here\n");
        return (127);
    }
    id = fork();
	if (!id)
    {
        execve(path , args, ft_conv(ev)); //check safety of every execve;
        handle_errors(args[0]);
    }
	waitpid(id, &stat, 0);
    if (path)
        free(path);
    return (ft_exit_status(stat));
}
int ft_execp(char **args, t_ev *ev)
{
    char    *path;
    char    *com;

    com = myft_strjoin("/", args[0]);
    if (!com)
        exit(0);
    path = exec_h(ev, com);
    free(com);
    if (!path)
        exit(127);
    execve(path, args, ft_conv(ev));
    handle_errors(args[0]);
    return (0);
}
int what_to_call(int v, t_ev **ev_h, t_ev **x_ev_h, char **args)
{
    if (v == 0)
        return (xprt(ev_h, x_ev_h, args + 1));
    else if (v == 1)
        return (unset(ev_h, x_ev_h, args + 1));
    else if (v == 2)
        return (env(*ev_h)); //pottential issue regarding if an unwanted argument was provided;
    else if(v == 3)
        return (cd(ev_h, x_ev_h, args));
    else if (v == 4)
        return (pwd());
    else if (v == 5)
        return (echo(args + 1));
    else if (v == 6)
    {
        fprintf(stderr, "exit\n");
        if (args && args[1])
            exit ((char)ft_atoi(args[1]));
        exit(0);
    }
    else if (v == 7)
        return (exec(args, *ev_h));
    else
        return (ft_execp(args, *ev_h));
    return(-1);
}
// int ft_start(t_ev **ev_h, t_ev **x_ev_h, char **args)
// {
//     int     v;
//     v = m_parsing(args);
//     what_to_call(v, ev_h, x_ev_h, args);
//     exit(0);
// }
t_cmdl *v_pars(char  *str, int *a)
{
    char    **coml;
    int count = 0;
    int i = 0;

    coml = ft_split(str, '|');
    while (coml[count])
        count++;
    *a = count;
    t_cmdl *cmdl = malloc(sizeof(t_cmdl) * (count + 1));
    while (i < count)
    {
        cmdl[i].args = ft_split(coml[i], ' ');
        i++;
    }
    cmdl[i].args = 0;
    return (cmdl);
}
void    fdclose(int n, int  *fd)
{
    int i;

    i = 0;
    while (i < n)
    {
        close(fd[i]);
        i++;
    }
}
void    ctl_C(int i)
{
    printf("\n");
    exit(0);
}
void    zero_fill(t_env *t)
{
    t->data = 0;
    t->name = 0;
    t->next = 0;
}
char    *ft_get_name(char *str)
{
    int     i;
    int     j;
    char    *r;

    i = 0;
    j = 0;
    if (!str)
        return (0);
    while (str[i] && str[i] != '=')
        i++;
    r = malloc(sizeof(char) * (i + 1));
    while (j < i)
    {
        r[j] = str[j];
        j++;
    }
    r[j] = 0;
    return (r);
}
char    *ft_get_data(char *str)
{
    int     i;
    char    *r;

    r = NULL;
    if (!str)
        return (0);
    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (str[i] == '=')
        r = mft_strdup(&str[i + 1]);
    return (r);
}
void    free_t_env(t_env *ev)
{
    t_env   *t;

    while (ev)
    {
        free(ev->data);
        free(ev->name);
        t = ev;
        ev = ev->next;
        free(t);
    }
}

t_env   *fill_env(t_ev  *ev)
{
    t_ev    *t;
    t_env   *r;
    t_env   *temp;
    int     j;
    int     i;

    i = 0;
    j = 0;
    t = ev;
    while (t)
    {
        t = t->next;
        i++;
    }
    r = malloc(sizeof(t_env));
    zero_fill(r);
    temp = r;
    while (j < i)
    {
        r->data = ft_get_data(ev->var);
        r->name = ft_get_name(ev->var);
        if (j < i - 1)
        {
            r->next = malloc(sizeof(t_env));
            r = r->next;
            ev = ev->next;
        }
        else
            r->next = 0;
        j++;
    }
    return (temp);
}

void    ft_close_pipes(int **pipes)
{
    int i;

    i = 0;
    if (pipes)
    {
        while (pipes[i])
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
            i++;
        }
    }
}

int mini_hell(char **av, char **ev)
{
    t_ev    *ev_h;
    t_ev    *x_ev_h;

    int     v;
    int     id;
    int     i;
    int     j;
    char    *str = NULL;
    int     count;
    int     stat;
    t_data  *pd;
    int     s0 = dup(0);
    int     s1= dup(1);
    int     t_errno;
    t_env   *main_env;
    char    **env;
    t_cmd   *head;

    pd = NULL;
    env = NULL;
    main_env = NULL;
    ev_h = NULL;
    x_ev_h = NULL;
    init(ev, &ev_h, &x_ev_h);
    i = 0;
    while (1)
    {
        if (str)
            free(str);
        if (main_env)
            free_t_env(main_env);
        if (env)
            freesplit(env);
        if (pd)
            destory_data(&pd);
        str = readline("Minishell>");
        if (!str)
            exit(0);
        while (str && !str[0])
        {
            free(str);
            str = readline("Minishell>");
        }
        if (!str)
            exit(0);
        add_history(str);
        main_env = fill_env(ev_h);
        env = ft_conv(ev_h);
        pd = parse_line(str, env, main_env);
        //here_doc;
        if (!pd->is_syntax_valid || pd->err)
        {
            if (pd->err)
                fprintf(stderr, "%s", pd->err);
            else
                fprintf(stderr, "syntax error");
            exit(1);
        }
        if (pd->n_cmds == 1)
        {
            if (!pd->commands->error_file)
            {
                v = m_parsing(pd->commands->main_args);
                if (pd->commands->infile)
                {
                    dup2(pd->commands->read_end, 0);
                    close(pd->commands->read_end);
                }
                if (pd->commands->outfile)
                {
                    dup2(pd->commands->write_end, 1);
                    close(pd->commands->write_end);
                }
                e_s = what_to_call(v, &ev_h, &x_ev_h, pd->commands->main_args);
                dup2(s0, 0);
                dup2(s1, 1);
            }
            else
            {
                fprintf(stderr, "%s : %s errno==%d\n", pd->commands->error_file, strerror(errno), errno);
                e_s = 1;
            }
            fprintf(stderr, "exit status==%d\n", e_s);
        }
        else
        {
            head = pd->commands;
            while (head)
            {
                // if (pd->commands->cmd_id == 2)
                    // sleep(5);
                t_errno = errno;
                id = fork(); // check later;
                if (!id)
                {
                    if (!head->error_file)
                    {
                            signal(SIGINT, SIG_DFL);
                            if (head->cmd_id != 1 || head->infile)
                                dup2(head->read_end, 0);
                            if (head->next || head->outfile)
                                dup2(head->write_end, 1);
                            ft_close_pipes(pd->pipes);
                            v = m_parsing(head->main_args);
                            if (!(head->is_builtin) || head->outfile)
                            {
                                what_to_call(v + 1, &ev_h, &x_ev_h, head->main_args);
                            }
                            else
                                exit(what_to_call(v, &ev_h, &x_ev_h, head->main_args)); // check exit_status;
                    }
                    else
                    {
                        fprintf(stderr, "%s : %s errno==%d\n", head->error_file, strerror(t_errno), t_errno);
                        exit(1);
                    }
                } 
                head = head->next;
                //check the leak;
            }
            ft_close_pipes(pd->pipes);
            waitpid(id, &stat, 0);
            while (waitpid(-1, NULL, 0) != -1);
            fprintf(stderr, "exit status==%d\n", ft_exit_status(stat));
        }
    }
}
void    parent_ctlC(int i)
{
}
int main(int ac, char **av, char **ev)
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, parent_ctlC);
    e_s = 0;
    // t_ev    *ev_h;
    // t_ev    *x_ev_h;
    // t_data  *pd;
    // t_env   *main_ev;
    // int     i;
    // errno = 0;
    // e_s = 0;
    // ev_h = NULL;
    // x_ev_h = NULL;
    // init(ev, &ev_h, &x_ev_h);
    // main_ev = fill_env(ev_h);
    // pd = parse_line("<<lim", ev, main_ev);
    // // check for syntax errors;
    // // check for error_file
    // //run_heredoc
    // printf("n_cmds %d\n", pd->n_cmds);
    // printf("is_syntax_valid = %d\n", pd->is_syntax_valid);
    // printf("err = %s\n", pd->err);
    // printf("this is the out fd %s and the mode=%d\n", pd->commands->outfile, pd->commands->outfile_mode);
    // t_queue *head = pd->heredoc;
    // while (pd && pd->heredoc)
    // {
    //     printf("|lim= %s  | - ",pd->heredoc->s);
    //     pd->heredoc = pd->heredoc->next;
    // }
    // printf("\n");
    // while (pd->commands)
    // {
    //     i = 0;
    //     while (pd->commands->main_args[i])
    //     {
    //         printf("%d=%s ", pd->commands->cmd_id, pd->commands->main_args[i]);
    //         i++;
    //     }
    //     printf("\nerror_file==%s outfile==%s=%d infile==%s=%d\n", \
    //     pd->commands->error_file, pd->commands->outfile,pd->commands->write_end, pd->commands->infile, pd->commands->read_end);
    //     if (pd->commands->error_file)
    //         printf("%s : %s", pd->commands->error_file, strerror(errno));
    //     pd->commands = pd->commands->next;
    // }
    // i = 0;
    // while (pd->pipes[i])
    // {
    //     printf("pipe%d == %d . ", i, pd->pipes[i][0]);
    //     printf("pipe%d == %d\n", i, pd->pipes[i][1]);
    //     i++;
    // }
    // run_heredoc(pd, head);
    mini_hell(av, ev);
    // free_t_env(main_ev);
}
/*
    validing the identifier
    manipulation behavior of bash
*/