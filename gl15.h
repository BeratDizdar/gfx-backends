#pragma once

#include "primitive_types.h"

typedef struct {
    struct {
        const char *Vendor;
        const char *Renderer;
    } Device;
} gl15_props_t;

void gl15_setup(void *(*get_proc_address)(const char *));
void gl15_clear(u8 r, u8 g, u8 b, u8 a);
u32  gl15_create_buffer(u32 id, u64 size, const void* data, u32 usage);
void gl15_draw_arrays(i32 topology, i32 first, i32 count);