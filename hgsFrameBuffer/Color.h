#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED


namespace hgs{

namespace Color{

    void setColor(float r, float g, float b, float a);
    void setMask(bool r, bool g, bool b, bool a);
    void limpiar();

}

inline void Color::setColor(float r, float g, float b, float a){
    glClearColor(r,g,b,a);
}

inline void Color::setMask(bool r, bool g, bool b, bool a){
    glColorMask(r,g,b,a);
}

inline void Color::limpiar(){
    glClear(GL_COLOR_BUFFER_BIT);
}


}


#endif // COLOR_H_INCLUDED
