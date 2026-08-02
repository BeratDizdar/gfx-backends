#include "gl15.h"
#include "gl15_functions.def"
#include "gl_constants.def"

#define X(name, args) void*(*name)args;
    GL15_FUNCTIONS
#undef X

static gl15_props_t p;
static void __id_init_gl15_props() {
    p.Device.Vendor     = (const char*)glGetString(GL_VENDOR);
    p.Device.Renderer   = (const char*)glGetString(GL_RENDERER);

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &p.Texture.MaxSize);
    glGetIntegerv(GL_MAX_TEXTURE_UNITS, &p.Texture.MaxUnits);

    glGetIntegerv(GL_DEPTH_BITS, &p.Framebuffer.DepthBits);
    glGetIntegerv(GL_STENCIL_BITS, &p.Framebuffer.StencilBits);
}
const gl15_props_t* gl15_get_props() { return &p; }

void gl15_setup(void *(*get_proc_address)(const char *)) {
    #define X(name, args) name = get_proc_address(#name);
        GL15_FUNCTIONS
    #undef X

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_FOG);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void gl15_attribute_pointer(i32 ptr_type, i32 size, u32 type, i64 stride, void *offset) {
    if (ptr_type == 0) {
        glVertexPointer(size, type, stride, offset);
    }
    else {
        glTexCoordPointer(size, type, stride, offset);
    }
}

void gl15_draw_arrays(i32 topology, i32 first, i32 count) {
    glDrawArrays(topology, first, count);
}

u32 gl15_create_buffer(u32 id, u64 size, const void *data, u32 usage) {
    u32 b;
    glGenBuffers(1, &b);
    if (data != (void*)0) {
        glBindBuffer(GL_ARRAY_BUFFER, b);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }
    return b;
}

void gl15_update_buffer(u32 id, u64 offset, u64 size, const void *data) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void gl15_bind_buffer(u32 id) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void gl15_delete_buffer(u32 id) {
    glDeleteBuffers(1, &id);
}

void gl15_culling_state(u32 cull_face, u32 front_face) {
    glFrontFace(front_face);
    glCullFace(cull_face);
}

void gl15_fog_state(u32 mode, f32 r, f32 g, f32 b, f32 density, f32 start, f32 end) {
    glFogi(GL_FOG_MODE, mode);
    f32 color[4] = { r, g, b, 1.0f };
    glFogfv(GL_FOG_COLOR, color);
    glFogf(GL_FOG_DENSITY, density);
    glFogf(GL_FOG_START, start);
    glFogf(GL_FOG_END, end);
}

u32 gl15_create_texture(i32 width, i32 height, u32 format, const void *data) {
    u32 t;
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    return t;
}

void gl15_update_texture(u32 id, i32 x, i32 y, i32 width, i32 height, u32 format, const void *data) {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, format, GL_UNSIGNED_BYTE, data);
}

void gl15_bind_texture(u32 id, i32 slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void gl15_delete_texture(u32 id) {
    glDeleteTextures(1, &id);
}

void gl15_texture_sampling(u32 id, u32 min_filter, u32 mag_filter, u32 wrap_s, u32 wrap_t) {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
}

void gl15_texture_env(i32 slot, u32 mode) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode);
}

void gl15_client_active_texture(i32 slot) {
    glClientActiveTexture(GL_TEXTURE0 + slot);
}

void gl15_set_coord_transform(i32 x, i32 y, i32 w, i32 h, f32 n, f32 f) {
    glViewport(x, y, w, h);
    glDepthRange(n, f);
}

void gl15_load_matrix(const f32 *m) {
    glLoadMatrixf(m);
}

void gl15_scissor_test(i32 left, i32 bottom, i32 width, i32 height) {
    glScissor(left, bottom, width, height);
}

void gl15_alpha_test(u32 func, f32 ref) {
    glAlphaFunc(func, ref);
}

void gl15_stencil_test_func(u32 func, i32 ref, u32 mask) {
    glStencilFunc(func, ref, mask);
}

void gl15_stencil_test_op(u32 sfail, u32 dpfail, u32 dppass) {
    glStencilOp(sfail, dpfail, dppass);
}

void gl15_depth_test(u32 func) {
    glDepthFunc(func);
}

void gl15_blend_test_func_separate(u32 srcRGB, u32 dstRGB, u32 srcAlpha, u32 dstAlpha) {
    glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void gl15_blend_test_func(u32 src, u32 dst) {
    glBlendFunc(src, dst);
}

void gl15_stencil_mask(i32 mask) {
    glStencilMask(mask);
}

void gl15_depth_mask(u32 mask) {
    glDepthMask(mask);
}

void gl15_clear(u8 r, u8 g, u8 b, u8 a) {
    glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}