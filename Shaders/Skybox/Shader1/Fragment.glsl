#version 330 core 

out vec4 FragColor;

in vec4 clipCoord;

uniform samplerCube u_texture_skybox;
uniform mat4 m_invProjView;


void main()
{
    
    vec4 worldCoord = m_invProjView *clipCoord;
    vec3 texCubeCoord = normalize(worldCoord.xyz/worldCoord.w);
    FragColor = texture(u_texture_skybox,texCubeCoord);
};