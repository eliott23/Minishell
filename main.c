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
        // printf("comparing arg=|%s| and temp->var = 11 |%s|\n--->res=%d\n", arg, temp->var + 11, ev_cmp(temp->var + 11, arg));
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

    t_PWD = NULL;
    t_OLDPWD = NULL;
    t_OLDPWD = getcwd(t_OLDPWD, 0);
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
					erno = chdir(&temp->var[i + 1]);
					if (erno)
					{
					    // throw the error;
					    return (0);
					}
					OLD_PWD = malloc(sizeof(char *) * 3);
					OLD_PWD[0] = ft_strjoin("OLDPWD=",t_OLDPWD);
					OLD_PWD[1] = ft_strjoin("PWD=",getcwd(t_PWD,0));
					OLD_PWD[2] = 0;
					xprt(ev_h, x_ev_h, OLD_PWD, 0);
					return (0);
				}
                i++;
            }
        } 
        temp = temp->next;
    }
    //else
    // throw home not set error unless it's a ~ character, so we should probably store the HOME var elsewhere;
    return (0);
}
int cd(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
    char    *t_OLDPWD;
    char    *t_PWD;
    char    **OLD_PWD;

    t_PWD = NULL;
    t_OLDPWD = NULL;
    t_OLDPWD = getcwd(t_OLDPWD, 0);
    if (args && args[0])
    {
        if (args[1])
        {
            erno = chdir(args[1]);
           if (erno)
           {
                printf("this is the error code %d\n", erno);
                return (0);
           }
           OLD_PWD = malloc(sizeof(char *) * 3);
           OLD_PWD[0] = ft_strjoin("OLDPWD=",t_OLDPWD);
           OLD_PWD[1] = ft_strjoin("PWD=",getcwd(t_PWD,0));
           OLD_PWD[2] = 0;
           xprt(ev_h, x_ev_h, OLD_PWD, 0);
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
    return (0);
}
int main(int ac, char **av, char **ev)
{
    t_ev    *ev_h;
    t_ev    *x_ev_h;

    int     v;
    char    *str = NULL;
    char    *noarg[] = {0};
    char    **args = NULL;
    ev_h = NULL;
    x_ev_h = NULL;
    init(ev, &ev_h, &x_ev_h);
    while (1)
    {
        if (str)
            free(str);
        str = readline("Minishell>");
        add_history(str);
        if (args)
            freesplit(args);
        args = ft_split(str, ' ');
        v = m_parsing(args);
        if (v == 0)
            xprt(&ev_h, &x_ev_h, args + 1, 0);
        else if (v == 1)
            unset(&ev_h, &x_ev_h, args + 1);
        else if (v == 2)
            env(ev_h);
        else if(v == 3)
            cd(&ev_h, &x_ev_h, args);
        else if (v == 4)
            pwd();
        else
            printf("%s: command not found\n", args[0]);
        // args = ft_split(str, ' ');
    }
    // if (v == 0)
    //     unset (ev_h,);
    // char    *args2[] = {"9udvnav", "to_change=dfbb","audnv======","empty","no_equal_sign", "=", 0};
    // char    *args3[] = {"9udvnav","9empty", "=", "empty", 0};

    // call xprt with args+1;
}

/*
    validing the identifier
    reassignment of existing variables
    manipulation behavior of bash
*/
