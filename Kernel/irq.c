#include "keyboard_driver.h"
#include "types.h"

typedef void (*handler_t)();

handler_t interrupts_handlers[] = {0, keyboardHandler};

void irqDispatcher(qword irq) {
	interrupts_handlers[irq]();
}


