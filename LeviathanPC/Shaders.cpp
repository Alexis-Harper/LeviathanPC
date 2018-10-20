#include "stdafx.h"
#include "Shaders.h"

#include "ErrorEnum.h"

GPU_ShaderBlock loadShaderProgram (const char *vert, const char *frag, Uint32 *v, Uint32 *f, Uint32 *p) {

	//Load vertex shader
	*v = GPU_LoadShader (GPU_VERTEX_SHADER, vert);

	if (!*v) {

		std::cout << "[-] GPU: " << GPU_GetErrorString (GPU_PopErrorCode ().error) << "\n";

		exit (ERROR_GPU_SHADER_LOAD_V);

	}

	//Load fragment shader
	*f = GPU_LoadShader (GPU_FRAGMENT_SHADER, frag);

	if (!*f) {

		std::cout << "[-] GPU: " << GPU_GetErrorString (GPU_PopErrorCode ().error) << "\n";

		exit (ERROR_GPU_SHADER_LOAD_F);

	}

	//Link shaders
	*p = GPU_LinkShaders (*v, *f);

	if (!*p) {

		std::cout << "[-] GPU: " << GPU_GetErrorString (GPU_PopErrorCode ().error) << "\n";

		exit (ERROR_GPU_SHADER_LINK);

	} 

	//Build block
	GPU_ShaderBlock block = GPU_LoadShaderBlock (*p, "gpu_Vertex", "gpu_TexCoord", "gpu_Color", "gpu_ModelViewProjectionMatrix");
	
	//Activate program
	GPU_ActivateShaderProgram (*p, &block);

	//Return
	return block;

}

ShaderProgram loadShaderProgram (const char *vertexFile, const char *fragmentFile) {

	struct ShaderProgram ret;

	ret.block = loadShaderProgram (vertexFile, fragmentFile, &ret.vertex, &ret.fragment, &ret.program);

	return ret;

}

void freeShaderProgram (Uint32 vertex, Uint32 fragment, Uint32 program) {

	GPU_FreeShader (vertex);
	GPU_FreeShader (fragment);
	GPU_FreeShaderProgram (program);

}

void freeShaderProgram (ShaderProgram program) {

	freeShaderProgram (program.vertex, program.fragment, program.program);

}
