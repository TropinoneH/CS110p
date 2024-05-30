#include "../inc/simulator.h"
#include "../inc/TLB.h"
#include <assert.h>
#include <stdlib.h>

status_t allocate_page(Process *process, addr_t address,
                       addr_t physical_address) {
  // This is guaranteed by the simulator
  assert(address >> OFFSET_BITS << OFFSET_BITS == address);
  assert(physical_address >> OFFSET_BITS << OFFSET_BITS == physical_address);
  // 1. Check if the process is valid
  if (process == NULL) {
    return ERROR;
  }
  // TODO: Implement me!
  return SUCCESS;
}

status_t deallocate_page(Process *process, addr_t address) {
  // This is guaranteed by the simulator
  assert(address >> OFFSET_BITS << OFFSET_BITS == address);
  // 1. Check if the process is valid
  if (process == NULL) {
    return ERROR;
  }
  // TODO: Implement me!
  return SUCCESS;
}

status_t read_byte(Process *process, addr_t address, byte_t *byte) {
  // 1. Check if the process is valid
  if (process == NULL) {
    return ERROR;
  }
  // TODO: Implement me!
  return SUCCESS;
}

status_t write_byte(Process *process, addr_t address, const byte_t *byte) {
  // 1. Check if the process is valid
  if (process == NULL) {
    return ERROR;
  }
  // TODO: Implement me!
  return SUCCESS;
}
