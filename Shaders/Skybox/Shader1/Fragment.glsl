#version 330 core 

out vec4 FragColor;

in vec4 clipCoord;

uniform samplerCube u_texture_skybox;
uniform mat4 m_invProjView;
uniform vec3 SunDir;

vec4 Lerp(vec4 v1, vec4 v2, float a) {
  return v1 + (v2-v1) * a;
}

void main()
{
    float SunInten = clamp( dot(vec3(0.0f,1.0f,0.0f),normalize(SunDir)),0.0f,1.0f);

    vec4 worldCoord = m_invProjView *clipCoord;
    vec3 texCubeCoord = normalize(worldCoord.xyz/worldCoord.w);

    vec4 skyFragCol = texture(u_texture_skybox,texCubeCoord);
    FragColor = Lerp(vec4(0.0f),skyFragCol,SunInten);
};