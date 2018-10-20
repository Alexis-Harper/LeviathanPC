#pragma once

struct ShaderProgram;

//Creates shader program from files
GPU_ShaderBlock loadShaderProgram (const char *vertexFile, const char *fragmentFile, Uint32 *vertex, Uint32 *fragment, Uint32 *program);

//Creates struct program from files
ShaderProgram loadShaderProgram (const char *vertexFile, const char *fragmentFile);

//Free shader program
void freeShaderProgram (Uint32 vertex, Uint32 fragment, Uint32 program);

//Free struct program
void freeShaderProgram (ShaderProgram program);

struct ShaderProgram {

	Uint32 vertex;
	Uint32 fragment;
	Uint32 program;
	GPU_ShaderBlock block;

};
