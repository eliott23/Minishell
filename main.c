#include "m_shell.h"

int erno;

void    env(t_ev *ev_h)
{
    if (ev_h)
    {
        while (ev_h)
        {
            printf("%s\n", ev_h->var);
            ev_h = ev_h->next;
        }
    }
}

int     xprt_he(char *arg, t_ev *temp)
{
    while (temp)
    {
        if (ev_cmp(temp->var, arg) && ft_srch(arg, '='))
        {
            free(temp->var);
            temp->var = ft_strdup(arg);
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

    while (args[(*i)] && !v_exp(args[(*i)], 0))
        (*i)++;
    if (args[(*i)] && !(*ev_h))
        {
            *ev_h = malloc(sizeof(t_ev));
            (*ev_h)->var = ft_strdup(args[(*i)]);
            (*ev_h)->next = NULL;
            (*i)++;
        }
        if (args[(*i)])
        {
            if (v_exp(args[(*i)], 0))
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
void    xprt_x(t_ev **x_ev_h, char **args, int *i)
{
    t_ev    *temp;

    while (args[(*i)] && !v_exp(args[(*i)], 0))
        (*i)++;
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
        (*i)++;
    }
}
void    xprt(t_ev **ev_h, t_ev **x_ev_h, char **args, int i)
{
    int t;

    while (args[i] != NULL)
    {
        if (ft_srch(args[i], '='))
        {
            t = i;
            xprt_e(ev_h, args, &i);
            i = t;
            xprt_x(x_ev_h, args, &i);
        }
        else
            xprt_x(x_ev_h, args, &i);
    }
    if (i == 0)
        env (*x_ev_h);
}


int unset_h(t_ev **ev_h, char *str)
{
    t_ev    *temp;
    t_ev    *temp2;

    temp = *ev_h;
    if (temp)
    {
        if (ev_cmp(temp->var, str))
        {
            *ev_h = (*ev_h)->next;
            free(temp->var);
            free(temp);
            return (0);
        }
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
void    unset(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
    int     i;
    int     v;
    char    *temp;

    i = 0;
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
            i++;
        }
    }
}

void    init(char **ev, t_ev **ev_h, t_ev **x_ev_h)
{
    int     i;
    t_ev    *temp;
    t_ev    *temp2;
    char    *OLDPWD[] = {"OLDPWD", 0};

    if (ev && ev_h)
    {
        i = 1;
        *ev_h = malloc(sizeof(t_ev));
        *x_ev_h = malloc(sizeof(t_ev));
        temp = *ev_h;
        temp2 = *x_ev_h;
        temp->var = ft_strdup(ev[0]);
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
    xprt(ev_h, x_ev_h, OLDPWD, 0);
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
//                                 args[i] = ft_strdup(&(ev_h->var)[j + 1]);
//                                 return (0);
//                             }
//                             j++;
//                         }
//                         args[i] = ft_strdup("");
//                     }
//                     ev_h = ev_h->next;
//                 }
//             }
//             i++;
//         }
//     }
// }
int    cd_h(t_ev **ev_h, t_ev **x_ev_h)
{
    t_ev    *temp;
    char    *t_OLDPWD;
    char    *t_PWD;
    char    **OLD_PWD;
    int     i;

    t_OLDPWD = NULL;
    t_PWD = NULL;
    i = 0;
    temp = *ev_h;
    while (temp)
    {
        if (ev_cmp(temp->var, "HOME"))
        {
            while (temp->var[i])
            {
                if (temp->var[i] == '=')
                {
                    t_OLDPWD = getcwd(t_OLDPWD, 0);
					erno = chdir(&temp->var[i + 1]);
					if (erno)
					{
                        printf("cd : %s: %s\n", &temp->var[i + 1], strerror(errno));
                        free(t_OLDPWD); 
					    return (0);
					}
					OLD_PWD = malloc(sizeof(char *) * 3);
					OLD_PWD[0] = myft_strjoin("OLDPWD=",t_OLDPWD);
                    free(t_OLDPWD);
                    t_PWD = getcwd(t_PWD, 0);
					OLD_PWD[1] = myft_strjoin("PWD=",t_PWD);
                    free(t_PWD);
					OLD_PWD[2] = 0;
					xprt(ev_h, x_ev_h, OLD_PWD, 0);
                    freesplit(OLD_PWD);
					return (0);
				}
                i++;
            }
        } 
        temp = temp->next;
    }
    printf("cd: HOME not set\n");
    return (0);
}
int cd(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
    char    *t_OLDPWD;
    char    *t_PWD;
    char    **OLD_PWD;

    t_OLDPWD = NULL;
    t_PWD = NULL;
    if (args && args[0])
    {
        if (args[1])
        {
           t_OLDPWD = getcwd(t_OLDPWD, 0);
           erno = chdir(args[1]);
           if (erno)
           {
                printf("cd : %s: %s\n", args[1] , strerror(errno));
                free(t_OLDPWD); 
                return (0);
           }
           OLD_PWD = malloc(sizeof(char *) * 3);
           OLD_PWD[0] = myft_strjoin("OLDPWD=",t_OLDPWD);
           free(t_OLDPWD);
           t_PWD = getcwd(t_PWD, 0);
           OLD_PWD[1] = myft_strjoin("PWD=", t_PWD);
           free(t_PWD);
           OLD_PWD[2] = 0;
           xprt(ev_h, x_ev_h, OLD_PWD, 0);
           freesplit(OLD_PWD);
        }
        else
            cd_h(ev_h, x_ev_h);
        
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

char *exec_h(t_ev *ev, char *com)
{
    char    *PATH;
    char    **PATHS;
    int     i;

    i = 0;
    PATHS = NULL;
    while (ev)
    {
        if (ev_cmp(ev->var, "PATH"))
        {
            PATH = ft_strdup(ev->var + 5);
            PATHS = ft_split(PATH, ':');
            free(PATH);
            while (PATHS[i])
            {
                PATH = myft_strjoin(PATHS[i], com);
                if (!access(PATH, F_OK))
                {
                    if (!access(PATH, X_OK))
                    {
                        freesplit(PATHS);
                        return (PATH);
                    }
                    else
                    {
                        printf("%s: %s\n", com, strerror(erno));
                        free(PATH);
                        freesplit(PATHS);
                        return (0);
                    }
                }
                i++;
                free(PATH);
            }
            if (!access(com + 1, F_OK))
            {
                if (access(com + 1, X_OK))
                {
                    printf("%s: %s\n", com + 1, strerror(errno));
                    freesplit(PATHS);
                    return (0);
                }
                else
                {
                    freesplit(PATHS);
                    return (ft_strdup(com + 1));
                }
            }
        }
        ev = ev->next;
    }
    if (PATHS)
        freesplit(PATHS);
    printf("minishell: %s: command not found\n", com + 1);
    return (0);
}
char    **ft_conv(t_ev *ev)
{
    char    **env;
    t_ev    *temp;
    int     i;

    temp = ev;
    while (temp)
    {
        temp = temp->next;
        i++;
    }
    env = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (ev)
    {
        env[i] = ft_strdup(ev->var);
        i++;
        ev = ev->next;
    }
    env[i] = 0;
    return (env);
}
int execp(char **args, t_ev *ev)
{
    char    *path;
    char    *com;

    printf("here is the args[0] %s\n", args[0]);
    com = myft_strjoin("/", args[0]);
    path = exec_h(ev, com);
    free(com);
    execve(path, args, ft_conv(ev));
    return (0);
}
int exec(char **args, t_ev *ev)
{
    char    *path;
    char    *com;
    int     id;
    int     stat;

    com = myft_strjoin("/", args[0]);
    path = exec_h(ev, com);
    free(com);
    if (!path)
        return (0);
    id = fork();
	if (!id)
    {
        execve(path , args, ft_conv(ev)); //check safety of every execve;
        exit(0);        //careful with the exit status;
    }
	waitpid(id, &stat, 0);
    if (path)
        free(path);
    return (0);
}
int what_to_call(int v, t_ev **ev_h, t_ev **x_ev_h, char **args)
{
    if (v == 0)
    xprt(ev_h, x_ev_h, args + 1, 0);
    else if (v == 1)
        unset(ev_h, x_ev_h, args + 1);
    else if (v == 2)
        env(*ev_h); //pottential issue regarding if an unwanted argument was provided;
    else if(v == 3)
        cd(ev_h, x_ev_h, args);
    else if (v == 4)
        pwd();
    else if (v == 5)
        echo(args + 1);
    else if (v == 6)
    {
        printf("exit\n");
        exit (0);
    }
    else if (v == 7)
        exec(args, *ev_h);
    else
    {
        printf("execp was called\n");
        execp(args, *ev_h);
    }
    return (0);
}
int ft_start(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
    int     v;
    v = m_parsing(args);
    what_to_call(v, ev_h, x_ev_h, args);
    exit(0);
}
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
int mini_hell(char **av, char **ev)
{
    t_ev    *ev_h;
    t_ev    *x_ev_h;
    t_cmdl  *tokens;

    int     v;
    int     i;
    char    *str = NULL;
    char    **args = NULL;
    int     count;
    int     id;
    int     *fd;
    int     *stat;
    ev_h = NULL;
    x_ev_h = NULL;
    init(ev, &ev_h, &x_ev_h);
    // int fd1 = dup(1);
    // int fd0 = dup(0);
    while (1)
    {
        if (str)
            free(str);
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
        if (!ft_srch(str, '|'))
        {
            if (args)
                freesplit(args);
            args = ft_split(str, ' ');
            v = m_parsing(args);
            what_to_call(v, &ev_h, &x_ev_h, args);
        }
        else
        {
            i = 0;
            tokens = v_pars(str, &count);
            fd = malloc(sizeof(int) * (count - 1) * 2);
            while (tokens[i].args)
            {
                id = fork();
                if (!id)
                {
                    // if (i == 1)
                    //    sleep(40);
                    // if (i)
                    // {

                    // }
                    // if (tokens[i + 1].args)
                    // {
                        //
                    // }
                    // fdclose((count - 1) * 2, fd);
                    v = m_parsing(tokens[i].args);
                    if (v == 7)
                        what_to_call(v + 1, &ev_h, &x_ev_h, args);
                }
                i++;
            }
            printf("waiting\n");
            while (waitpid(-1, NULL, WUNTRACED) != -1);
            free(fd);
        }
    }
}

int main(int ac, char **av, char **ev)
{
    mini_hell(av, ev);
}
/*
    validing the identifier
    manipulation behavior of bash
*/