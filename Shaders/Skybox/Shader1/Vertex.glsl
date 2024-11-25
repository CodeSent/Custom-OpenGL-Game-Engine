#version 330 core 

layout (location=0) in vec3 position; 

out vec4 clipCoord;

void main() { 

	gl_Position = vec4(position.xy,0.0f,1.0f); 
	clipCoord = gl_Position;
};
