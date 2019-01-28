#version 150

varying vec4 color;
varying vec2 texCoord;

uniform float damageBoost;
uniform float sprintCounter;
uniform sampler2D tex;

void main (void) {

	vec4 sprint = vec4 (1.0, 1.0, 1.0, 1.0);
	vec4 flash = vec4 (1.0, 1.0, 1.0, 1.0);
	
	if (sprintCounter > 25.0) {
		
		float gbColor = (sin (sprintCounter) + 2.0) / 3.0;

		//sprint.r = gbColor;
		sprint.g = gbColor;
		sprint.b = gbColor;
		
	} else if (damageBoost > 0.0) {

		flash.a = (sin (damageBoost) + 2.0) / 3.0;

	}

	gl_FragColor = texture (tex, texCoord) * sprint * flash;

}
