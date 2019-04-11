
#include "Raton.h"
#include "../hgsLista/hgsLista.h"
using namespace hgs;

static hgsLista<function<void(int boton, int accion, int mods)>*> botonListeners;
static hgsLista<function<void(double cantX, double cantY)>*> movListeners;
static hgsLista<function<void(double cantX, double cantY)>*> scrollListeners;


static void hgsBotonEvento(GLFWwindow * window, int boton, int action, int mods){
    using tipo= function<void(int boton, int accion, int mods)>*;
    for (tipo funcion : botonListeners){
        (*funcion)(boton,action,mods);
    }
}

static void hgsMovEvento(GLFWwindow * window, double posX, double posY){
    static double ultimoX= posX;
    static double ultimoY= posY;
    double cantX= posX-ultimoX;
    double cantY= posY-ultimoY;
    using tipo= function<void(double cantX, double cantY)>*;
    for (tipo funcion : movListeners){
        (*funcion)(cantX,cantY);
    }
    ultimoX= posX;
    ultimoY= posY;
}

static void hgsScrollEvento(GLFWwindow * window, double cantX, double cantY){
    using tipo= function<void(double cantX, double cantY)>*;
    for (tipo funcion : scrollListeners){
        (*funcion)(cantX,cantY);
    }
}


Raton::Raton(GLFWwindow * window): window(window){
    glfwSetMouseButtonCallback(this->window,hgsBotonEvento);
    glfwSetCursorPosCallback(this->window,hgsMovEvento);
    glfwSetScrollCallback(this->window,hgsScrollEvento);
}

void Raton::insertarBotonListener(function<void(int boton, int action, int mods)> * listener){
    botonListeners.push_back(listener);
}

void Raton::insertarMovListener(function<void(double cantX, double cantY)> * listener){
    movListeners.push_back(listener);
}

void Raton::insertarScrollListener(function<void(double cantX, double cantY)> * listener){
    scrollListeners.push_back(listener);
}

void Raton::extraerBotonListener(function<void(int boton, int action, int mods)> * listener){

    using tipo= function<void(int boton, int accion, int mods)>*;
    for (hgsLista<tipo>::iterator it= botonListeners.begin(); it!=botonListeners.end(); ++it){
        function<void(int boton, int accion, int mods)> * funcion= *it;
        if (funcion==listener){
            it.erase();
            return;
        }
    }

}

void Raton::extraerMovListener(function<void(double cantX, double cantY)> * listener){

    using tipo= function<void(double cantX, double cantY)>*;
    for (hgsLista<tipo>::iterator it= movListeners.begin(); it!=movListeners.end(); ++it){
        function<void(double cantX, double cantY)> * funcion= *it;
        if (funcion==listener){
            it.erase();
            return;
        }
    }

}

void Raton::extraerScrollListener(function<void(double cantX, double cantY)> * listener){

    using tipo= function<void(double cantX, double cantY)>*;
    for (hgsLista<tipo>::iterator it= scrollListeners.begin(); it!=scrollListeners.end(); ++it){
        function<void(double cantX, double cantY)> * funcion= *it;
        if (funcion==listener){
            it.erase();
            return;
        }
    }

}
