FLAGS=-Werror -Wall -Wextra -I /goinfre/aababach/.brew/opt/readline/include\

LIBRARY=-L /goinfre/aababach/.brew/opt/readline/lib -lreadline\

NAME=minishell\

SRC=main.c\
errors.c\
file1.c\
file2.c\
file3.c\
file4.c\
file5.c\
file6.c\
file7.c\
file8.c\
file9.c\
ft_split.c\
m_funct.c\
m_parsing.c\
m_tools.c\
tools.c\
tools_1.c\
m_tools2.c\
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
file9.o\
ft_split.o\
m_funct.o\
m_parsing.o\
m_tools.o\
tools.o\
tools_1.o\
m_tools2.o\
buckets.o\
cmd.o\
commands.o\
dollars.o\
heredocs.o\
queue.o\
destroy.o\
errors.o\
expressions1.o\
expressions2.o\
builtins.o\
compare.o\
conditions.o\
conditions2.o\
itoa.o\
join_strings.o\
quotes.o\
search.o\
strings.o\
help_destroy.o\
here_doc.o\
parsing.o\
prompt.o\
redirect.o\
run_heredoc.o\
expansion.o\
expansion1.o\
get_dollars.o\

all:$(NAME) 

$(NAME):$(OBJ)
	cc $(FLAGS) $(LIBRARY) -o $(NAME) $(OBJ)

$(OBJ):$(SRC)
	cc $(FLAGS) -c $^

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)

re:fclean all
