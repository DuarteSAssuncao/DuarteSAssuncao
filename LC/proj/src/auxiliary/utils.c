/**
 * @file utils.c
 * @brief Definition of function to get a single byte from a device instead of four
 * @author T17_G1
 * @date 27/05/2024
 */

#include <lcom/lcf.h>
#include <lcom/utils.h>

/**
 * @brief Get a byte from a device instead of four
 * @param int port : port of the device
 * @uint8_t *value : pointer to byte to hold the value
 * @return int : 0 on success
 */
int (util_sys_inb)(int port, uint8_t *value) {
  if (value == NULL)
    return EINVAL;
  uint32_t tmp;
  int retv = sys_inb(port, &tmp);
  if (retv)
    return retv;
  *value = tmp;

  return 0;
}
