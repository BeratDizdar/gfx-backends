#include "gl15.h"
#include "gl15_functions.def"
#include "gl_constants.def"
#define X(name, args) void*(*name)args;
    GL15_FUNCTIONS
#undef X

/* SETUP **********************************************************************/
void gl15_setup(void*(*get_proc_address)(const char*)) {
    #define X(name, args) name = get_proc_address(#name);
        GL15_FUNCTIONS
    #undef X

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_FOG);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // bunlar şuanki client içinmiş
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

/* VERTEX ARRAYS **************************************************************/
void gl15_vertex_v2f_t2f() {
    glVertexPointer(2, 0x1406, sizeof(float)*4, 0);
    glTexCoordPointer(2, 0x1406, sizeof(float)*4, (void*)(sizeof(float)*2));
}

void gl15_vertex_v3f_t2f() {
    glVertexPointer(3, 0x1406, sizeof(float)*5, 0);
    glTexCoordPointer(2, 0x1406, sizeof(float)*5, (void*)(sizeof(float)*3));
}

void gl15_draw_arrays(gl15_topology_t t, i32 first, i32 count) {
    glDrawArrays(t, first, count);
}

/* BUFFER OBJECT **************************************************************/
u32  gl15_buffer_create(u64 size) {
    u32 b;
    glGenBuffers(1, &b);
    glBindBuffer(GL_ARRAY_BUFFER, b);
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
    return b;
}

void gl15_buffer_memcpy(u32 id, u64 offset, u64 size, const void* data) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void gl15_buffer_bind(u32 id) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void gl15_buffer_delete(u32 id) {
    glDeleteBuffers(1, &id);
}

/* TEXTURE ********************************************************************/
u32 gl15_texture_create(i64 width, i64 height, const void *data) {
    u32 id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return id;
}

void gl15_texture_nearest(u32 id) {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void gl15_texture_linear(u32 id) {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void gl15_texture_unit(u32 id, u32 unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void gl15_texture_delete(u32 id) {
    glDeleteTextures(1, &id);
}

/* RASTERIZATION **************************************************************/
void gl15_depth_range(f32 n, f32 f) {
    glDepthRange(n, f);
}

void gl15_viewport(i32 x, i32 y, i32 w, i32 h) {
    glViewport(x, y, w, h);
}

/* FOG ************************************************************************/
void gl15_fog(u32 mode, u8 r, u8 g, u8 b, f32 density, f32 start, f32 end) {
    glFogi(GL_FOG_MODE, mode);
    f32 color[4] = { r/255.0f, g/255.0f, b/255.0f, 1.0f };
    glFogfv(GL_FOG_COLOR, color);
    glFogf(GL_FOG_DENSITY, density);
    glFogf(GL_FOG_START, start);
    glFogf(GL_FOG_END, end);
}

/* PER-FRAGMENT OPERATIONS ****************************************************/
void gl15_clear(u8 r, u8 g, u8 b, u8 a) {
    glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void gl15_scissor_test(f32 x, f32 y, f32 w, f32 h) {
    glScissor(x, y, w, h);
}

void gl15_alpha_test(gl15_compare_func_t func, f32 ref) {
    glAlphaFunc(func, ref);
}