#pragma once

#define ID_TEXEL_FLOAT 0
#define ID_TEXEL_INT   1
#define ID_TEXEL_UINT  2

void id_Setup(void*(*get_proc_address)(const char*));

unsigned id_CreateShaderProgram(const char *vert, const char *frag);
void id_DeleteShaderProgram(unsigned id);
void id_BindShaderProgram(unsigned id);
void id_ReleaseShaderCompiler();
void id_SetShaderTexelBuffer(unsigned shader_id, const char *name, int sampler_slot);

unsigned id_CreateTexelBuffer(int type, int width, int height, const void *data);
void id_BindTexelBuffer(unsigned id, int sampler_slot);
void id_UpdateTexelBuffer(int type, unsigned id, int x, int y, int w, int h, const void *data);
void id_DeleteTexelBuffer(unsigned id);

unsigned id_CreateTextureArray(int type, int width, int height, const void *data);
void id_DeleteTextureArray(unsigned);
void id_BindTextureArray(unsigned id, int sampler_slot);

void id_DrawArrays(int vertex_offset, int vertex_count);
void id_Clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

typedef struct id_api_props_t {
    struct {
        const char* Vendor;
        const char* Renderer;
        const char* GLVersion;
        const char* GLSLVersion;
    } Device;
    struct {
        int MaxCombinedBlock;
        int MaxBufferBindings;
        int MaxBlockSize;
        int BufferOffsetAlignment;
    } ShaderStorage;
    struct {
        int MaxAttributes;
        int MaxAttributeRelativeOffset;
        int MaxAttributeBindings;
    } VertexBuffer;
    struct {
        int MaxSize;
        int Max3DSize;
        int MaxCubemapSize;
        int MaxTextureImageUnits;
        int MaxArrayLayers;
        int MaxTexelOffset;
        int MaxSamples;
    } Texture;
    struct {
        int MaxFragmentUniform;
        int MaxVertexUniform;
        int MaxVertexTextureImageUnit;
        int MaxCombinedTextureImageUnit;
        int MaxVertexOutComponents;
        int MaxFragmentInComponents;
        int MaxSubroutines;
    } Shader;
    struct {
        int MaxCullDistances;
    } State;
} id_api_props_t;

const id_api_props_t *id_GetAPIProps();