#version 130
uniform mat4 uProjectionMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uNormalMatrix;

attribute vec3 aPosition;
attribute vec3 aNormal;
smooth out vec4 theColor;
void main()
{
   gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aPosition, 1);
   theColor = normalize(uNormalMatrix * vec4(aNormal, 0));
}
