#include "swl/swl.h"
#include "gfx-backends/gl15.h"
typedef struct {float x, y, u, v;} vertex_t;

//432'000'000 vertex iGPU (Intel(R) Iris(R) Xe Graphics) i├žin teorik limit 

u32 tex[16];
int main() {
    swl_CreateWindow("X", 400, 300);
    swl_GL_CreateContext(1, 5, 24, 8);
    gl15_setup(swl_GL_GetProcAddress);

    vertex_t v[3] = {
        { -0.5f, -0.5f, 0.0f, 0.0f },
        {  0.5f, -0.5f, 1.0f, 0.0f },
        {  0.0f,  0.5f, 0.5f, 1.0f },
    };

    u32 b = gl15_create_buffer(sizeof(v), v, 0x88E4);
    gl15_bind_buffer(b);
    gl15_attribute_pointer(0, 2, 0x1406, sizeof(vertex_t), 0);
    gl15_attribute_pointer(1, 2, 0x1406, sizeof(vertex_t), (void*)(sizeof(float)*2));

    u32 t = gl15_create_texture(4, 4, 0x1908, tex);

    for (;!swl_ShouldClose();) {
        if (swl_IsKeyPressed(27)) swl_SendQuitEvent();
        gl15_clear(53, 75, 75, 255);

        gl15_bind_buffer(b);
        gl15_bind_texture(tb, 0);
        gl15_draw_arrays(0x0004, 0, 3000000);

        swl_GL_SwapBuffers();
        swl_PollEvents();
        swl_PassScheduler();
    }
 
    gl15_delete_texture(t);
    gl15_delete_buffer(b);
    swl_GL_DestroyContext();
    swl_CloseWindow();
    return 0;
}
