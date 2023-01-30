FLAGS=-Werror -Wall -Wextra -I /goinfre/aababach/.brew/opt/readline/include\

LIBRARY=-L /goinfre/aababach/.brew/opt/readline/lib -lreadline\

NAME=minishell\

SRC=main.c\
file1.c\
file2.c\
file3.c\
file4.c\
file5.c\
file6.c\
file7.c\
file8.c\
ft_split.c\
m_funct.c\
m_parsing.c\
m_tools.c\
tools.c\
tools_1.c\
parsing/buckets.c\
parsing/cmd.c\
parsing/data_structures/commands.c\
parsing/data_structures/dollars.c\
parsing/data_structures/heredocs.c\
parsing/data_structures/queue.c\
parsing/destroy.c\
parsing/errors.c\
parsing/expressions1.c\
parsing/expressions2.c\
parsing/functions/builtins.c\
parsing/functions/compare.c\
parsing/functions/conditions.c\
parsing/functions/conditions2.c\
parsing/functions/itoa.c\
parsing/functions/join_strings.c\
parsing/functions/quotes.c\
parsing/functions/search.c\
parsing/functions/strings.c\
parsing/help_destroy.c\
parsing/here_doc.c\
parsing/parsing.c\
parsing/prompt.c\
parsing/redirect.c\
parsing/run_heredoc.c\
parsing/variables/expansion.c\
parsing/variables/expansion1.c\
parsing/variables/get_dollars.c\

OBJ=main.o\
file1.o\
file2.o\
file3.o\
file4.o\
file5.o\
file6.o\
file7.o\
file8.o\
ft_split.o\
m_funct.o\
m_parsing.o\
m_tools.o\
tools.o\
tools_1.o\
parsing/buckets.o\
parsing/cmd.o\
parsing/data_structures/commands.o\
parsing/data_structures/dollars.o\
parsing/data_structures/heredocs.o\
parsing/data_structures/queue.o\
parsing/destroy.o\
parsing/errors.o\
parsing/expressions1.o\
parsing/expressions2.o\
parsing/functions/builtins.o\
parsing/functions/compare.o\
parsing/functions/conditions.o\
parsing/functions/conditions2.o\
parsing/functions/itoa.o\
parsing/functions/join_strings.o\
parsing/functions/quotes.o\
parsing/functions/search.o\
parsing/functions/strings.o\
parsing/help_destroy.o\
parsing/here_doc.o\
parsing/parsing.o\
parsing/prompt.o\
parsing/redirect.o\
parsing/run_heredoc.o\
parsing/variables/expansion.o\
parsing/variables/expansion1.o\
parsing/variables/get_dollars.o\

all:$(NAME) 

$(NAME):$(OBJ)
	cc $(FLAGS) $(LIBRARY) -o $@ $^

$(OBJ):$(SRC)
	cc $(FLAGS) -c $^

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re:fclean all
