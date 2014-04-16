#version 130
uniform mat4 uProjectionMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uNormalMatrix;

uniform float uBlue;

attribute vec3 aPosition;
attribute vec3 aNormal;
smooth out vec4 theColor;
void main()
{
   gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aPosition, 1);
   theColor = normalize(vec4(1 - uBlue, 0, uBlue, 1) + 0.5f * normalize(uNormalMatrix * vec4(aNormal, 0)));
}
