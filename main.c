#include "m_shell.h"

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

void    unset(t_ev **ev_h, char **args)
{
    int i;
    int v;

    i = 0;
    if (args)
    {
        while (args[i])
        {
            v = v_exp(args[i], 1);
            if (v == 1)
                unset_h(ev_h, args[i]);
            i++;
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
    static int n = 0;
    while (temp)
    {
        printf("looped around n=%d and this is temp->var=|%s|\n--->and this is what ev_cmpr returned %d after\
        comparing it to arg=|%s|\n", ++n,temp->var, ev_cmp(temp->var, "09"), "99");
        sleep(5);
        if (ev_cmp(temp->var, arg))
        {
            free(temp->var);
            temp->var = x_ev_join(arg);
            printf("comparing after freeing temp->var=%s\n", temp->var);
            return (0);
        }
        if (!temp->next)
        {
            printf("then yes it went here\n");
            temp->next = malloc(sizeof(t_ev));
            temp->var = x_ev_join(arg);
            printf("but why seg fault temp->var=|%s|\n", temp->var);
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
            printf("went here and this is i now %d\n", *i);
            // sleep(100);
        }
    if (args[(*i)])
    {
        if (v_exp(args[(*i)], 0))
        {
        printf("jhh\n");
            temp = *x_ev_h;
            xprt_hx(args[(*i)], temp);
        }
        (*i)++;
    }
}

void    xprt(t_ev **ev_h, t_ev **x_ev_h, char **args, int i)
{
    static char *OLDPWD[2] = {"OLDPWD",0};

    while (args[i] != NULL)
    {
        // if (ft_srch(args[i], '='))
        // {
            // xprt_e(ev_h, args, &i);
        xprt_x(x_ev_h, args, &i);
        printf("this is i outside %d so this is args[i]=%s\n", i,args[i]);
        if (args[i])
            printf("siiick\n");
        if (args[i])
            printf("siiick\n");
        // }
        // else
        //     xprt_x(x_ev_h, args, &i);
    }
    if (i == 0)
        env (*x_ev_h); //also add the OLDPWD;
    printf("hadi mchat mchat\n\n");
}


void    init(char **ev, t_ev **ev_h, t_ev **x_ev_h)
{
    int     i;
    t_ev    *temp;
    t_ev    *temp2;

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
            ev_alloc(temp2, x_ev_join(ev[i]));
            temp = temp->next;
            temp2 = temp2->next;
            i++;
        }
        temp->next = NULL;
        temp2->next = NULL;
    }
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

int main(int ac, char **av, char **ev)
{
    t_ev    *ev_h;
    t_ev    *x_ev_h;
    char    *args[2] = {"ahahah",0};
    char    *args2[] = {"9udvnav", "to_change=dfbb","audnv======","empty","no_equal_sign", "=", 0};
    char    *args3[] = {"9udvnav","9empty", "=", "empty", 0};

    ev_h = NULL;
    x_ev_h = NULL;
    // printf("env= ---> %s\n", x_ev_join("to_changkbjdvnkmfrehguhmrvklmdfvjiorejfijweojf90u3490i5901i9056i90iu690iu690kjvikrejmve=dfbdfnvvdfnjnvafvfb"));
    // init(ev, &ev_h, &x_ev_h);
    xprt(&ev_h, &x_ev_h, args, 0); //empty export
    xprt(&ev_h, &x_ev_h, args, 0);
    xprt(&ev_h, &x_ev_h, args, 0);
    // xprt(&ev_h, &x_ev_h, args, 0);
    // sleep(500);
    // env(x_ev_h);
    // printf("\n\nunset\n\n");
    // free(ev[1]);
    unset(&ev_h, args);
    // call xprt with args+1;
    // xprt(&ev_h, args2, 0);
    // xprt(&ev_h, args);
    env(ev_h);
}

/*
    validing the identifier
    reassignment of existing variables
    manipulation behavior of bash
*/
