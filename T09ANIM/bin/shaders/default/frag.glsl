#version 330

layout(location = 0) out vec4 OutColor;
 
in vec4 DrawColor;
 
void main( void )
{
  OutColor = DrawColor;
}