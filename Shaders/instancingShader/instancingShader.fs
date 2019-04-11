#version 330 core

#define MAX_DIRECCION   5
#define MAX_PUNTO       10
#define MAX_LINTERNA    10

in INFO{
    vec3 fPos;
    vec3 normalVec;
    vec3 viewPos;
}fs_in;

out vec4 FragColor;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    int illum;
};

struct LuzDireccion{
    vec3 direccion;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct LuzPunto{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct LuzLinterna{
    vec3 position;
    vec3 direccion;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float phiIn;
    float phiOut;
};

layout (std140) uniform LucesDireccion {
    int dirEnc[MAX_DIRECCION];
    LuzDireccion luzDir[MAX_DIRECCION];
};


layout (std140) uniform LucesPunto{
    int punEnc[MAX_PUNTO];
    LuzPunto luzPun[MAX_PUNTO];
};

layout (std140) uniform LucesLinterna{
    int linEnc[MAX_LINTERNA];
    LuzLinterna luzLin[MAX_LINTERNA];
};


uniform Material material;
//uniform int dirEnc[MAX_DIRECCION];
//uniform LuzDireccion luzDir[MAX_DIRECCION];
//uniform int punEnc[MAX_PUNTO];
//uniform LuzPunto luzPun[MAX_PUNTO];
//uniform int linEnc[MAX_LINTERNA];
//uniform LuzLinterna luzLin[MAX_LINTERNA];
uniform samplerCube skybox;

vec3 CalcDirLight(const LuzDireccion luz, const vec3 normal, const vec3 viewDir){

    vec3 lightDir= normalize(-luz.direccion);

    float diff= max(dot(normal,lightDir),0.0);

    vec3 reflectDir= reflect(-lightDir,normal);
    float spec= pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    vec3 ambient= luz.ambient*material.ambient;
    vec3 diffuse= luz.diffuse*diff*material.diffuse;
    vec3 specular= luz.specular*spec*material.specular;

    return ambient+diffuse+specular;

}

vec3 CalcPointLight(const LuzPunto luz, const vec3 normal, const vec3 fragPos, const vec3 viewDir){

    vec3 lightDir= normalize(luz.position-fragPos);

    float diff= max(dot(normal,lightDir),0.0);

    vec3 reflectDir= reflect(-lightDir,normal);
    float spec= pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    float distance= length(luz.position-fragPos);
    float attenuation= 1.0/(luz.constant+luz.linear*distance+luz.quadratic*(distance*distance));

    vec3 ambient= luz.ambient*material.ambient;
    vec3 diffuse= luz.diffuse*diff*material.diffuse;
    vec3 specular= luz.specular*spec*material.specular;

    ambient*= attenuation;
    diffuse*= attenuation;
    specular*= attenuation;

    return (ambient+diffuse+specular);

}

vec3 CalcPlotLight(const LuzLinterna luz, const vec3 normal, const vec3 fragPos, const vec3 viewDir){

    vec3 lightDir= normalize(luz.position-fragPos);
    float theta= dot(lightDir,normalize(-luz.direccion));

    if (theta>luz.phiOut){
        float diff= max(dot(normal,lightDir),0.0);

        vec3 reflectDir= normalize(reflect(-lightDir,normal));
        float spec= pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

        float distance= length(luz.position-fragPos);
        float attenuation= 1.0/(luz.constant+luz.linear*distance+luz.quadratic*(distance*distance));

        float intensity= 1.0;
        if (theta<luz.phiIn){
            float epsilon= luz.phiIn-luz.phiOut;
            intensity= abs((theta-luz.phiOut)/epsilon);
        }

        vec3 ambient= luz.ambient*material.ambient;
        vec3 diffuse= luz.diffuse*diff*material.diffuse;
        vec3 specular= luz.specular*spec*material.specular;

        ambient*= attenuation*intensity;
        diffuse*= attenuation*intensity;
        specular*= attenuation*intensity;

        return (ambient+diffuse+specular);
    }
    else
        return vec3(0.0,0.0,0.0);

}


void main(){

    if (material.illum==3){
        vec3 I = normalize(fs_in.fPos - fs_in.viewPos);
        vec3 R = reflect(I, normalize(fs_in.normalVec));
        FragColor = vec4(texture(skybox, R).rgb, 1.0);
    }
    else if(material.illum==6){
        float ratio = 1.00 / 1.52;
        vec3 I = normalize(fs_in.fPos - fs_in.viewPos);
        vec3 R = refract(I, normalize(fs_in.normalVec), ratio);
        FragColor = vec4(texture(skybox, R).rgb, 1.0);
    }
    else{

        vec3 result= vec3(0.0,0.0,0.0);

        vec3 normal= normalize(fs_in.normalVec);
        vec3 viewDir= normalize(fs_in.viewPos-fs_in.fPos);

        for (int i=0; i<MAX_DIRECCION; i++){
            if (dirEnc[i]!=0)
                result+= CalcDirLight(luzDir[i],normal,viewDir);
        }

        for (int i=0; i<MAX_PUNTO; i++){
            if (punEnc[i]!=0)
                result+= CalcPointLight(luzPun[i],normal,fs_in.fPos,viewDir);
        }

        for (int i=0; i<MAX_LINTERNA; i++){
            if (linEnc[i]!=0)
                result+= CalcPlotLight(luzLin[i],normal,fs_in.fPos,viewDir);
        }

        FragColor= vec4(result,1.0);
    }

}
