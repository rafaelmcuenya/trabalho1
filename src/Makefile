# Nome do executável
PROJ_NAME = ted
ALUNO = Rafael Matui Cuenya

# Compilador
CC = gcc

# Flags
CFLAGS = -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration
LDFLAGS = -O0

OBJETOS = main.o leitor.o forma.o circulo.o retangulo.o linha.o texto.o \
          chao.o arena.o disparador.o carregador.o sobrepor.o criarTxt.o criarSvg.o \
          trataNomeArquivo.o

# Regra principal
$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) -lm
	echo "Compilação bem sucedida."

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Módulo principal
main.o: main.c leitor.h forma.h chao.h disparador.h carregador.h arena.h \
        circulo.h retangulo.h linha.h texto.h sobrepor.h criarTxt.h criarSvg.h \
        trataNomeArquivo.h

# Módulo leitor
leitor.o: leitor.c leitor.h criarTxt.h trataNomeArquivo.h

# Módulo forma
forma.o: forma.c forma.h circulo.h retangulo.h linha.h texto.h sobrepor.h

# Módulos de formas geométricas
circulo.o: circulo.c circulo.h
retangulo.o: retangulo.c retangulo.h
linha.o: linha.c linha.h
texto.o: texto.c texto.h

# Módulos de gerenciamento
chao.o: chao.c chao.h forma.h
arena.o: arena.c arena.h forma.h chao.h sobrepor.h circulo.h retangulo.h linha.h texto.h
disparador.o: disparador.c disparador.h carregador.h forma.h
carregador.o: carregador.c carregador.h forma.h

# Módulos de processamento e saída
sobrepor.o: sobrepor.c sobrepor.h circulo.h retangulo.h linha.h texto.h
criarTxt.o: criarTxt.c criarTxt.h circulo.h retangulo.h linha.h texto.h forma.h
criarSvg.o: criarSvg.c criarSvg.h circulo.h retangulo.h linha.h texto.h

# Módulo de tratamento de nomes
trataNomeArquivo.o: trataNomeArquivo.c trataNomeArquivo.h

# Regras utilitárias
clean:
	rm -f $(OBJETOS) $(PROJ_NAME)
	echo "Limpeza realizada"

valgrind: $(PROJ_NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(PROJ_NAME) -f teste.geo -o saida

.PHONY: clean valgrind
