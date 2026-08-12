#include "igl.h"

/*
- ayır!
+ neyi?
- performanstan ödün verebileceklerini.
+ ama ne için?
- fonksiyon sayısını azaltmalısın.
+ nelerden ödün verebilirim ve nasıl vermeliyim?
- başlangıç ve bitiş fonksiyonlarında performans payı var.
+ nasıl olacak bu?
- switch case + enum kullanarak
+ ah şimdi anladım.
*/

#ifndef PRINTF
    #include <stdio.h>
    #define PRINTF(fmt, ...) printf(fmt, __VA_ARGS__)
#endif

#define GL_FUNCTIONS \
    X(glClear, (int)) \
    X(glClearColor, (float, float, float, float)) \
    X(glDrawArrays, (int, int, int)) \
    X(glGetIntegerv, (int, int*)) \
    X(glGetString, (int)) \
    X(glCreateShader, (int)) \
    X(glShaderSource, (unsigned, int, const char**, int*)) \
    X(glCompileShader, (unsigned)) \
    X(glCreateProgram, ()) \
    X(glGetShaderiv, (unsigned, int, int*)) \
    X(glAttachShader, (unsigned, unsigned)) \
    X(glLinkProgram, (unsigned)) \
    X(glDetachShader, (unsigned, unsigned)) \
    X(glGetShaderInfoLog, (int, int, void*, char*)) \
    X(glDeleteShader, (unsigned)) \
    X(glDeleteProgram, (unsigned)) \
    X(glGetProgramInfoLog, (int, int, void*, char*)) \
    X(glUseProgram, (unsigned)) \
    X(glGetProgramiv, (unsigned, int, int*)) \
    X(glReleaseShaderCompiler, ()) \
    X(glGenTextures, (int, unsigned*)) \
    X(glDeleteTextures, (int, unsigned*)) \
    X(glTexParameteri, (int, int, int)) \
    X(glTexImage2D, (int, int, int, int, int, int, int, int, const void*)) \
    X(glTexSubImage2D, (int, int, int, int, int, int, int, int, const void*)) \
    X(glBindTexture, (int, unsigned)) \
    X(glGetUniformLocation, (unsigned, const char*)) \
    X(glUniform1i, (int, int)) \
    X(glActiveTexture, (int))

#define X(name, args) void*(*name)args;
    GL_FUNCTIONS
#undef X

static void __id_initapiprops();
void id_Setup(void *(*get_proc_address)(const char *)) {
    void *(*id_get_proc)(const char*) = get_proc_address;
    unsigned vao;
    ((void(*)(int, unsigned*))id_get_proc("glGenVertexArrays"))(1, &vao);
    ((void(*)(int))id_get_proc("glBindVertexArray"))(vao);

    #define X(name, args) name = id_get_proc(#name);
        GL_FUNCTIONS
    #undef X

    __id_initapiprops();
}

unsigned id_CreateShaderProgram(const char *vert, const char *frag) {
    unsigned p, v, f;
    int success;
    char infoLog[1024];

    v = (unsigned long long)glCreateShader(0x8B31);
    glShaderSource(v, 1, &vert, (void*)0);
    glCompileShader(v);

    glGetShaderiv(v, 0x8B81, &success);
    if (!success) {
        glGetShaderInfoLog(v, 1024, (void*)0, infoLog);
        PRINTF("HATA::VERTEX_SHADER_DERLEME_BASARISIZ\n%s\n", infoLog);
        glDeleteShader(v);
        return 0;
    }

    f = (unsigned long long)glCreateShader(0x8B30);
    glShaderSource(f, 1, &frag, (void*)0);
    glCompileShader(f);

    glGetShaderiv(f, 0x8B81, &success);
    if (!success) {
        glGetShaderInfoLog(f, 1024, (void*)0, infoLog);
        PRINTF("HATA::FRAGMENT_SHADER_DERLEME_BASARISIZ\n%s\n", infoLog);
        glDeleteShader(v);
        glDeleteShader(f);
        return 0;
    }

    p = (unsigned long long)glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);
    
    glGetProgramiv(p, 0x8B82, &success);
    if (!success) {
        glGetProgramInfoLog(p, 1024, (void*)0, infoLog);
        PRINTF("HATA::SHADER_PROGRAM_LINKLEME_BASARISIZ\n%s\n", infoLog);
        glDeleteShader(v);
        glDeleteShader(f);
        glDeleteProgram(p);
        return 0;
    }

    glDeleteShader(v);
    glDeleteShader(f);

    return p;
}

void id_DeleteShaderProgram(unsigned id) {
    glDeleteProgram(id);
}

void id_BindShaderProgram(unsigned id) {
    glUseProgram(id);
}

void id_ReleaseShaderCompiler() {
    glReleaseShaderCompiler();
}

unsigned id_CreateTexelBuffer(int type, int width, int height, const void* data) {
    int internal_format, format, data_type;

    if (type == ID_TEXEL_INT) {
        internal_format = 0x8D82; // GL_RGBA32I (32-bit Integer)
        format          = 0x8D99; // GL_RGBA_INTEGER (Int yollanacağını belirtir)
        data_type       = 0x1404; // GL_INT
    } 
    else if (type == ID_TEXEL_UINT) {
        internal_format = 0x8D70; // GL_RGBA32UI (32-bit Unsigned Int)
        format          = 0x8D99; // GL_RGBA_INTEGER
        data_type       = 0x1405; // GL_UNSIGNED_INT
    } 
    else {
        internal_format = 0x8814; // GL_RGBA32F (32-bit Float)
        format          = 0x1908; // GL_RGBA
        data_type       = 0x1406; // GL_FLOAT
    }

    unsigned tex;
    glGenTextures(1, &tex);
    glBindTexture(0x0DE1, tex);

    glTexParameteri(0x0DE1, 0x813C, 0); 
    glTexParameteri(0x0DE1, 0x813D, 0); 
    glTexParameteri(0x0DE1, 0x2801, 0x2600);
    glTexParameteri(0x0DE1, 0x2800, 0x2600);
    glTexParameteri(0x0DE1, 0x2802, 0x812F); // GL_CLAMP_TO_EDGE (0x812F)
    glTexParameteri(0x0DE1, 0x2803, 0x812F);

    glTexImage2D(0x0DE1, 0, internal_format, width, height, 0, format, data_type, data);

    glBindTexture(0x0DE1, 0);
    return tex;
}

void id_BindTexelBuffer(unsigned id, int slot) {
    glActiveTexture(0x84C0 + slot); // GL_TEXTURE0 0x84C0
    glBindTexture(0x0DE1, id);
}

void id_UpdateTexelBuffer(int type, unsigned id, int x_offset, int y_offset, int width, int height, const void *data) {
    int format, data_type;

    if (type == ID_TEXEL_INT) {
        format    = 0x8D99; // GL_RGBA_INTEGER
        data_type = 0x1404; // GL_INT
    } 
    else if (type == ID_TEXEL_UINT) {
        format    = 0x8D99; // GL_RGBA_INTEGER
        data_type = 0x1405; // GL_UNSIGNED_INT
    } 
    else { // FLOAT
        format    = 0x1908; // GL_RGBA
        data_type = 0x1406; // GL_FLOAT
    }

    glBindTexture(0x0DE1, id); 
    glTexSubImage2D(0x0DE1, 0, x_offset, y_offset, width, height, format, data_type, data);
}

void id_DeleteTexelBuffer(unsigned id) {
    glDeleteTextures(1, &id);
}

void id_SetShaderTexelBuffer(unsigned shader_id, const char *name, int slot) {
    id_BindShaderProgram(shader_id);
    glUniform1i((int)glGetUniformLocation(shader_id, name), slot);
    id_BindShaderProgram(0);
}

void id_DrawArrays(int vertex_offset, int vertex_count) {
    glDrawArrays(0x0004, vertex_offset, vertex_count);
}

void id_Clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    float rf = r/255.0f;
    float gf = g/255.0f;
    float bf = b/255.0f;
    float af = a/255.0f;
    glClearColor(rf, gf, bf, af);
    glClear(0x00004000);
}

static id_api_props_t p;
static void __id_initapiprops() {
    p.Device.Vendor = (const char*)glGetString(0x1F00);
    p.Device.Renderer = (const char*)glGetString(0x1F01);    
    glGetIntegerv(0x0D33,&p.Texture.MaxSize);
}
const id_api_props_t* id_GetAPIProps() { return &p; }