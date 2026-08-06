#pragma once
#include "gfx_prim_t.h"

typedef enum {
    GL_ATTR_V2F_T2F,
    GL_ATTR_V3F_T2F,
} gl15_attribute_format_t;

typedef enum {
    GL_SAMPLE_PIXEL  = 0x2600,
    GL_SAMPLE_LINEAR = 0x2601,
} gl15_sampling_preset_t;

typedef enum {
    GL_POINTS         = 0x0000,
    GL_LINES          = 0x0001,
    GL_LINE_LOOP      = 0x0002,
    GL_LINE_STRIP     = 0x0003,
    GL_TRIANGLES      = 0x0004,
    GL_TRIANGLE_STRIP = 0x0005,
    GL_TRIANGLE_FAN   = 0x0006,
    GL_QUADS          = 0x0007,
} gl15_topology_t;

typedef enum {
    GL_CMP_NEVER    = 0x0200,
    GL_CMP_LESS     = 0x0201,
    GL_CMP_EQUAL    = 0x0202,
    GL_CMP_LEQUAL   = 0x0203,
    GL_CMP_GREATER  = 0x0204,
    GL_CMP_NOTEQUAL = 0x0205,
    GL_CMP_GEQUAL   = 0x0206,
    GL_CMP_ALWAYS   = 0x0207,
} gl15_compare_func_t;

/* SETUP **********************************************************************/
void gl15_setup(void*(*get_proc_address)(const char*));

/* VERTEX ARRAYS **************************************************************/
void gl15_attribute_state(gl15_attribute_format_t f);
void gl15_draw_arrays(gl15_topology_t t, i32 first, i32 count);

/* BUFFER OBJECT **************************************************************/
u32  gl15_malloc(u64 size);
void gl15_memcpy(u32 id, u64 offset, u64 size, const void* data);
void gl15_bind_buffer(u32 id);
void gl15_free(u32 id);

/* TEXTURE ********************************************************************/
u32  gl15_create_texture(i64 width, i64 height, void *data);
void gl15_apply_sampling(u32 id, gl15_sampling_preset_t s);
void gl15_bind_texture(u32 id, u32 slot);
void gl15_delete_texture(u32 id);

/* RASTERIZATION **************************************************************/
void gl15_depth_range(f32 n, f32 f);
void gl15_viewport(i32 x, i32 y, i32 w, i32 h);

/* FOG ************************************************************************/
void gl15_fog(u32 mode, f32 r, f32 g, f32 b, f32 density, f32 start, f32 end);

/* PER-FRAGMENT OPERATIONS ****************************************************/
void gl15_clear(u8 r, u8 g, u8 b, u8 a);
void gl15_scissor_test(f32 x, f32 y, f32 w, f32 h);
void gl15_alpha_test(gl15_compare_func_t func, f32 ref);