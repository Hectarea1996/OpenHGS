#ifndef RATON_H_INCLUDED
#define RATON_H_INCLUDED

#include "../OpenHGS.h"
#include <functional>
using namespace std;


#define HGS_CURSOR_NORMAL       GLFW_CURSOR_NORMAL
#define HGS_CURSOR_DESACTIVADO  GLFW_CURSOR_DISABLED
#define HGS_CURSOR_ESCONDIDO    GLFW_CURSOR_HIDDEN


namespace hgs{


class Raton{

    friend class Ventana;

    private:

        GLFWwindow * window;

        Raton(GLFWwindow * window);


    public:

        void getPosicion(int GLFW_KEY, double& x, double& y);
        bool botonPulsado(int GLFW_MOUSE_BUTTON);
        void setMode(int HGS_CURSOR);

        void insertarBotonListener(function<void(int boton, int action, int mods)> * listener);
        void insertarMovListener(function<void(double cantX,double cantY)> * listener);
        void insertarScrollListener(function<void(double cantX, double cantY)> * listener);

        void extraerBotonListener(function<void(int boton, int action, int mods)> * listener);
        void extraerMovListener(function<void(double cantX,double cantY)> * listener);
        void extraerScrollListener(function<void(double cantX, double cantY)> * listener);

};



inline void Raton::getPosicion(int GLFW_KEY, double& x, double& y){
    glfwGetCursorPos(this->window,&x,&y);
}

inline bool Raton::botonPulsado(int GLFW_MOUSE_BUTTON){
    return glfwGetMouseButton(this->window,GLFW_MOUSE_BUTTON)==GLFW_PRESS;
}

inline void Raton::setMode(int HGS_CURSOR){
    glfwSetInputMode(this->window,GLFW_CURSOR,HGS_CURSOR);
}


}

#endif // RATON_H_INCLUDED
