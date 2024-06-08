#include "../inc/TLB.h"

#include <stdlib.h>

uint64_t timer = 0;

uint32_t get_timestamp(void) {
    return ++timer;
}

unsigned global_TLB_init(void) {
    global_tlb = calloc(1, sizeof(TLB));
    return 0;
}

void global_TLB_free(void) {
    if (global_tlb == NULL) {
        return;
    }
    free(global_tlb);
    global_tlb = NULL;
}

unsigned read_TLB(proc_id_t pid, unsigned vpn) {
    if (global_tlb->pid != pid) {
        // flash
        flush_TLB(global_tlb->pid);
        return -1;
    }
    for (uint32_t i = 0; i < TLB_SIZE; i++) {
        if (global_tlb->entries[i].valid && global_tlb->entries[i].vpn == vpn) {
            global_tlb->entries[i].lut = get_timestamp();
            return global_tlb->entries[i].ppn;
        }
    }
    return -1;
}

void write_TLB(proc_id_t pid, unsigned vpn, unsigned ppn) {
    if (global_tlb->pid != pid) {
        // flash
        flush_TLB(global_tlb->pid);
    }
    for (uint32_t i = 0; i < TLB_SIZE; i++) {
        if (global_tlb->entries[i].valid && global_tlb->entries[i].vpn == vpn) {
            global_tlb->entries[i].lut = get_timestamp();
            global_tlb->entries[i].ppn = ppn;
            return;
        }
    }
    for (uint32_t i = 0; i < TLB_SIZE; i++) {
        if (!global_tlb->entries[i].valid) {
            global_tlb->entries[i].valid = 1;
            global_tlb->entries[i].lut = get_timestamp();
            global_tlb->entries[i].ppn = ppn;
            return;
        }
    }
}

void remove_TLB(proc_id_t pid, unsigned vpn) {
    if (global_tlb->pid != pid) {
        flush_TLB(global_tlb->pid);
        return;
    }
    for (int32_t i = 0; i < TLB_SIZE; i++){
        if (global_tlb->entries[i].valid && global_tlb->entries[i].vpn == vpn) {
            global_tlb->entries[i].valid = 0;
        }
    }
}

void flush_TLB(proc_id_t pid) {
    if (pid != global_tlb->pid) return;
    for (uint32_t i = 0; i < TLB_SIZE; i++) {
        global_tlb->entries[i].valid = 0;
        global_tlb->entries[i].lut = 0;
    }
}
