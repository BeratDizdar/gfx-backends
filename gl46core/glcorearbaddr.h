#pragma once
#include <stdint.h>
#include <stddef.h>

#define GLCOREARBADDR_CLEAR \
    X(glClear, (uint32_t)) \
    X(glClearColor, (float, float, float, float))

#define GLCOREARBADDR_BUFFERS \
    X(glCreateBuffers, (int32_t, uint32_t*)) \
    X(glBindBufferBase, (uint32_t, uint32_t, uint32_t)) \
    X(glNamedBufferStorage, (uint32_t, size_t, const void*, uint32_t)) \
    X(glNamedBufferSubData, (uint32_t, size_t, size_t, const void*)) \
    X(glMapNamedBufferRange, (uint32_t, intptr_t, size_t, uint32_t)) \
    X(glUnmapNamedBuffer, (uint32_t)) \
    X(glDeleteBuffers, (int32_t, const uint32_t*))

#define GLCOREARBADDR_SHADERS \
    X(glCreateShaderProgramv, (uint32_t, size_t, const char**)) \
    X(glGetProgramiv, ()) \
    X(glGetProgramInfoLog, ()) \
    X(glUseProgramStages, ()) \
    X(glDeleteProgram, ()) \
    X(glCreateProgramPipelines, ()) \
    X(glBindProgramPipeline, ()) \
    X(glDeleteProgramPipelines, ())

#define GLCOREARBADDR_COMMANDS \
    X(glDrawArraysInstancedBaseInstance, ())


#define GLCOREARBADDR \
    GLCOREARBADDR_CLEAR \
    GLCOREARBADDR_BUFFERS \
    GLCOREARBADDR_SHADERS \
    GLCOREARBADDR_COMMANDS

#define X(name, args) void*(*name)args;
    GLCOREARBADDR
#undef X