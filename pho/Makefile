NAME	:=	philo

#CC		:=	cc -Wall -Wextra -Werror -g -pthread
#CC		:=	cc -Wall -Wextra -Werror -g -fsanitize=address
# CC		:=	cc -Wall -Wextra -Werror -g -pthread -fsanitize=thread # osc
CC		:=	cc -Wall -Wextra -Werror -g -pthread # ubu

RM		:=	/bin/rm -f
INC		:=	-I./

PRINT		:=	route_cs.c \
			route_id.c \
			route_p.c \
			route_u.c \
			route_x.c \
			print.c

UTL		:=	ft_atoi.c \
			ft_atoll.c \
			ft_minmax.c \
			ft_current_ms.c \
			$(addprefix print/, $(PRINT))

SIM		:=	philo_jobs.c \
			philo_sims.c \
			trackers.c \
			checkers.c \
			cleaners.c \
			parsers.c \

SRC		:=	main.c \
			$(addprefix utils/, $(UTL)) \
			$(addprefix helpers/, $(HEL)) \
			$(addprefix simulation/, $(SIM))

BUD		:=	$(SRC:%.c=%.o)

all		:	$(NAME)

%.o		:	%.c
			@ $(CC) $(INC) -c $< -o $@
			@ echo "compiling [$@]"

$(NAME)	:	$(BUD)
			@ $(CC) $(BUD) -o $@
			@ echo "compiling [$@]"
			@#@ printf "\n(remember to delete the fsanitize line)"
			@#@ printf "\n(remember to delete the fsanitize line)"
			@#@ printf "\n(remember to delete the fsanitize line)\n"
			@ printf "\n- \n\n"

clean	:
			@ $(RM) $(BUD)

fclean	:	clean
			@ $(RM) $(NAME) *.o */*.o out

c		: 	clean	
f		:	fclean
re		:	fclean all
.PHONY	:	fclean clean all re f c
