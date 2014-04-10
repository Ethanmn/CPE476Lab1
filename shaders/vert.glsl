#version 130
attribute vec4 position;
attribute vec4 color;
smooth out vec4 theColor;
void main()
{
	gl_Position = position;
	theColor = color;
}
