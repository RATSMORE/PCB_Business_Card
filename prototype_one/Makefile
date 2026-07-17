CC = arm-none-eabi-gcc 
CFLAGS = -nostdlib -c -mcpu=cortex-m4 -mthumb -g
LDFLAGS = -mcpu=cortex-m4 -mthumb --specs=nosys.specs  -nostartfiles -T RATSMORE_stm32f411re_linker.ld

all : proto_one.elf

main.o : prototype_one.c
	$(CC) $(CFLAGS) $^ -o $@


startup.o : RATSMORE_stm32f411re_startup.c
	$(CC) $(CFLAGS) $^ -o $@


proto_one.elf : main.o startup.o
	$(CC) $^ $(LDFLAGS) -o $@ -Wl,-Map=proto_one.map


clean :
	del /q /f *.o *.elf