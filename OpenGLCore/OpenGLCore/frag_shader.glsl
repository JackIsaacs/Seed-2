#version 400 core
out vec4 color;

in vec4 in_color;
 
void main(void)
{
  color = in_color;
}