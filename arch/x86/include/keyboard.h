#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <idt.h>

struct keyboard_t
{
        const char* driver_name;
        const char* description;
        const char* author;
        const char* device_name;
        const char* license;
        char* buffer;
        void (*input_handler) (struct regs* regs);
        void (*init_keyboard) (void); // optional function
        void (*release_keyboard) (void); // optional function
};

extern int init_keyboard(struct keyboard_t);

/* Default x86 keyboard driver */

#define DEFAULT_KEYBOARD_WRITE_PORT 0x60

extern int default_keyboard_init_driver(void);

#endif
