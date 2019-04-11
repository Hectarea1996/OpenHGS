
#version 330 core

#define MAX_DIRECCION   5
#define MAX_PUNTO       10
#define MAX_LINTERNA    10

in INFO{
    vec3 fPos;
    vec3 normalVec;
    vec3 viewPos;
    vec4 fPosLight;
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


uniform float far_plane; //Este far_plane pertenece al projection del shadowPunMap.
uniform Material material;
uniform samplerCube skybox;
uniform sampler2D shadowDirMap;
uniform samplerCube shadowPunMap;


float ShadowDirLightCalculation(vec4 fragPosLightSpace, const LuzDireccion luz) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    if (projCoords.z > 1.0)
        return 0.0;
    // get closest depth value from light’s perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowDirMap, projCoords.xy).r;
    // get depth of current fragment from light’s perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    vec3 lightDir= normalize(-luz.direccion);
    float maximumBias= 0.05;
    float minimumBias= 0.005;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowDirMap, 0);
    float bias = max(maximumBias * (1.0 - dot(fs_in.normalVec, lightDir)), minimumBias);
    for(int x = -1; x <= 1; ++x){
        for(int y = -1; y <= 1; ++y){
            float pcfDepth = texture(shadowDirMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}


float ShadowPunLightCalculation(vec3 fragPos, const LuzPunto luz) {
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - luz.position;
    // use the light to fragment vector to sample from the depth map
    float closestDepth = texture(shadowPunMap, fragToLight).r;
    // it is currently in linear range between [0,1]. Re-transform back to original value
    closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // now test for shadows
    float bias = 0.05;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}



vec3 CalcDirLight(const LuzDireccion luz, const vec3 normal, const vec3 viewDir){

    vec3 lightDir= normalize(-luz.direccion);

    float diff= max(dot(normal,lightDir),0.0);

    /* Phong
    vec3 reflectDir= reflect(-lightDir,normal);
    float spec= pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    */

    // Blinn-Phong
    vec3 halfWayDir= normalize(lightDir+viewDir);
    float spec= pow(max(dot(normal,halfWayDir),0.0),material.shininess);

    vec3 ambient= luz.ambient*material.ambient;
    vec3 diffuse= luz.diffuse*diff*material.diffuse;
    vec3 specular= luz.specular*spec*material.specular;

    float shadow= ShadowDirLightCalculation(fs_in.fPosLight,luz);

    return (ambient+(1.0-shadow)*(diffuse+specular));

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

    float shadow = ShadowPunLightCalculation(fs_in.fPos,luz);
    return (ambient+(1.0-shadow)*(diffuse+specular));

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
