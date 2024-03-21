# Variáveis
CC = gcc 
# Compilador a ser utilizado
OUTPUT_DIR = ./build
# Diretório de saída e nome do programa
OUTPUT = $(OUTPUT_DIR)/program 
# Arquivos fonte
SOURCES = main.c operations/blur_grey.c operations/copy.c operations/distance.c utils/bmp.c utils/fs.c utils/writing.c
# Diretório dos arquivos objeto baseado no diretório dos arquivos fonte
OBJECTS = $(patsubst %.c,$(OUTPUT_DIR)/%.o,$(SOURCES))

# Regras
# Aqui definimos as regras de compilação.

# o all é a regra padrão, ou seja, quando
# executamos o comando make, ele irá executar
# a regra all. 

# $(OUTPUT) é a regra que gera
# o programa final, e depende de $(OBJECTS),
# que é a regra que gera os arquivos objeto.

all: $(OUTPUT)

# Aqui é definida a ligação dos arquivos objeto
# gerados na regra $(OBJECTS) para gerar o
# programa final.
$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^

# Aqui é feita a compilação dos arquivos fonte
# para gerar os arquivos objeto.
$(OUTPUT_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@

# Essa regra serve para limpar os arquivos
# gerados na compilação. Se executar
# será necessário compilar novamente.
clean:
	rm -f $(OBJECTS)
	rm -f $(OUTPUT)

# Aqui definimos que as regras all e clean
# não são arquivos.
.PHONY: all clean 
