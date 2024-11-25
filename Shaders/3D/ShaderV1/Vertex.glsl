#version 330 core 

layout (location=0) in vec3 position; 
layout (location=1) in vec3 normal; 
layout (location=2) in vec2 a_UV;

out vec2 f_UV;

//uniform mat4 um_mat;
//uniform mat4 ucam_mat;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main() { 
	vec4 pos = vec4(position,1.0f); 
	gl_Position = u_Proj * u_View * u_Model * pos;
	//gl_Position =  ucam_mat * um_mat * pos;
	//gl_Position = pos;
	f_UV = a_UV;
};
