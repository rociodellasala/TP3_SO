#include <keyboard_driver.h>
#include <stdint.h>
#include <time.h>
#include <types.h>

typedef void (*handler_t)(void);
handler_t handlers[] = {0, keyboard_handler};

void irqDispatcher(qword irq) {
	handlers[irq]();
}


