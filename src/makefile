# Nome do executável
PROJ_NAME = ted
ALUNO = Rafael Matui Cuenya

# Compilador
CC = gcc

# Flags de compilação (conforme especificação)
CFLAGS = -g -O0 -std=c99 -fstack-protector-all -Wall -Wextra
LDFLAGS = 

# Encontra todos os arquivos .c automaticamente
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Regra principal
$(PROJ_NAME): $(OBJS)
	$(CC) -o $(PROJ_NAME) $(OBJS) $(LDFLAGS)

# Regra para cada arquivo objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS) $(PROJ_NAME)

# Recompilar tudo
re: clean $(PROJ_NAME)

# Valgrind com teste simples (apenas geo)
valgrind-simple: $(PROJ_NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(PROJ_NAME) -f teste.geo -o saida

# Valgrind com teste completo (geo e qry)
valgrind-complete: $(PROJ_NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(PROJ_NAME) -f teste.geo -q teste.qry -o saida

.PHONY: clean re valgrind-simple valgrind-complete
