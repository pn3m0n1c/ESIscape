##### Compilador y flags
# Compilador que vamos a usar
CC = gcc
# Para generar dependencias .d, practica recomendada
CFLAGS = -Wall -Wextra -g -MMD -MP
LDFLAGS = 

##### Directorios
# Directorio raíz del proyecto
SRC_DIR = src
# headers
INCLUDE_DIR = include
# Directorio para .o
BUILD_DIR = build
BIN_DIR = bin

# Directorios de los módulos actuales
PART_DIRS = $(SRC_DIR)/ui \
$(SRC_DIR)/salas \
$(SRC_DIR)/puzles \
$(SRC_DIR)/jugador \
$(SRC_DIR)/inventario \
$(SRC_DIR)/partida

# Para incluir los encabezados
INCLUDES =	-I$(INCLUDE_DIR) \
-I$(SRC_DIR)/ui \
-I$(SRC_DIR)/salas \
-I$(SRC_DIR)/puzles \
-I$(SRC_DIR)/jugador \
-I$(SRC_DIR)/inventario \
-I$(SRC_DIR)/partida

# Hacemos para adaptaarnos al sistema operativo,
# básicamente en un sistema operativo tenemos unos comandos
# y en otro pues otros, esta selectiva define variables en función
# al sistema operativo que se detecte
ifeq ($(OS), Windows_NT)

TARGET = $(BIN_DIR)/esi-escape.exe
MKDIR = mkdir
RM = rmdir /s /q
SOURCES := $(shell dir /s /b $(SRC_DIR)\*.c 2>nul)

else 
# Se entiende GNU-Linux en este caso
TARGET = $(BIN_DIR)/esi-escape
MKDIR = mkdir -p
RM      = rm -rf
# Busca los .c en los directorios, los archivos compilados serán .o en /build
SOURCES := $(shell find $(SRC_DIR) -name '*.c')

endif

OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Auto-generated dependency files
DEPS := $(OBJECTS:.o=.d)

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# De los .o generados anteriormente, saca el ejecutable
$(TARGET): $(OBJECTS)
	-$(MKDIR) $(BIN_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)
	@echo "Construido el target: $@"

# Compilar de .c a .o 
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	-$(MKDIR) $(@D)  # Create parent dir for .o file (e.g., build/Part1)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@  # $< = input .c file, $@ = output .o file

# Limpiar artefactos (no se que son)
clean:  
	$(RM) $(BUILD_DIR) $(BIN_DIR)
	@echo "Limpiados los artefactos y el directorio /bin"

# Include dependencies  
-include $(DEPS)
