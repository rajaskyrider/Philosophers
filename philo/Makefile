# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 13:53:39 by rpandipe          #+#    #+#              #
#    Updated: 2024/08/27 11:19:55 by rpandipe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAG		= -Wall -Werror -Wextra -g
RM 			= rm -rf
PHILO		= main.c check_input.c dinner.c init.c monitor.c routine.c \
			  utils.c
SRCS		= $(PHILO)
OBJDIR      = objs
OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAG) $(LIBFT) -pthread -o $(NAME)

clean:
		@$(RM) $(OBJDIR) > /dev/null 2>&1
		@echo -e '${RED}Clean complete!'

fclean:	clean
		@$(RM) $(NAME) > /dev/null 2>&1
		@echo -e '${RED}Build deleted!'
		@echo -ne '\n'

re: fclean all

.PHONY: all clean fclean re