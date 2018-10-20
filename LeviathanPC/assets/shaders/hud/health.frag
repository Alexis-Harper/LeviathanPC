#version 150

varying vec4 color;
varying vec2 texCoord;
varying float healthFloat;

uniform sampler2D tex;
uniform float health;

void main (void) {

	vec4 texColor = texture (tex, texCoord);

	if (texColor.x <= health) {

		texColor = vec4 (1.0, 0.0, 0.0, 0.8);

	} else {

		texColor = vec4 (0.0, 0.0, 0.0, 0.0);

	}

	gl_FragColor = texColor;

}
