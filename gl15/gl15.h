#pragma once
#include "../types.h"

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
void gl15_vertex_v2f_t2f();
void gl15_vertex_v3f_t2f();
void gl15_draw_arrays(gl15_topology_t t, i32 first, i32 count);

/* BUFFER OBJECT **************************************************************/
u32  gl15_buffer_create(u64 size);
void gl15_buffer_memcpy(u32 id, u64 offset, u64 size, const void* data);
void gl15_buffer_bind(u32 id);
void gl15_buffer_delete(u32 id);

/* TEXTURE ********************************************************************/
u32  gl15_texture_create(i64 width, i64 height, const void *data);
void gl15_texture_nearest(u32 id);
void gl15_texture_linear(u32 id);
void gl15_texture_unit(u32 id, u32 unit);
void gl15_texture_delete(u32 id);

/* RASTERIZATION **************************************************************/
void gl15_depth_range(f32 n, f32 f);
void gl15_viewport(i32 x, i32 y, i32 w, i32 h);

/* FOG ************************************************************************/
void gl15_fog(u32 mode, u8 r, u8 g, u8 b, f32 density, f32 start, f32 end);

/* PER-FRAGMENT OPERATIONS ****************************************************/
void gl15_clear(u8 r, u8 g, u8 b, u8 a);
void gl15_scissor_test(f32 x, f32 y, f32 w, f32 h);
void gl15_alpha_test(gl15_compare_func_t func, f32 ref);

/* FIXED-SHADING PROGRAM ******************************************************/
// TODO:
// void gl15_program_texture(u32 unit);