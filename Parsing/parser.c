#include "../Header/minishell.h"

void	print_args(char **args)
{
	int	i;

	i = -1;
	if (!args)
		printf("args : NULL\n");
	else
	{
		printf("args : {");
		while (args[++i])
			printf("%s, ", args[i]);
		printf("%s", args[i]);
		printf("}\n");
	}
}

void	print_parsing_lst(t_cmdl *cmd)
{
	while (cmd)
	{
		printf("-------------------------------\n");
		printf("idx : %d\n", cmd->idx);
		printf("path : %s\n", cmd->path);
		print_args(cmd->args);
		printf("in fd : %d\n", cmd->in_fd);
		printf("out fd : %d\n", cmd->out_fd);
		printf("isbuiltin : %d\n", cmd->builtin);
		printf("-------------------------------\n");
		cmd = cmd->next;
	}
}

t_cmdl	*parser(void)
{
	t_parser	p;

	t_parser_init(&p);
	p.red_line = readline("Minishell $> ");
	if (p.red_line && p.red_line[0])
	{
		add_history(p.red_line);
		if (check_unrequired_by_subject(p.red_line) != 0)
			free(p.red_line);
		else
		{
			parser_short(&p);
			return (p.cmd_line);
		}
	}
	else if (!p.red_line)
		exit(g_shell.status);
	else
		free(p.red_line);
	return (NULL);
}
