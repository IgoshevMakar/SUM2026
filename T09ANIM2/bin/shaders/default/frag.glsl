/**/
#version 330

layout(location = 0) out vec4 OutColor;
 
in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;
in vec2 DrawTexCoord;

uniform float Time, GlobalTime;
uniform vec3 Ka, Kd, Ks;
uniform float Ph;
uniform int IsTexture0;
uniform sampler2D Texture0;
 
void main( void )
{
  vec3 L = normalize(vec3(10 * sin(8 *Time), 1, 1));
  vec3 L1 = normalize(vec3(1, 1, 10 * sin(5 * Time)));
  vec3 N = normalize(DrawNormal);
  
  float diff = max(max(dot(N, L), 0.0), dot(N, L1));
  vec3 V = normalize(-DrawPos);
  vec3 H = normalize(L + V);
  float spec = pow(max(dot(N, H), 0.0), Ph);

  vec4 texColor = vec4(1,1,0.3, 1);
  if (IsTexture0 == 1)
    texColor = texture(Texture0, vec2(1, -1) * DrawTexCoord);

  vec3 color = Ka + Kd * diff + Ks * spec;
  OutColor = texColor * vec4(color, 1.0) * DrawColor;
}