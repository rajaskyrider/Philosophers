# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 13:53:39 by rpandipe          #+#    #+#              #
#    Updated: 2024/09/18 13:05:14 by rpandipe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus
CC			= cc
CFLAG		= -Wall -Werror -Wextra  -pthread -g -O3
RM 			= rm -rf
#SANITIZER 	= -fsanitize=thread
PHILO		= main.c utils.c init.c monitor.c utils2.c
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