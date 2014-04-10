#version 130
attribute vec4 position;
smooth out vec4 theColor;
void main()
{
	gl_Position = position;
	theColor = vec4(1.0, 0, 0, 1);
}
