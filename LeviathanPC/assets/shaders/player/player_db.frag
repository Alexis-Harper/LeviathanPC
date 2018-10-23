#version 150

varying vec4 color;
varying vec2 texCoord;

uniform float damageBoost;
uniform sampler2D tex;

void main (void) {

	float flash = 1.0;
	
	if (damageBoost > 0) {

		flash = (sin (damageBoost) + 2.0) / 3.0;

	}

	gl_FragColor = texture (tex, texCoord) * vec4 (1.0, 1.0, 1.0, flash);

}
