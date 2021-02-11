.PHONY: all run remake clean

NAME:=EchidnaOs

AS=i686-elf-as
CXX=i686-elf-g++
LD=i686-elf-ld

# project repertories
SRC=src
OBJ=obj
INCLUDE=include
ISO=iso
BOOT_FILE=$(ISO)/boot

# source files
C_FILES=$(wildcard $(SRC)/*.c)
CPP_FILES=$(wildcard $(SRC)/*.cpp)
AS_FILES=$(wildcard $(SRC)/*.asm)

# object files
OBJ_FILES+=$(C_FILES:$(SRC)/%.c=$(OBJ)/%.o)
OBJ_FILES+=$(AS_FILES:$(SRC)/%.asm=$(OBJ)/%.o)
OBJ_FILES+=$(CPP_FILES:$(SRC)/%.cpp=$(OBJ)/%.o)

CPPFLAGS=-O2 -I$(INCLUDE) -fexec-charset=850 -std=c++17

all: $(NAME).iso

remake: clean all

run: all
	qemu-system-x86_64 -drive file=$(NAME).iso,format=raw

$(NAME).iso: $(BOOT_FILE)/$(NAME).bin
	@grub-mkrescue -o $@ $(ISO)/ 2> /dev/null

$(BOOT_FILE)/$(NAME).bin: $(OBJ_FILES)
	$(LD) -n -o $@ -T linker.ld $^

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) -c $^ -o $@ $(CPPFLAGS)

$(OBJ)/%.o: $(SRC)/%.asm
	$(AS) $^ -o $@

clean:
	rm $(OBJ)/* -fv
	rm $(NAME).iso -fv
	rm $(BOOT_FILE)/$(NAME).bin -fv
