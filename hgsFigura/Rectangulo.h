#ifndef RECTANGULO_H_INCLUDED
#define RECTANGULO_H_INCLUDED

#include <glm/glm.hpp>
#include <array>

namespace hgs{

class VaoInfo;

namespace Rectangulo{

    VaoInfo getVaoInfo();
    VaoInfo getVaoInfo(const std::array<glm::vec2,4>& texCoords);

};

}

#endif // RECTANGULO_H_INCLUDED
