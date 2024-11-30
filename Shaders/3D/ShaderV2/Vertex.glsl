#version 330 core 

layout (location=0) in vec3 position; 
layout (location=1) in vec3 normal; 
layout (location=2) in vec2 a_UV;

out Data {
	vec2 f_UV;
    vec3 fragNormal;
	vec3 fragPos;
	mat4 projection;
	mat4 Model;
} data_out;



uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main() { 
	/*
	vec4 pos = vec4(position,1.0f); 
	vec3 small = vec3(1.0f,1.0f,1.0f) * 0.0001;

	fragNormal = mat3(transpose(inverse(u_Model))) * normalize(normal+ small);
	fragPos = vec3(u_Model * vec4(position+ small,1.0f));

	gl_Position = u_Proj * u_View * u_Model * pos;
	f_UV = a_UV;
	*/
	vec4 pos = vec4(position,1.0f); 
	vec3 small = vec3(0.001f);

	data_out.fragNormal = mat3(transpose(inverse(u_Model))) * normalize(normal+ small);
	data_out.fragPos = vec3(u_Model * vec4(position+ small,1.0f));
	data_out.f_UV =  a_UV;
	data_out.projection = u_Proj  * u_View;
	data_out.Model = u_Model;


	gl_Position =   u_Model * pos;

};
