#ifndef TRIANGULO_H_INCLUDED
#define TRIANGULO_H_INCLUDED

#include <glm/vec2.hpp>

namespace hgs{

class VaoInfo;

namespace Triangulo{

    VaoInfo getVaoInfo();
    VaoInfo getVaoInfo(const glm::vec2& t1, const glm::vec2& t2, const glm::vec2& t3);

};



}

#endif // TRIANGULO_H_INCLUDED
