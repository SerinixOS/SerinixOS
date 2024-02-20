#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include "unit_types.h"

#define KEYBOARD_DATA_PORT 0X60

#define NULL 0

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

uint16* vga_buffer;

#define BOX_MAX_WIDTH 78
#define BOX_MAX_HEIGHT 23

#define BOX_SINGLELINE 1
#define BOX_DOUBLELINE 2

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

extern unsigned char read_scan_code(void);
extern char scan_code_to_ascii(unsigned char scan_code);
extern void print_char(char ch);
extern void print_string(char *str);
extern void print_color_string(char *str, uint8_t fore_color, uint8_t back_color);
extern void print_int(int num);
extern int digit_count(int num);
extern void itoa(int num, char *str);

static inline unsigned char inb(unsigned short port) {
    unsigned char data;
    asm volatile ("inb %1, %0" : "=a" (data) : "Nd" (port));
    return data;
}
#endif
