#version 130
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

attribute vec3 aPosition;
smooth out vec4 theColor;
void main()
{
   gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPosition.xyz, 1);
   theColor = vec4(1.0, 0, 0, 1);
}
