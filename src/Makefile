CC=gcc
LIBS= 
#OBJECCTS = findabi.o elf_abi.o
CFLAGS = 
LIBS =

FINDABI = findabi.out

all: $(FINDABI)

$(FINDABI): findabi.o elf_abi.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

findabi.o:
	$(CC) $(CFLAGS) -c findabi.c -o findabi.o
elf_abi.o:
	$(CC) $(CFLAGS) -c elf_abi.c -o elf_abi.o

#%.o:%.c:
#	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm *.o *.out

