#ifndef ATENUACION_H_INCLUDED
#define ATENUACION_H_INCLUDED


namespace hgs{

struct Atenuacion{

    float constant;
    float linear;
    float quadratic;

    Atenuacion(float constant, float linear, float quadratic)
    : constant(constant), linear(linear), quadratic(quadratic){}

};


}


#endif // ATENUACION_H_INCLUDED
