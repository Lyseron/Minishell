NAME       = minishell
CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g

INCS	   = -I. -Iincludes -I$(LIBFT_DIR) 

LIBFT_DIR  = libft
LIBFT      = $(LIBFT_DIR)/libft.a
LDLIBS     = -lreadline

SRC_DIR    = src/
PARS_DIR   = $(SRC_DIR)parsing/
LEX_DIR    = $(SRC_DIR)lexer/
EXEC_DIR   = $(SRC_DIR)exec/
UTIL_DIR   = $(SRC_DIR)utils/
BUILT_DIR  = $(SRC_DIR)built_in/
SIGN_DIR   = $(SRC_DIR)signaux/
EXP_DIR    = $(SRC_DIR)expans/
CLEAN_DIR  = $(SRC_DIR)clean/
SC_DIR     = $(SRC_DIR)second_chance/

PARS_SRCS  = \
	$(PARS_DIR)parse_cmd.c \
	$(PARS_DIR)parse_pipe.c \
	$(PARS_DIR)parsing.c \
	$(PARS_DIR)parsing_error.c

LEXER_SRCS = \
	$(LEX_DIR)lexer_error.c \
	$(LEX_DIR)lexer.c

EXPAN_SRCS = \
	$(EXP_DIR)expans.c \
	$(EXP_DIR)expans_helper.c \
	$(EXP_DIR)expans_args.c

UTILS_SRCS = \
	$(UTIL_DIR)exec_utils.c \
	$(UTIL_DIR)exec_utils2.c \
	$(UTIL_DIR)exec_utils3.c \
	$(UTIL_DIR)lexer_utils.c \
	$(UTIL_DIR)exec_heredoc_utils.c \
	$(UTIL_DIR)exec_heredoc_utils2.c \
	$(UTIL_DIR)lexer_utils2.c \
	$(UTIL_DIR)parsing_utils.c \
	$(UTIL_DIR)parsing_utils2.c \
	$(UTIL_DIR)path_utils.c \
	$(UTIL_DIR)second_chance_utils.c \
	$(UTIL_DIR)env_utils.c \
	$(UTIL_DIR)expans_utils.c \
	$(UTIL_DIR)expans_utils2.c \
	$(UTIL_DIR)error_utils.c \
	$(UTIL_DIR)built_in_utils2.c \
	$(UTIL_DIR)built_in_utils.c

EXEC_SRCS  = \
	$(EXEC_DIR)exec_cmd.c \
	$(EXEC_DIR)exec_pipe.c \
	$(EXEC_DIR)exec_redir.c \
	$(EXEC_DIR)exec_built_in.c \
	$(EXEC_DIR)redir.c \
	$(EXEC_DIR)exec.c \
	$(EXEC_DIR)path.c

SIGN_SRCS  = \
	$(SIGN_DIR)signaux.c 

BUILT_SRC  = \
	$(BUILT_DIR)pwd.c \
	$(BUILT_DIR)exit.c \
	$(BUILT_DIR)cd.c \
	$(BUILT_DIR)echo.c \
	$(BUILT_DIR)export.c \
	$(BUILT_DIR)unset.c \
	$(BUILT_DIR)env.c 

CLEAN_SRCS  = \
	$(CLEAN_DIR)print_error.c \
	$(CLEAN_DIR)clean.c

SC_SRCS     = \
	$(SC_DIR)second_chance.c \
	$(SC_DIR)second_chance_helper.c

SRCS       = \
	$(SRC_DIR)main.c \
	$(PARS_SRCS) \
	$(LEXER_SRCS) \
	$(UTILS_SRCS) \
	$(EXEC_SRCS) \
	$(SIGN_SRCS) \
	$(BUILT_SRC) \
	$(EXPAN_SRCS) \
	$(CLEAN_SRCS) \
	$(SC_SRCS)



# to compile readline on mac :
READLINE_DIR = /opt/homebrew/opt/readline
CFLAGS += -I$(READLINE_DIR)/include
LDFLAGS += -L$(READLINE_DIR)/lib

OBJ_DIR    = obj/
OBJS       = $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))
RM         = rm -rf

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@printf "🍀\033[32m Compiling completed \033[0m🍀\n"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@printf "\033[34mObjects cleaned\033[0m\n"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@printf "\033[36mFull clean\033[0m\n"
re: fclean all

.PHONY: all clean fclean re asan valgrind leaks