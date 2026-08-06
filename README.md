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
#include "gfx-backends/gl15/gl15.h"
#define CUI_IMPL
#include "c-ui/cui.h"

int main() {
    swl_CreateWindow("X", 400, 300);
    swl_GL_CreateContext(1, 5, 24, 8);
    gl15_setup(swl_GL_GetProcAddress);
    
    unsigned int tex[] = {
        0xFFFF00FF, //ABGR
        0xFF00FF00, //ABGR
    };
    u32 t = gl15_texture_create(2, 1, tex);
    gl15_texture_nearest(t);

    cui_set_surface_info(400, 300);
    cui_set_texture_info(2, 1);

    u32 b = gl15_buffer_create(sizeof(float) * 16);
    gl15_buffer_memcpy(b, 0, sizeof(float) * 16, cui_get_tile(0, 0, 50, 50, 0, 0, 2, 1).v);
    gl15_buffer_bind(b);
    
    gl15_vertex_v2f_t2f();
    gl15_texture_unit(t, 0);
    
    for (;!swl_ShouldClose();) {
        if (swl_IsKeyPressed(27)) swl_SendQuitEvent();
        gl15_clear(53, 75, 75, 255);
        
        gl15_buffer_bind(b);
        gl15_draw_arrays(GL_QUADS, 0, 4);
        
        swl_GL_SwapBuffers();
        swl_PollEvents();
        swl_PassScheduler();
    }
 
    gl15_texture_delete(t);
    gl15_buffer_delete(b);
    swl_GL_DestroyContext();
    swl_CloseWindow();
    return 0;
}
```

</details>

<details>
<summary>OpenGL 3.3 Backend</summary>

</details>