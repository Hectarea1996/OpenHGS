#ifndef MATERIALFACTORY_H_INCLUDED
#define MATERIALFACTORY_H_INCLUDED

#include "material.h"
#include <glm/glm.hpp>

namespace hgs{

namespace MaterialFactory{

    inline static Material esmeralda(){
        return Material(glm::vec3(0.0215,0.1745,0.0215),glm::vec3(0.07568,0.61424,0.07568),glm::vec3(0.633,0.727811,0.633),0.6*128);
    }

    inline static Material jade(){
        return Material(glm::vec3(0.135,0.2225,0.1575),glm::vec3(0.54,0.89,0.63),glm::vec3(0.316228,0.316228,0.316228),0.1*128);
    }

    inline static Material obsidiana(){
        return Material(glm::vec3(0.05375,0.05,0.06625),glm::vec3(0.18275,0.17,0.22525),glm::vec3(0.332741,0.328634,0.346435),0.3*128);
    }

    inline static Material perla(){
        return Material(glm::vec3(0.25,0.20725,0.20725),glm::vec3(1,0.829,0.829),glm::vec3(0.296648,0.296648,0.296648),0.088*128);
    }

    inline static Material rubi(){
        return Material(glm::vec3(0.1745,0.01175,0.01175),glm::vec3(0.61424,0.04136,0.04136),glm::vec3(0.727811,0.626959,0.626959),0.6*128);
    }

    inline static Material turquesa(){
        return Material(glm::vec3(0.1,0.18725,0.1745),glm::vec3(0.396,0.74151,0.69102),glm::vec3(0.297254,0.30829,0.306678),0.1*128);
    }

    inline static Material laton(){
        return Material(glm::vec3(0.329412,0.223529,0.027451),glm::vec3(0.780392,0.568627,0.113725),glm::vec3(0.992157,0.941176,0.807843),0.21794872*128);
    }

    inline static Material bronce(){
        return Material(glm::vec3(0.2125,0.1275,0.054),glm::vec3(0.714,0.4284,0.18144),glm::vec3(0.393548,0.271906,0.166721),0.2*128);
    }

    inline static Material cromo(){
        return Material(glm::vec3(0.25,0.25,0.25),glm::vec3(0.4,0.4,0.4),glm::vec3(0.774597,0.774597,0.774597),0.6*128);
    }

}

}

#endif // MATERIALFACTORY_H_INCLUDED
