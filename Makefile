NAME            =   avm

INC_PATH        =   include

SRC_PATH        =   src

SRC             = srcs/main.cpp \
		srcs/VirtualMachine.cpp \
		srcs/AbstractVMException.cpp \
		srcs/Commands.cpp \
		srcs/Lexer.cpp \
		srcs/OperandFactory.cpp \
		srcs/Parser.cpp \
		srcs/Token.cpp

CXXFLAGS        =  -g -Wall -Wextra -Werror -std=c++20 -pedantic -fsanitize=address

INC             =   -I${INC_PATH}

OBJ_D           =   objs

OBJ             =   $(SRC:${SRC_PATH}/%.cpp=${OBJ_D}/%.o)

UNAME           :=  $(shell uname)

RM              =   rm -rf

ifeq ($(UNAME), Darwin)
    CXX = c++
else ifeq ($(UNAME), FreeBSD)
    CXX = clang++
else
    CXX  = g++
    CXXFLAGS += -D LINUX
endif

# Sphinx and Doxygen configuration
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = ./doc
BUILDDIR      = ./doc/_build

all:        ${NAME}

${OBJ_D}/%.o:${SRC_PATH}/%.cpp
			@mkdir -p ${OBJ_D}
			$(CXX) $(CXXFLAGS) ${INC} -o $@ -c $<

${NAME}:   ${OBJ}
			@printf "Compiling $(C_YELLOW)$(NAME)$(C_END) ... \n"
			$(CXX) $(CXXFLAGS) ${INC} -o ${NAME} ${OBJ}
			@printf "$(C_GREEN)DONE$(C_END)\n"

clean:
	$(RM) $(OBJ_D)
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	@printf "$(C_RED)Cleaning objs$(C_END)\n"

fclean:     clean
	$(RM) $(NAME) *valgrind-out.txt doc/xml
	@printf "$(C_RED)Deleted Everything$(C_END)\n"

re: fclean all

show:
	@printf "$(C_GREEN)"
	@printf "UNAME     : $(UNAME)\n"
	@printf "NAME      : $(C_YELLOW)$(NAME)$(C_GREEN)\n"
	@printf "CXX       : $(CXX)\n"
	@printf "CXXFLAGS  : $(CXXFLAGS)\n"
	@printf "INCLUDES  : $(INC)\n"
	@printf "SRC       : $(C_YELLOW)$(SRC)$(C_GREEN)\n"
	@printf "OBJ       : $(C_YELLOW) $(OBJ)$(C_END)\n"

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile all re clean fclean show

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@-doxygen ./doc/Doxyfile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

C_BLACK     = \033[0;30m
C_RED       = \033[0;31m
C_GREEN     = \033[0;32m
C_YELLOW    = \033[0;33m
C_BLUE      = \033[0;34m
C_WHITE     = \033[0;37m
C_END       = \033[0m
