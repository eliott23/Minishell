#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// typedef struct node{
//     char **args;
//     struct node *next;
// }t_list;

typedef struct node{
    char *var;
    struct node *next;
}t_ev;

void    xprt(t_ev **ev_h, char **args)
{
    // call xprt with args+1;
    t_ev    *temp;
    int     i;

    i = 0;
    temp = *ev_h;
    if (!temp)
    {
        *ev_h = malloc(sizeof(t_ev));
        temp = *ev_h;
    }
    while (args[i])
    {
        if (temp->next)
        {
            while (temp->next->next)
                temp = temp->next;
        }
        else
            temp->next = malloc(sizeof(t_ev));
        temp->next->next = NULL;
        temp->next->var = args[i];
        i++;
        temp = temp->next;
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
            temp->next = malloc(sizeof(t_ev));
            temp->next->var = ev[i];
            temp = temp->next;
            i++;
        }
        temp->next = NULL;
    }
}

int ev_cmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (s1 && s2)
    {
        while (s1[i] && s2[i] && s1[i] != '=')
        {
            if (s1[i] != s2[i])
                return (0);
            i++;
        }
        if (s1[i] != '=' || s2[i])
            return (0);
        return (1);
    }
    printf("unexpected behavior\n");
    return (0);
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

    printf("this is env[0] %s\n\n", ev[0]);
    init(ev, &ev_h);
    env(ev_h);
    printf("\n\nunset\n\n");
    unset(&ev_h, "audnv");
    unset(&ev_h, "hh");
    xprt(&ev_h, args);
    unset(&ev_h, "udvnav");
    env(ev_h);
    sleep(50);
}
