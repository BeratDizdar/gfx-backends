#pragma once
#include "gfx_prim_t.h"

// TODO:
// - enumları ekle
// - başlıkları düzelt

typedef struct {
    struct {
        const char *Vendor;
        const char *Renderer;
    } Device;
    struct {
        i32 MaxSize;
        i32 MaxUnits;
    } Texture;
    struct {
        i32 DepthBits;
        i32 StencilBits;
    } Framebuffer;
} gl15_props_t;
const gl15_props_t *gl15_get_props();

void gl15_setup(void *(*get_proc_address)(const char *));

/* OpenGL Operations */
void gl15_raster_state(u32 polygon_face, u32 polygon_mode, f32 point_size, f32 line_width);

void gl15_attribute_pointer(i32 ptr_type, i32 size, u32 type, i64 stride, void *offset);
void gl15_draw_arrays(i32 topology, i32 first, i32 count);

u32  gl15_create_buffer(u64 size, const void *data, u32 usage);
void gl15_update_buffer(u32 id, u64 offset, u64 size, const void *data);
void gl15_bind_buffer(u32 id);
void gl15_delete_buffer(u32 id);

void gl15_culling_state(u32 cull_face, u32 front_face);
void gl15_fog_state(u32 mode, f32 r, f32 g, f32 b, f32 density, f32 start, f32 end);
u32 gl15_create_texture(i32 width, i32 height, u32 format, const void *data);
void gl15_update_texture(u32 id, i32 x, i32 y, i32 width, i32 height, u32 format, const void *data);
void gl15_bind_texture(u32 id, i32 slot);
void gl15_delete_texture(u32 id);
void gl15_texture_sampling(u32 id, u32 min_filter, u32 mag_filter, u32 wrap_s, u32 wrap_t);
void gl15_texture_env(i32 slot, u32 mode);
void gl15_client_active_texture(i32 slot);

/* Coordinate Transformations */
void gl15_set_coord_transform(i32 x, i32 y, i32 w, i32 h, f32 n, f32 f);
void gl15_load_matrix(const f32 *m);

/* Per-Fragment Operations */
void gl15_scissor_test(i32 left, i32 bottom, i32 width, i32 height);
void gl15_alpha_test(u32 func, f32 ref);
void gl15_stencil_test_func(u32 func, i32 ref, u32 mask);
void gl15_stencil_test_op(u32 sfail, u32 dpfail, u32 dppass);
void gl15_depth_test(u32 func);
void gl15_blend_test_func_separate(u32 srcRGB, u32 dstRGB, u32 srcAlpha, u32 dstAlpha);
void gl15_blend_test_func(u32 src, u32 dst);

/* Whole Framebuffer Operations */
void gl15_stencil_mask(i32 mask);
void gl15_depth_mask(u32 mask);
void gl15_clear(u8 r, u8 g, u8 b, u8 a);