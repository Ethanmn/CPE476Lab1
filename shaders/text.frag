varying vec2 vTexCoord;

uniform sampler2D uTexture;
uniform vec4 uColor;

void main(void) {
   gl_FragColor = vec4(1, 1, 1, texture2D(uTexture, vTexCoord).a) * uColor;
}
