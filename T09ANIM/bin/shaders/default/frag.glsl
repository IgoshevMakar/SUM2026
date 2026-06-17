/**/
#version 330

layout(location = 0) out vec4 OutColor;
 
in vec4 DrawColor;
ut vec3 DrawNormal;
 
void main( void )
{
  OutColor = DrawColor;

  vec3 N = normalize(DrawNormal);

  OutColor = vec4(N, 1 );
}