NAME			= philosophers

#COMPILATION
CC				= clang
CFLAGS			= -Wall -Wextra -Werror -g -pthread

#VISUAL
MAKEFLAGS		+= --no-print-directory
RM_LINE			= @tput cuu1 && tput el

BLUE			= \033[0;34m
BOLD_BLUE		= \e[1;94m
GREEN			= \033[0;92m
DEF_COLOR		= \033[0;39m

#FILES DIRECTORIES
SRC_DIR			=	srcs/
OBJS_DIR		=	objs/
UTILS_DIR		=	utils/
CORE_DIR		=	core/

#SRCS FILES
C_FILES			=	$(CORE_DIR)philosophers.c \
					$(CORE_DIR)init.c \
					$(UTILS_DIR)libft_utils.c \
					$(UTILS_DIR)utils.c \
					$(UTILS_DIR)all_kinds_of_free.c

SRC				=	$(addprefix $(SRC_DIR), $(C_FILES))
OBJS			=	$(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC))

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< into $@..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@${RM_LINE}

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${BLUE}Done creating [ ${BOLD_BLUE}${NAME}${BLUE} ]${DEF_COLOR}"

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@echo "Removing ${NAME} and dependencies..."
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re