#include <time.h>
#include <keyboard_driver.h>
#include <stdint.h>
#include <types.h>

typedef void (*handler_t)(void);
handler_t handlers[] = {timer_handler, keyboard_handler};

void irqDispatcher(qword irq) {
	handlers[irq]();
}


