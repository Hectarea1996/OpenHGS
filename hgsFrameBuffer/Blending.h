#ifndef BLENDING_H_INCLUDED
#define BLENDING_H_INCLUDED

#define HGS_BLENDF_ZERO                         GL_ZERO
#define HGS_BLENDF_ONE                          GL_ONE
#define HGS_BLENDF_SRC_COLOR                    GL_SRC_COLOR
#define HGS_BLENDF_ONE_MINUS_SRC_COLOR          GL_ONE_MINUS_SRC_COLOR
#define HGS_BLENDF_DST_COLOR                    GL_DST_COLOR
#define HGS_BLENDF_ONE_MINUS_DST_COLOR          GL_ONE_MINUS_DST_COLOR
#define HGS_BLENDF_SRC_ALPHA                    GL_SRC_ALPHA
#define HGS_BLENDF_ONE_MINUS_SRC_ALPHA          GL_ONE_MINUS_SRC_ALPHA
#define HGS_BLENDF_DST_ALPHA                    GL_DST_ALPHA
#define HGS_BLENDF_ONE_MINUS_DST_ALPHA          GL_ONE_MINUS_DST_ALPHA
#define HGS_BLENDF_CONSTANT_COLOR               GL_CONSTANT_COLOR
#define HGS_BLENDF_ONE_MINUS_CONSTANT_COLOR     GL_ONE_MINUS_CONSTANT_COLOR
#define HGS_BLENDF_CONSTANT_ALPHA               GL_CONSTANT_ALPHA
#define HGS_BLENDF_ONE_MINUS_CONSTANT_ALPHA     GL_ONE_MINUS_CONSTANT_ALPHA

#define HGS_BLENDEQ_ADD                         GL_FUNC_ADD
#define HGS_BLENDEQ_SUBTRACT                    GL_FUNC_SUBTRACT
#define HGS_BLENDEQ_REVERSE_SUBTRACT            GL_FUNC_REVERSE_SUBTRACT


namespace Blending{

    void activar();
    void desactivar();
    void setBlendColorConstant(float red,float green, float blue, float alpha);
    void setBlendFunction(unsigned int HGS_BLENDFACTOR_s, unsigned int HGS_BLENDFACTOR_d);
    void setBlendFunctionSeparate(unsigned int HGS_BLENDF_sRGB, unsigned int HGS_BLENDF_dRGB,
                                    unsigned int HGS_BLENDF_sA, unsigned int HGS_BLENDF_dA);
    void setBlendEquation(unsigned int HGS_BLENDEQ);
    void setBlendEquationSeparate(unsigned int HGS_BLENDEQ_RGB, unsigned int HGS_BLENDEQ_A);

};


inline void Blending::activar(){
    glEnable(GL_BLEND);
}

inline void Blending::desactivar(){
    glDisable(GL_BLEND);
}

inline void Blending::setBlendColorConstant(float red,float green, float blue, float alpha){
    glBlendColor(red,green,blue,alpha);
}

inline void Blending::setBlendFunction(unsigned int HGS_BLENDFACTOR_s, unsigned int HGS_BLENDFACTOR_d){
    glBlendFunc(HGS_BLENDFACTOR_s,HGS_BLENDFACTOR_d);
}

inline void Blending::setBlendFunctionSeparate(unsigned int HGS_BLENDF_sRGB, unsigned int HGS_BLENDF_dRGB,
                                                    unsigned int HGS_BLENDF_sA, unsigned int HGS_BLENDF_dA){
    glBlendFuncSeparate(HGS_BLENDF_sRGB,HGS_BLENDF_dRGB,HGS_BLENDF_sA,HGS_BLENDF_dA);
}

inline void Blending::setBlendEquation(unsigned int HGS_BLENDEQ){
    glBlendEquation(HGS_BLENDEQ);
}

inline void Blending::setBlendEquationSeparate(unsigned int HGS_BLENDEQ_RGB, unsigned int HGS_BLENDEQ_A){
    glBlendEquationSeparate(HGS_BLENDEQ_RGB,HGS_BLENDEQ_A);
}


#endif // BLENDING_H_INCLUDED
