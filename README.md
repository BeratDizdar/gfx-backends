# gfx-backends
- OpenGL 1.5 (Windows & Linux) for old hardwares
- OpenGL 3.3 (Windows & Linux)
- Metal (Mac)

## References
- [GLSLangSpec.3.30.pdf](https://registry.khronos.org/OpenGL/specs/gl/GLSLangSpec.3.30.pdf)
- [glcorearb.h](https://registry.khronos.org/OpenGL/api/GL/glcorearb.h)
- [glspec33.core.pdf](https://registry.khronos.org/OpenGL/specs/gl/glspec33.core.pdf)
- [glspec15.pdf](https://registry.khronos.org/OpenGL/specs/gl/glspec15.pdf)
- [es1.1.xhtml](https://registry.khronos.org/OpenGL-Refpages/es1.1/xhtml/)

## Examples
<details>
<summary>OpenGL 1.5 Backend</summary>

```c
#include "swl/swl.h"
#include "gfx-backends/gl15_2.h"
#define CUI_IMPL
#include "c-ui/cui.h"
typedef struct {float x, y, u, v;} vertex_t;

int main() {
    swl_CreateWindow("X", 400, 300);
    swl_GL_CreateContext(1, 5, 24, 8);
    gl15_setup(swl_GL_GetProcAddress);
    
    unsigned int tex[] = {
        0xFFFF00FF, //ABGR
        0xFF00FF00, //ABGR
    };
    u32 t = gl15_create_texture(2, 1, tex);
    gl15_apply_sampling(t, GL_SAMPLE_PIXEL);

    cui_uv_rect_t r = cui_get_uv_rect(0, 0, 2, 1, (cui_texinfo_t){2, 1});
    vertex_t v[4] = {
        { -0.5f,  0.5f, r.uv[0], r.uv[1] },
        { -0.5f, -0.5f, r.uv[2], r.uv[3] },
        {  0.5f, -0.5f, r.uv[4], r.uv[5] },
        {  0.5f,  0.5f, r.uv[6], r.uv[7] },
    };
    
    u32 b = gl15_malloc(sizeof(v));
    gl15_memcpy(b, 0, sizeof(v), v);
    gl15_bind_buffer(b);
    gl15_attribute_state(GL_ATTR_V2F_T2F);
    
    for (;!swl_ShouldClose();) {
        if (swl_IsKeyPressed(27)) swl_SendQuitEvent();
        gl15_clear(53, 75, 75, 255);
        
        gl15_bind_buffer(b);
        gl15_bind_texture(t, 0);
        gl15_draw_arrays(GL_QUADS, 0, 4);
        
        swl_GL_SwapBuffers();
        swl_PollEvents();
        swl_PassScheduler();
    }
 
    gl15_delete_texture(t);
    gl15_free(b);
    swl_GL_DestroyContext();
    swl_CloseWindow();
    return 0;
}
```

</details>

<details>
<summary>OpenGL 3.3 Backend</summary>

</details>