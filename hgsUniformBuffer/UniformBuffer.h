#ifndef UNIFORMBUFFER_H_INCLUDED
#define UNIFORMBUFFER_H_INCLUDED

#define HGS_SIZE_MAT4           64
#define HGS_SIZE_FLOAT          4
#define HGS_SIZE_INT            4
#define HGS_SIZE_BOOL           4
#define HGS_SIZE_VEC2           8
#define HGS_SIZE_VEC3           12
#define HGS_SIZE_VEC4           16
#define HGS_SIZE_ARRAY_ELEMENT  16

#define HGS_ALLIGNMENT_MAT4           16
#define HGS_ALLIGNMENT_FLOAT          4
#define HGS_ALLIGNMENT_INT            4
#define HGS_ALLIGNMENT_BOOL           4
#define HGS_ALLIGNMENT_VEC2           8
#define HGS_ALLIGNMENT_VEC3           16
#define HGS_ALLIGNMENT_VEC4           16
#define HGS_ALLIGNMENT_ARRAY_ELEMENT  16

#include <memory>

class UniformBuffer{

    protected:

        std::shared_ptr<unsigned> ubo;
        unsigned int bindPoint;


    public:

        UniformBuffer(unsigned int bytes, unsigned int bindPoint);
        unsigned int getBindPoint();

};

inline unsigned int UniformBuffer::getBindPoint(){
    return this->bindPoint;
}



#endif // UNIFORMBUFFER_H_INCLUDED
