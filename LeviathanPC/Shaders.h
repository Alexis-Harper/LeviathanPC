#pragma once

/**
 * Author:    Alexis Harper
 * Created:   19.10.2018
 *
 * Description: Shaders.h has functions and structs that handle the dirty work
 *              in loading up GLSL shaders allowed from SDL_gpu. This loads up
 *              shaders from file and has a struct block to store all needed 
 *              values to load and free shaders.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

//Forward declaration to be used in function declarations
struct ShaderProgram;

//Creates shader program from files
GPU_ShaderBlock loadShaderProgram (const char *vertexFile, const char *fragmentFile, Uint32 *vertex, Uint32 *fragment, Uint32 *program);

//Creates struct program from files
ShaderProgram loadShaderProgram (const char *vertexFile, const char *fragmentFile);

//Free shader program
void freeShaderProgram (Uint32 vertex, Uint32 fragment, Uint32 program);

//Free struct program
void freeShaderProgram (ShaderProgram program);

//Holds shader pointers
struct ShaderProgram {

	Uint32 vertex;
	Uint32 fragment;
	Uint32 program;
	GPU_ShaderBlock block;

};
