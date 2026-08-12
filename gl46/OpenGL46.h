#pragma once

void gl_kaka(void*(*get_proc_address)(const char*));

/*
#define GLCOREARBADDR \

#define X(name, args) void*(*name)args;
    GLCOREARBADDR
#undef X

#define X(name, args) name = get_proc_address(#name);
    GLCOREARBADDR
#undef X
*/