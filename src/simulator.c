#include "../inc/simulator.h"
#include "../inc/TLB.h"
#include <assert.h>
#include <stdlib.h>

status_t allocate_page(Process *process, addr_t address, addr_t physical_address) {
    // This is guaranteed by the simulator
    assert(address >> OFFSET_BITS << OFFSET_BITS == address);
    assert(physical_address >> OFFSET_BITS << OFFSET_BITS == physical_address);
    // 1. Check if the process is valid
    if (process == NULL) {
        return ERROR;
    }
    // Implement me!
    // decode
    uint32_t vpn1 = address >> (OFFSET_BITS + L2_BITS);
    uint32_t vpn2 = (address & ((1 << (OFFSET_BITS + L2_BITS)) - 1)) >> OFFSET_BITS;

    if ((physical_address >> OFFSET_BITS) >= MAX_NUM_PAGES || vpn1 >= (1 << L1_BITS)) return ERROR;
    if (process->page_table.entries[vpn1].entries != NULL) {
        if (process->page_table.entries[vpn1].entries[vpn2].valid)
            return ERROR;
    } else {
        // alloc
        process->page_table.entries[vpn1].entries = calloc(1 << L2_BITS, sizeof(PTE));
    }

    process->page_table.entries[vpn1].entries[vpn2].frame = (physical_address >> OFFSET_BITS);
    process->page_table.entries[vpn1].entries[vpn2].valid = 1;
    process->page_table.entries[vpn1].valid_count++;

    return SUCCESS;
}

status_t deallocate_page(Process *process, addr_t address) {
    // This is guaranteed by the simulator
    assert(address >> OFFSET_BITS << OFFSET_BITS == address);
    // 1. Check if the process is valid
    if (process == NULL) {
        return ERROR;
    }
    // Implement me!
    uint32_t vpn1 = address >> (OFFSET_BITS + L2_BITS);
    uint32_t vpn2 = (address & ((1 << (OFFSET_BITS + L2_BITS)) - 1)) >> OFFSET_BITS;
    uint32_t vpn = address >> OFFSET_BITS;

    if (process->page_table.entries[vpn1].entries == NULL || !process->page_table.entries[vpn1].entries[vpn2].valid) return ERROR;

    free(process->page_table.entries[vpn1].entries);
    process->page_table.entries[vpn1].entries = NULL;
    process->page_table.entries[vpn1].valid_count = 0;
    // remove cur page from TLB
    remove_TLB(process->pid, vpn);
    return SUCCESS;
}

status_t read_byte(Process *process, addr_t address, byte_t *byte) {
    // 1. Check if the process is valid
    if (process == NULL) {
        return ERROR;
    }
    // Implement me!
    uint32_t vpn1 = address >> (OFFSET_BITS + L2_BITS);
    uint32_t vpn2 = (address & ((1 << (OFFSET_BITS + L2_BITS)) - 1)) >> OFFSET_BITS;
    uint32_t vpn = address >> OFFSET_BITS;

    uint32_t offset = address & ((1 << OFFSET_BITS) - 1);

    // find in TLB
    uint32_t ppn = read_TLB(process->pid, vpn);
    if (ppn != (uint32_t) -1) {
        // hit
        *byte = main_memory->pages[ppn]->data[offset];
        return TLB_HIT;
    }
    // walk
    if (process->page_table.entries[vpn1].entries == NULL || !process->page_table.entries[vpn1].entries[vpn2].valid)
        return ERROR;

    ppn = process->page_table.entries[vpn1].entries[vpn2].frame;
    write_TLB(process->pid, vpn, ppn);

    *byte = main_memory->pages[ppn]->data[offset];
    return SUCCESS;
}

status_t write_byte(Process *process, addr_t address, const byte_t *byte) {
    // 1. Check if the process is valid
    if (process == NULL) {
        return ERROR;
    }
    // Implement me!
    // find in tlb
    uint32_t vpn1 = address >> (OFFSET_BITS + L2_BITS);
    uint32_t vpn2 = (address & ((1 << (OFFSET_BITS + L2_BITS)) - 1)) >> OFFSET_BITS;
    uint32_t vpn = address >> OFFSET_BITS;

    uint32_t offset = address & ((1 << OFFSET_BITS) - 1);

    uint32_t ppn = read_TLB(process->pid, vpn);
    if (ppn != (uint32_t) -1) {
        // write in
        main_memory->pages[ppn]->data[offset] = *byte;
        return TLB_HIT;
    }

    // walk
    if (process->page_table.entries[vpn1].entries == NULL || !process->page_table.entries[vpn1].entries[vpn2].valid)
        return ERROR;

    ppn = process->page_table.entries[vpn1].entries[vpn2].frame;
    write_TLB(process->pid, vpn, ppn);
    main_memory->pages[ppn]->data[offset] = *byte;

    return SUCCESS;
}
