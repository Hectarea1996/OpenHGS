#ifndef TECLADO_H_INCLUDED
#define TECLADO_H_INCLUDED

#include "../OpenHGS.h"
#include <functional>
using namespace std;

namespace hgs{

class Ventana;

class Teclado{

    friend class Ventana;

    private:

        GLFWwindow * window;

        Teclado(GLFWwindow * window);


    public:

        bool teclaPulsada(int GLFW_KEY) const;

        void insertarListener(function<void(int key, int scancode, int action, int mods)> * listener);
        void insertarListener(function<void(unsigned int codepoint, int mods)> * listener);

        void extraerListener(function<void(int key, int scancode, int action, int mods)> * listener);
        void extraerListener(function<void(unsigned int codepoint, int mods)> * listener);

};

inline bool Teclado::teclaPulsada(int GLFW_KEY) const{
    return glfwGetKey(this->window,GLFW_KEY)==GLFW_PRESS;
}

}

#endif // TECLADO_H_INCLUDED
