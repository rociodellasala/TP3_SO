#include "keyboard_driver.h"
#include "types.h"

typedef void (*handler_t)(void);

handler_t handlers[] = {0, keyboardHandler};

void irqDispatcher(qword irq) {
	handlers[irq]();
}


