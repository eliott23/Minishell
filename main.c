#include "m_shell.h"

void    unset(t_ev **ev_h, char **args)
{
    int i;
    int v;

    i = 0;
    if (args)
    {
        while (args[i])
        {
            v = v_exp(args[i]);
            if (v == 1)
                unset_h(ev_h, args[i]);
            else
                printf("unset: `%s': not a valid identifier\n",args[i]);
            i++;
        }
    }
}

int     xprt_h(t_ev **ev_h, char *arg, t_ev *temp)
{
    while (temp)
    {
        if (ev_cmp(temp->var, arg) && ft_srch(arg, '='))
        {
            free(temp->var);
            temp->var = ft_strdup(arg);
            return (0);
        }
        if (!temp->next)
        {
            if (ft_srch(arg, '='))
            {
                ev_alloc(temp,arg);
                temp->next->next = NULL;
                return (0);
            }
            // else call the add_to_xprt_ev;
        }
        temp = temp->next;
    }
    return (1);
}

void    xprt(t_ev **ev_h, char **args, int i)
{
    t_ev    *temp;

    while (args[i])
    {
        if (!v_exp(args[i]))
        {
            printf("export: `%s': not a valid identifier\n",args[i]);
            // set the erno to 1;
            i++;
        }
        if (args[i] && !(*ev_h))
        {   *ev_h = malloc(sizeof(t_ev));
            (*ev_h)->var = ft_strdup(args[i]);
            (*ev_h)->next = NULL;
            i++;
        }
        if (args[i])
        {
            if (v_exp(args[i]))
            {   
                temp = *ev_h;
                xprt_h(ev_h, args[i], temp);
            }
            i++;
        }
    }
    // if i == 0;
}

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

void    init(char **ev, t_ev **ev_h)
{
    int     i;
    t_ev    *temp;

    if (ev && ev_h)
    {
        i = 1;
        *ev_h = malloc(sizeof(t_ev));
        temp = *ev_h;
        temp->var = ev[0];
        while (ev[i])
        {
            ev_alloc(temp, ev[i]);
            temp = temp->next;
            i++;
        }
        temp->next = NULL;
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
    char    *args[] = {0};
    char    *args2[] = {"9udvnav", "to_change=dfbb","audnv======","empty","no_equal_sign", "=", 0};
    char    *args3[] = {"9udvnav","9empty", "=", "empty", 0};

    ev_h = NULL;
    printf("this is env[0] %s\n\n", ev[0]);
    // init(ev, &ev_h);
    xprt(&ev_h, args, 0);
    xprt(&ev_h, args2, 0);
    env(ev_h);
    printf("\n\nunset\n\n");
    unset(&ev_h, args3);
    // call xprt with args+1;
    // xprt(&ev_h, args2, 0);
    // xprt(&ev_h, args);
    env(ev_h);
    sleep(500);
}

/*
    validing the identifier
    reassignment of existing variables
    manipulation behavior of bash
*/
