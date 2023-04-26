run: build/hd.img
	- echo c | bochs -f bochsrc

debug: build/hd.img
	- bochs -f bochsrc

build/hd.img: build/mbr.bin build/loader.bin kernel/kernel.bin

build/mbr.bin: asm/mbr.S asm/boot.inc
	nasm -I asm -o build/mbr.bin asm/mbr.S
	dd if=build/mbr.bin of=build/hd.img bs=512 count=1 conv=notrunc

build/loader.bin: asm/loader.S asm/boot.inc
	nasm -I asm -o build/loader.bin asm/loader.S
	dd if=build/loader.bin of=build/hd.img bs=512 count=5 conv=notrunc seek=2

kernel/kernel.bin: kernel/*.cpp kernel/*.S kernel/Makefile
	make -C kernel
	dd if=kernel/kernel.bin of=build/hd.img bs=512 count=200 seek=9 conv=notrunc

clean:
	- find -name "*.bin" | xargs -I {} rm {}
	- find -name "*.o" | xargs -I {} rm {}