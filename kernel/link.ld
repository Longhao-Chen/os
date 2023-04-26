ENTRY(start_kernel)
SECTIONS
{
    . = 0xc0001500;
    .text : {
        *(.text)
    }
}