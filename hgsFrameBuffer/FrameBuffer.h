#ifndef FRAMEBUFFER_H_INCLUDED
#define FRAMEBUFFER_H_INCLUDED

#include "../OpenHGS.h"
#include "../hgsVideo/Texture.h"
#include "../hgsTemplate/enable_function.h"
#include <memory>
#include <iostream>

#ifndef HGS_RENDERBUFFER_NONE
    #define HGS_RENDERBUFFER_NONE           0
    #define HGS_RENDERBUFFER_DEPTH          1
    #define HGS_RENDERBUFFER_STENCIL        2
    #define HGS_RENDERBUFFER_DEPTH_STENCIL  3
#endif // HGS_RENDERBUFFER_NONE

namespace hgs{


template<unsigned int R>
class FrameBuffer{

    template<unsigned int U>
    friend class FrameBuffer;

    private:

        std::shared_ptr<unsigned> FBO;
        Texture renderTexture;
        unsigned int ancho;
        unsigned int alto;


    public:

        FrameBuffer(unsigned int ancho, unsigned int alto);
        FrameBuffer(unsigned int ancho, unsigned int alto, unsigned int numMSAA);

        template<unsigned int U>
        void blitFrameBuffer(const FrameBuffer<U>& dst);
        void blitToDefaultFrameBuffer(unsigned int ancho, unsigned int alto);

        void usar() const;

        Texture getRenderTexture() const;
        unsigned int getFBO();

};

template<unsigned int R>
struct getVarRender{
    static const unsigned int internalformat= 0;
    static const unsigned int attachment= 0;
};

template<>
struct getVarRender<HGS_RENDERBUFFER_DEPTH>{
    static const unsigned int internalformat= GL_DEPTH_COMPONENT;
    static const unsigned int attachment= GL_DEPTH_ATTACHMENT;
};

template<>
struct getVarRender<HGS_RENDERBUFFER_STENCIL>{
    static const unsigned int internalformat= GL_STENCIL_INDEX;
    static const unsigned int attachment= GL_STENCIL_ATTACHMENT;
};

template<>
struct getVarRender<HGS_RENDERBUFFER_DEPTH_STENCIL>{
    static const unsigned int internalformat= GL_DEPTH24_STENCIL8;
    static const unsigned int attachment= GL_DEPTH_STENCIL_ATTACHMENT;
};

template<unsigned int R>
static void generarRenderBuffer(unsigned int ancho, unsigned int alto){
    unsigned int rbo;
    glGenRenderbuffers(1,&rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,rbo);
    glRenderbufferStorage(GL_RENDERBUFFER,getVarRender<R>::internalformat,ancho,alto);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,getVarRender<R>::attachment,GL_RENDERBUFFER,rbo);
}

template<unsigned int R>
static void generarRenderBufferMultisample(unsigned int ancho, unsigned int alto, unsigned int numMSAA){
    unsigned int rbo;
    glGenRenderbuffers(1,&rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER,numMSAA,getVarRender<R>::internalformat,ancho,alto);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,getVarRender<R>::attachment,GL_RENDERBUFFER,rbo);
}


template<unsigned int R>
FrameBuffer<R>::FrameBuffer(unsigned int ancho, unsigned int alto)
: FBO(new unsigned(0)), ancho(ancho), alto(alto){

    unsigned int textureId= this->renderTexture.getTextureId();

    glGenFramebuffers(1,this->FBO.get());
    unsigned int fbo= *this->FBO;
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);

    glBindTexture(GL_TEXTURE_2D,textureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,ancho,alto,0,GL_RGB,GL_UNSIGNED_BYTE,nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindTexture(GL_TEXTURE_2D,0);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,textureId,0);

    enable_function_if<R!=HGS_RENDERBUFFER_NONE,void>::ejecutar(generarRenderBuffer<R>,ancho,alto);

    unsigned int status= glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status!=GL_FRAMEBUFFER_COMPLETE){
        std::cout << "FrameBufferCubeMap no esta completo: ";
        switch (status){
            case GL_FRAMEBUFFER_UNDEFINED :
                cout << "GL_FRAMEBUFFER_UNDEFINED " << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER :
                cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER " << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER  :
                cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER  " << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE  :
                cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE  " << endl;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS  :
                cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS  " << endl;
                break;
            case GL_FRAMEBUFFER_UNSUPPORTED:
                cout << "GL_FRAMEBUFFER_UNSUPPORTED" << endl;
                break;
        }

        exit(EXIT_FAILURE);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,0);

}

template<unsigned int R>
FrameBuffer<R>::FrameBuffer(unsigned int ancho, unsigned int alto, unsigned int numMSAA)
: FBO(new unsigned(0)), ancho(ancho), alto(alto){

    assert(numMSAA>=2);

    unsigned int textureId= this->renderTexture.getTextureId();

    glGenFramebuffers(1,this->FBO.get());
    unsigned int fbo= *this->FBO;
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);

    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,textureId);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,numMSAA,GL_RGB,ancho,alto,GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindTexture(GL_TEXTURE_2D,0);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D_MULTISAMPLE,textureId,0);

    enable_function_if<R!=HGS_RENDERBUFFER_NONE,void>::ejecutar(generarRenderBufferMultisample<R>,ancho,alto,numMSAA);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
        std::cout << "FrameBuffer no esta completo" << std::endl;
        exit(EXIT_FAILURE);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,0);

}


template<unsigned int R>
template<unsigned int S>
inline void FrameBuffer<R>::blitFrameBuffer(const FrameBuffer<S>& dst){
    glBindFramebuffer(GL_READ_FRAMEBUFFER,*this->FBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,*dst.FBO);
    glBlitFramebuffer(0,0,this->ancho,this->alto,
                      0,0,dst.ancho,dst.alto,
                      GL_COLOR_BUFFER_BIT,GL_NEAREST);
}

template<unsigned int R>
void FrameBuffer<R>::blitToDefaultFrameBuffer(unsigned int ancho, unsigned int alto){
    glBindFramebuffer(GL_READ_FRAMEBUFFER,*this->FBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
    glBlitFramebuffer(0,0,this->ancho,this->alto,0,0,ancho,alto,GL_COLOR_BUFFER_BIT,GL_NEAREST);
}

template<unsigned int R>
inline void FrameBuffer<R>::usar() const{
    glViewport(0,0,this->ancho,this->alto);
    glBindFramebuffer(GL_FRAMEBUFFER,*this->FBO);
}


template<unsigned int R>
inline Texture FrameBuffer<R>::getRenderTexture() const{
    return this->renderTexture;
}

template<unsigned int R>
inline unsigned int FrameBuffer<R>::getFBO(){
    return *this->FBO;
}

}

#endif // FRAMEBUFFER_H_INCLUDED
