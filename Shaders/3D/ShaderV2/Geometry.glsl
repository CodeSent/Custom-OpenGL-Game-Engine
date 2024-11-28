#version 330 core

layout (triangles) in;
layout (triangle_strip,max_vertices = 3) out;

out vec2 f_UV;
out vec3 fragNormal;
out vec3 fragPos;
out mat3 fragTBN;



in Data {
	vec2 f_UV;
    vec3 fragNormal;
	vec3 fragPos;
	mat4 projection;
	mat4 Model;
} data_in[];

void defVertex(uint Index) {
	gl_Position = data_in[Index].projection * gl_in[Index].gl_Position;
	fragNormal = data_in[Index].fragNormal;
	fragPos = data_in[Index].fragPos;
	f_UV = data_in[Index].f_UV;
	EmitVertex();
}


void main() {
	vec3 edge0 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 edge1 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;

	vec2 deltaUV0 = data_in[1].f_UV - data_in[0].f_UV;
	vec2 deltaUV1 = data_in[2].f_UV - data_in[0].f_UV;

	float invDet = 1.0f/(deltaUV0.x * deltaUV1.y - deltaUV0.y * deltaUV1.x);

	vec3 tangent = vec3(invDet * (deltaUV1.y * edge0 - deltaUV0.y * edge1));
	vec3 bitangent = vec3(invDet * (-deltaUV1.x * edge0 + deltaUV0.x * edge1));

	vec3 T = normalize(vec3(data_in[0].Model * vec4(tangent,1.0f)));
	vec3 B = normalize(vec3(data_in[0].Model * vec4(bitangent,1.0f)));
	vec3 N = normalize(vec3(data_in[0].Model * vec4(cross(edge1,edge0),0.0f)));

	mat3 TBN = mat3(T,B,N);
	mat3 inv_TBN = TBN;

	gl_Position = data_in[0].projection * gl_in[0].gl_Position;
	fragNormal = data_in[0].fragNormal;
	fragPos = data_in[0].fragPos;
	f_UV = data_in[0].f_UV;
	fragTBN = inv_TBN;
	EmitVertex();
	gl_Position = data_in[1].projection * gl_in[1].gl_Position;
	fragNormal = data_in[1].fragNormal;
	fragPos = data_in[1].fragPos;
	f_UV = data_in[1].f_UV;
	fragTBN = inv_TBN;
	EmitVertex();
	gl_Position = data_in[2].projection * gl_in[2].gl_Position;
	fragNormal = data_in[2].fragNormal;
	fragPos = data_in[2].fragPos;
	f_UV = data_in[2].f_UV;
	fragTBN = inv_TBN;
	EmitVertex();
	EndPrimitive();
}