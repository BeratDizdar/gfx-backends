# gfx-backends
- OpenGL 1.5 (Windows & Linux) for old hardwares
- OpenGL 3.3 (Windows & Linux)
- Metal (Mac)

## References
- [GLSLangSpec.3.30.pdf](https://registry.khronos.org/OpenGL/specs/gl/GLSLangSpec.3.30.pdf)
- [glspec33.core.pdf](https://registry.khronos.org/OpenGL/specs/gl/glspec33.core.pdf)
- [glspec15.pdf](https://registry.khronos.org/OpenGL/specs/gl/glspec15.pdf)
- [es1.1.xhtml](https://registry.khronos.org/OpenGL-Refpages/es1.1/xhtml/)

## Examples
<details>
<summary>OpenGL 1.5 Backend</summary>

```c
#include "swl-main/swl.h"
#include "gfx-backends-main/gl15.h"
#define CUI_IMPL
#include "c-ui-main/cui.h"
#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
typedef struct {float x, y, u, v;} vertex_t;

int main() {
    swl_CreateWindow("X", 400, 300);
    swl_GL_CreateContext(1, 5, 24, 8);
    gl15_setup(swl_GL_GetProcAddress);
    
    cui_texinfo_t ti;
    int c_in;
    unsigned char *tb = stbi_load("tileset.png", &ti.width, &ti.height, &c_in, 4);
    u32 t = gl15_create_texture(ti.width, ti.height, 0x1908, tb);
    free(tb);

    cui_uv_rect_t r = cui_get_uv_rect(0, 0, 16, 16, ti);
    vertex_t v[4] = {
        { -0.5f,  0.5f, r.uv[0], r.uv[1] },
        { -0.5f, -0.5f, r.uv[2], r.uv[3] },
        {  0.5f, -0.5f, r.uv[4], r.uv[5] },
        {  0.5f,  0.5f, r.uv[6], r.uv[7] },
    };

    u32 b = gl15_create_buffer(sizeof(v), v, 0x88E4);
    gl15_bind_buffer(b);
    gl15_attribute_pointer(0, 2, 0x1406, sizeof(vertex_t), 0);
    gl15_attribute_pointer(1, 2, 0x1406, sizeof(vertex_t), (void*)(sizeof(float)*2));

    for (;!swl_ShouldClose();) {
        if (swl_IsKeyPressed(27)) swl_SendQuitEvent();
        gl15_clear(53, 75, 75, 255);

        gl15_bind_buffer(b);
        gl15_bind_texture(t, 0);
        gl15_draw_arrays(0x0007, 0, 4);

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
```

</details>

<details>
<summary>OpenGL 3.3 Backend</summary>

</details>