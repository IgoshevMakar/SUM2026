/**/
#version 330

layout(location = 0) out vec4 OutColor;
 
in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;
in vec3 DrawPosOrg;

uniform vec3 CamLoc;
uniform float Time, GlobalTime;
uniform vec3 Ka, Kd, Ks;
uniform float Ph;
 
void main( void )
{
 OutColor = vec4(0.5, 0.78, 0.4, 1);
}