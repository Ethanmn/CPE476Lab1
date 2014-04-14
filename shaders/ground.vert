#version 130
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

attribute vec3 aPosition;
attribute vec3 aNormal;
smooth out vec4 theColor;
void main()
{
   gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPosition.xyz, 1);
   theColor = normalize(uNormalMatrix * vec4(aNormal.xyz, 1));
}
