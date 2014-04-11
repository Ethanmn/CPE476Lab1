#version 130
attribute vec4 aPosition;
smooth out vec4 theColor;
void main()
{
   gl_Position = aPosition;
   theColor = vec4(1.0, 0, 0, 1);
}
