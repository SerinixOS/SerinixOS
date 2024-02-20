# set flags to 0
.set FLAGS,    0

# set magic number to 0x1BADB002 to be identified by bootloader 
.set MAGIC,    0x1BADB002

# set the checksum
.set CHECKSUM, -(MAGIC + FLAGS)

# set multiboot enabled
.section .multiboot

# define type to long for each data defined as above
.long MAGIC
.long FLAGS
.long CHECKSUM

# set the stack bottom 
stackBottom:

# define the maximum size of stack to 512 bytes
.skip 4096

# set the stack top which grows from higher to lower
stackTop:

.section .text
.global _start
.type _start, @function

_start:
    # assign current stack pointer location to stackTop
    movl $stackTop, %esp   # Use movl for 32-bit value

    # call the kernel main function
    call kernel_entry

    cli  # Disable interrupts

    # put the system in an infinite loop
hltLoop:
    hlt
    jmp hltLoop

.size _start, . - _start

.section .bss
# Reserve space for the stack
.stack:
    .skip 4096  # 4KB stack size

.section .text
# Define the entry point
.global _start
.extern kernel_entry  # Assume kernel_entry is your C kernel's entry point

_start_kernel:
    # Set up the stack
    movl $stackTop, %esp   # Use movl for 32-bit value

    # Call your kernel's main function
    call kernel_entry

    # Halt the CPU
    cli
halt:
    hlt
    jmp halt
