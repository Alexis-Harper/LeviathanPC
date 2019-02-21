#version 150

varying vec4 color;
varying vec2 texCoord;

uniform float damageBoost;
uniform sampler2D tex;

void main (void) {

	vec4 flash = vec4 (1.0, 1.0, 1.0, 1.0);
	
	if (damageBoost > 0.0) {

		flash.a = (sin (damageBoost) + 2.0) / 3.0;

	}

	gl_FragColor = texture (tex, texCoord) * flash;

}
