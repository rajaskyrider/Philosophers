# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 13:53:39 by rpandipe          #+#    #+#              #
#    Updated: 2024/09/07 00:12:59 by rpandipe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAG		= -Wall -Werror -Wextra  -pthread -g -O3
RM 			= rm -rf
#SANITIZER 	= -fsanitize=thread
PHILO		= main.c check_input.c dinner.c monitor.c routine.c \
			  utils.c utils2.c
SRCS		= $(PHILO)
OBJDIR      = objs
OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) $(SANITIZER) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAG) -o $(NAME) $(SANITIZER)

clean:
		@$(RM) $(OBJDIR) > /dev/null 2>&1
		@echo -e '${RED}Clean complete!'

fclean:	clean
		@$(RM) $(NAME) > /dev/null 2>&1
		@echo -e '${RED}Build deleted!'
		@echo -ne '\n'

re: fclean all

.PHONY: all clean fclean re