CFLAGS = -Wall -Werror -Wextra
SOURCES = pipex.c args_utils.c ft_split.c pipex_exec_util.c str_utils.c pipex_lst_utils.c
BSOURCES = pipex_bonus.c args_utils.c ft_split.c pipex_exec_util.c str_utils.c pipex_lst_utils.c
CC = cc
OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

bonus: $(BOBJECTS)
	$(CC) $(CFLAGS) $(BOBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS) $(BOBJECTS) 

fclean: clean
	rm -f $(NAME)

re: fclean all
