#include "heap.h"
#include "kernel.h"
#include "status.h"
#include "memory/memory.h"
#include <stdbool.h>

static int heap_validate_table(void* ptr, void* end, struct heap_table* table) {
    int res = 0;
    size_t table_size = (size_t)(end - ptr);
    size_t total_blocks = table_size / OS_HEAP_BLOCK_SIZE;
    if (table->total != total_blocks) {
        res = -EINVARG;
        return res;
    }
    return res;
}
static bool heap_validate_alignment(void* ptr) {
    return ((unsigned int)ptr % OS_HEAP_BLOCK_SIZE) == 0;
}

int heap_create(struct heap* heap, void* datapool_ptr, void* heap_end, struct heap_table* table) {
    int res = 0;

    if (!heap_validate_alignment(datapool_ptr) || heap_validate_alignment(heap_end)) {
        res = -EINVARG;
        return res;
    }
    memset(heap, 0, sizeof(struct  heap));
    heap->saddr = datapool_ptr;
    heap->table = table;
    res = heap_validate_table(datapool_ptr, heap_end, table);
    if (res < 0) {
        return res;
    }

    size_t table_size = sizeof(HEAP_BLOCK_TABLE_ENTRY) * table->total;
    memset(table->entries, HEAP_BLOCK_IS_FIRST, table_size);
    return res;   
}

static uint32_t heap_align_value_to_upper(uint32_t val) {
    if ((val % OS_HEAP_BLOCK_SIZE) == 0) {
        return val;
    }

    val = (val - (val % OS_HEAP_BLOCK_SIZE));
    val += OS_HEAP_BLOCK_SIZE;
    return val;
}

static int heap_get_entry_type(HEAP_BLOCK_TABLE_ENTRY entry) {
    return entry & 0x0f;
}

int heap_get_start_block(struct heap* heap, uint32_t total_blocks) {
    struct heap_table* table = heap->table;
    int block_count = 0;
    int block_start = -1;

    for (size_t i = 0; i < table->total; i++) {
        if (heap_get_entry_type(table->entries[i]) != HEAP_BLOCK_TABLE_ENTRY_FREE) {
            block_count = 0;
            block_start = -1;
            continue;
        }

        // if this is the first block
        if (block_start == -1) {
            block_start = i;
        }
        block_count++;
        if (block_count == total_blocks) {
            break;
        }
    }

    if (block_start == -1) {
        return -ENOMEM;
    }

    return block_start;
}

void* heap_block_to_address(struct heap* heap, int block) {
    return heap->saddr + (block * OS_HEAP_BLOCK_SIZE);
}

void heap_mark_blocks_taken(struct heap* heap, int start_block, int total_blocks) {
    int end_block = (start_block + total_blocks) - 1;
    HEAP_BLOCK_TABLE_ENTRY entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN | HEAP_BLOCK_IS_FIRST;

    if (total_blocks > 1) {
        entry |= HEAP_BLOCK_HAS_NEXT;
    }

    for (int i = start_block; i <= end_block; i++) {
        heap->table->entries[i] = entry;
        entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
        if (i != end_block - 1) {
            entry |= HEAP_BLOCK_HAS_NEXT;
        }
    }
}

void* heap_malloc_blocks(struct heap* heap, uint32_t total_blocks) {
    void* address = 0;

    int start_block = heap_get_start_block(heap, total_blocks);
    if (start_block < 0) {
        return address;
    }

    address = heap_block_to_address(heap, start_block);

    // Mark the blocks as taken
    heap_mark_blocks_taken(heap, start_block, total_blocks);
    return address;
} 

void* heap_malloc(struct heap* heap, size_t size) {
    size_t aligned_size = heap_align_value_to_upper(size);
    uint32_t total_blocks = aligned_size / OS_HEAP_BLOCK_SIZE;
    return heap_malloc_blocks(heap, total_blocks);
}

void heap_free(struct heap* heap, void* ptr) {
}