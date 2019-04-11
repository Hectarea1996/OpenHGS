
#include "Teclado.h"
#include "../hgsLista/hgsLista.h"
using namespace hgs;

static hgsLista<function<void(int key, int scancode, int action, int mods)>*> teclaListeners;
static hgsLista<function<void(unsigned int codepoint, int mods)>*> textoListeners;


static void hgsTeclaEvento(GLFWwindow * window, int key, int scancode, int action, int mods){
    for (auto funcion : teclaListeners){
        (*funcion)(key,scancode,action,mods);
    }
}

static void hgsTextoEvento(GLFWwindow * window, unsigned int codepoint, int mods){
    for (auto funcion : textoListeners){
        (*funcion)(codepoint,mods);
    }
}

Teclado::Teclado(GLFWwindow * window): window(window){
    glfwSetKeyCallback(this->window,hgsTeclaEvento);
    glfwSetCharModsCallback(this->window,hgsTextoEvento);
}

void Teclado::insertarListener(function<void(int key, int scancode, int action, int mods)> * listener){
    teclaListeners.push_back(listener);
}

void Teclado::insertarListener(function<void(unsigned int codepoint, int mods)> * listener){
    textoListeners.push_back(listener);
}

void Teclado::extraerListener(function<void(int key, int scancode, int action, int mods)> * listener){

    using tipo= function<void(int key, int scancode, int action, int mods)>*;
    for (hgsLista<tipo>::iterator it= teclaListeners.begin(); it!=teclaListeners.end(); ++it){
        function<void(int key, int scancode, int action, int mods)> * funcion= *it;
        if (funcion==listener){
            it.erase();
            return;
        }
    }

}

void Teclado::extraerListener(function<void(unsigned int codepoint, int mods)> * listener){

    using tipo= function<void(unsigned int codepoint, int mods)>*;
    for (hgsLista<tipo>::iterator it= textoListeners.begin(); it!=textoListeners.end(); ++it){
        function<void(unsigned int codepoint, int mods)> * funcion= *it;
        if (funcion==listener){
            it.erase();
            return;
        }
    }

}



