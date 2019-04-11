#ifndef UBOVIEWPOS_H_INCLUDED
#define UBOVIEWPOS_H_INCLUDED

namespace hgs{

template<unsigned int bindValue>
class UboViewPos_impl: public UniformBuffer{

    private:

        UboViewPos_impl();


    public:

        static UboViewPos_impl<bindValue>& getInstancia();
        void setViewPosition(const glm::vec3& view);
        UboViewPos_impl<bindValue>& operator=(const UboViewPos_impl<bindValue>& otro)= delete;

};

template<unsigned int bindValue>
inline UboViewPos_impl<bindValue>::UboViewPos_impl(): UniformBuffer(HGS_SIZE_VEC3,bindValue){}

template<unsigned int bindValue>
inline UboViewPos_impl<bindValue>& UboViewPos_impl<bindValue>::getInstancia(){
    static UboViewPos_impl<bindValue> uboViewPos;
    return uboViewPos;
}

template<unsigned int bindValue>
inline void UboViewPos_impl<bindValue>::setViewPosition(const glm::vec3& viewPos){
    glBindBuffer(GL_UNIFORM_BUFFER,*this->ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,0,HGS_SIZE_VEC3,glm::value_ptr(viewPos));
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}


using UboViewPos= UboViewPos_impl<5>;

}

#endif // UBOVIEWPOS_H_INCLUDED
