#version 150

varying vec4 color;
varying vec2 texCoord;

uniform sampler2D tex;

void main (void) {

	gl_FragColor = texture (tex, texCoord);

}
