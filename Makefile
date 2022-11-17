NC = \033[0m
RED = \033[0;91m
ORANGE = \033[93m
GREEN = \033[32m
PURPLE = \033[0;95m
BLUE = \033[0;34m
BOLD = \033[1m
CYAN = \033[36m

SRC_NAME				=		main.cpp
INCLUDES				=		./
NAME					=		containers
OBJ_NAME				=		$(SRC_NAME:.cpp=.o)
CC						=		c++
RM						=		rm -f
CFLAG					=		-Wall -Wextra -Werror -std=c++98 -g
SRC						=		$(SRC_NAME)
OBJ						=		$(OBJ_NAME)

.cpp.o:
								@${CC} ${CFLAG} -I${INCLUDES} -c $< -o ${<:.cpp=.o}
								@printf "${GREEN}[ OK ] ${<:.s=.o}${NC}                \r"
${NAME}:						${OBJ}
								@printf "${GREEN}[DONE]${NC}\n"
								@${CC} $^ -I${INCLUDES} -o $@ ${CFLAG}
								@printf "${CYAN}[COMPILATION COMPLETE]${NC}\n"
all:							${NAME}

clean:
								@${RM} ${OBJ}
								@printf "\n${GREEN}[ OK ]${NC}${RED} *.o files DELETED${NC}\n"
fclean:							clean
								@${RM} ${NAME}
								@printf "${GREEN}[ OK ]${NC}${RED} ${NAME} DELETED${NC}\n"
re:								fclean ${NAME}
.PHONY:							all clean fclean re
