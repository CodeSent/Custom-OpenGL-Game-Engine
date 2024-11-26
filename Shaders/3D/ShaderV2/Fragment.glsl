#version 330 core 

layout (location=0) out vec4 FragColor;

#define MAX_LIGHTS 256

#define enum_POINT_LIGHT 0
#define enum_SPOT_LIGHT 1

struct LightModel {
    uint Type;
    vec3 lColor;
    vec3 Pos;
    vec3 Dir;
    float Am , Diff , Spec;
    float Quadratic, Linear, Constant;
    //float Quadratic, Linear, Constant;
};

struct SunModel {
    vec3 Dir;
    vec3 lColor;
    float Am , Diff , Spec;
    
};

in vec2 f_UV;
in vec3 fragNormal;
in vec3 fragPos;

uniform sampler2D Tex0;
//uniform LightModel Light;
uniform SunModel Sun;

uniform uint total_Lights;
uniform LightModel Lights[MAX_LIGHTS];

uniform vec3 camPos;
uniform float lightInfluence;

vec3 Lerp(vec3 v1, vec3 v2, float a) {
  return v1 + (v2-v1) * a;
}

vec3 getPointLight(vec3 Color,LightModel LightSource) {
    

    vec3 v_Normal = normalize(fragNormal);

    vec3 vAm =   LightSource.lColor * LightSource.Am;
    vec3 vDiff = LightSource.lColor * LightSource.Diff;
    vec3 vSpec = LightSource.lColor * LightSource.Spec;

    vec3 ambient = vAm;

    vec3 lightDir = normalize(LightSource.Pos - fragPos);
    float diff = max(0, dot(lightDir,v_Normal));
    vec3 diffuse = diff * vDiff;

    vec3 viewDir = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(-lightDir,v_Normal);
    float SpecConst = pow(max(dot(viewDir,reflectDir),0),32);
    vec3 specular = SpecConst * vSpec;

    float Dist = length(LightSource.Pos - fragPos);
    float atten = 1.0f /  (LightSource.Constant + (LightSource.Linear * Dist) + (LightSource.Quadratic * (Dist * Dist)));

   

    return Color * (ambient + diffuse + specular) * atten;
}

vec3 getSunLight(vec3 Color) {
    vec3 v_Normal = normalize(fragNormal);

    vec3 vAm = Sun.lColor * Sun.Am;
    vec3 vDiff = Sun.lColor * Sun.Diff;
    vec3 vSpec = Sun.lColor * Sun.Spec;

    vec3 ambient = vAm;

    vec3 lightDir = normalize(Sun.Dir);
    float diff = max(0, dot(lightDir,v_Normal));
    vec3 diffuse = diff * vDiff;

    vec3 viewDir = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(-lightDir,v_Normal);
    float SpecConst = pow(max(dot(viewDir,reflectDir),0),32);
    vec3 specular = SpecConst * vSpec;

    return Color * (ambient+ diffuse + specular);
}

vec3 getSpotLight(vec3 Color,LightModel LightSource) {
    float outerCone = 0.90f;
    float innerCone = 0.95f;

    vec3 v_Normal = normalize(fragNormal);

    vec3 vAm =   LightSource.lColor * LightSource.Am;
    vec3 vDiff = LightSource.lColor * LightSource.Diff;
    vec3 vSpec = LightSource.lColor * LightSource.Spec;

    vec3 ambient = vAm;

    vec3 lightDir = normalize(LightSource.Pos - fragPos);
    float diff = max(0, dot(lightDir,v_Normal));
    vec3 diffuse = diff * vDiff;

    vec3 viewDir = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(-lightDir,v_Normal);
    float SpecConst = pow(max(dot(viewDir,reflectDir),0),32);
    vec3 specular = SpecConst * vSpec;

    float Dist = length(LightSource.Pos - fragPos);
    float atten = 1.0f /  (LightSource.Constant + (LightSource.Linear * Dist) + (LightSource.Quadratic * (Dist * Dist)));

    float angle = dot(normalize(LightSource.Dir),-lightDir);
    float inten = clamp((angle - outerCone)/(innerCone-outerCone),0.0f,1.0f);

    return Color * (ambient + (diffuse * inten) + (specular * inten)) * atten;
}


void main()
{
    float Gamma = 2.2f;
    vec3 texColor = texture(Tex0,f_UV).rgb;

    texColor = pow(texColor,vec3(Gamma));
    vec3 color = getSunLight(texColor);
   // color += getPointLight(color,Light);

    for (uint i = 0; i < total_Lights ; i++) {
        LightModel selLight = Lights[i];
        switch(selLight.Type) {

        case enum_POINT_LIGHT:
            color += getPointLight(color,selLight);
        case enum_SPOT_LIGHT:
            color += getSpotLight(color,selLight);
        default:
            break;
        }
        
    }

   color = pow(color,1/vec3(Gamma));

    vec3 finalColor = Lerp(texColor,color,lightInfluence);

    

    FragColor = vec4(finalColor,1.0f);
};