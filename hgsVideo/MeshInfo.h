#ifndef MESHINFO_H_INCLUDED
#define MESHINFO_H_INCLUDED

#include <string>
#include <vector>
#include "VaoInfo.h"
#include "../hgsMaterial/Material.h"
#include "Vertex.h"


namespace hgs{

struct MeshInfo{

    std::string MeshName;
    VaoInfo vaoInfo;
    Material MeshMaterial;

    MeshInfo();
    template<class VAOINFO>
    MeshInfo(VAOINFO&& vaoInfo);
    template<class VAOINFO>
    MeshInfo(VAOINFO&& vaoInfo, const Material& material);

};

inline MeshInfo::MeshInfo(){}

template<class VAOINFO>
inline MeshInfo::MeshInfo(VAOINFO&& vaoInfo)
: vaoInfo(std::forward<VAOINFO>(vaoInfo)){}

template<class VAOINFO>
inline MeshInfo::MeshInfo(VAOINFO&& vaoInfo, const Material& material)
: vaoInfo(std::forward<VAOINFO>(vaoInfo)), MeshMaterial(material){}



}

#endif // MESHINFO_H_INCLUDED
