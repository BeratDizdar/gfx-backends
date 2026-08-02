#include "gl15.h"
#include "gl15_functions.def"
#include "gl_constants.def"

#define X(name, args) void*(*name)args;
    GL15_FUNCTIONS
#undef X

void gl15_setup(void *(*get_proc_address)(const char *)) {
    #define X(name, args) name = get_proc_address(#name);
        GL15_FUNCTIONS
    #undef X
}

void gl15_clear(u8 r, u8 g, u8 b, u8 a) {
    glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl15_draw_arrays(i32 topology, i32 first, i32 count) {
    glDrawArrays(topology, first, count);
}