#include "m_shell.h"

// int     srch_ev(t_ev *temp, char *arg, int i)
// {
//     int v;

//     v = 0;
//     if (temp)
//     {
//         while (temp->next)
//         {
//             if (v)
//             {
//                 free(temp->var);
//                 temp->var = 
//             }
//             temp = temp->next;
//             v = ev_cmp(temp->var, arg);
//         }
//     }
// }

int     xprt_h(t_ev **ev_h, char *arg)
{
    t_ev    *temp;

    if (!(*ev_h))
    {   *ev_h = malloc(sizeof(t_ev));
        (*ev_h)->var = ft_strdup(arg);
        (*ev_h)->next = NULL;
        return (0);
    }
    temp = *ev_h;
    while (temp)
    {
        if (ev_cmp(temp->var, arg))
        {
            free(temp->var);
            temp->var = ft_strdup(arg);
            return (0);
        }
        temp = temp->next;
    }
}

void    xprt(t_ev **ev_h, char **args, int i)
{
    t_ev    *temp;

    temp = *ev_h;
    while (args[i])
    {
        xprt_h(ev_h, args[i]);
        i++;
    }
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



int unset(t_ev **ev_h, char *str)
{
    t_ev    *temp;
    t_ev    *temp2;

    temp = *ev_h;
    if (temp)
    {
        if (ev_cmp(temp->var, str))
        {
            *ev_h = (*ev_h)->next;
            free(temp);
            return (0);
        }
        while (temp->next)
        {
            if (ev_cmp(temp->next->var, str))
            {
                temp2 = temp->next;
                temp->next = temp->next->next;
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
    char    *args[] = {"audnv=23iru", "udvnav=32r8r3", "8231759715", 0};

    ev_h = NULL;
    printf("this is env[0] %s\n\n", ev[0]);
    // init(ev, &ev_h);
    env(ev_h);
    printf("\n\nunset\n\n");
    unset(&ev_h, "audnv");
    unset(&ev_h, "hh");
    xprt(&ev_h, args, 0);
    unset(&ev_h, "udvnav");
    unset(&ev_h, "udvnav");
    // call xprt with args+1;
    // xprt(&ev_h, args, 0);
    // xprt(&ev_h, args);
    env(ev_h);
    sleep(50);
}

/*
    validing the identifier
    reassignment of existing variables
    manipulation behavior of bash
*/
