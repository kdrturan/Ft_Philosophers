NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRC_FILES = srcs/check_errors.c srcs/job_utils.c srcs/main.c srcs/routine.c srcs/time.c srcs/utils.c
OBJ_FILES = $(SRC_FILES:.c=.o)

OBJS = objs/check_errors.o objs/job_utils.o objs/main.o objs/routine.o objs/time.o objs/utils.o
INCLUDE = includes/philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) \
	-I includes \
	-o $(NAME)

objs/%.o: srcs/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -I includes -c $< -o $@

clean:
	rm -rf objs/

fclean: clean
	rm -rf philo

re: fclean all

.PHONY: all clean fclean re