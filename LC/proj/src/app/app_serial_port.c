#include "app_serial_port.h"

#include <serial_port/sp_ih.h>

int_ret_t sp_proj_handler() {
    serial_ih();
    return INT_CONTINUE;
}
