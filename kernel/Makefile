objfiles = start_kernel.o graph.o screen.o asm.o asmcpp.o block.o interrupt.o timer.o tetris.o keyboard.o
CXXFLAGS = -m32 -fno-rtti -fno-exceptions -I include -fno-builtin -fno-stack-protector  -O3 

kernel.bin: $(objfiles) Makefile
	ld -T link.ld -o kernel.bin -m elf_i386 $(objfiles)

%.o: %.cpp
	g++ $(CXXFLAGS) -c -o $@ $^

asm.o: asm.S Makefile
	nasm -f elf -o asm.o asm.S

clean:
	- rm *.o
	- rm *.bin