#ifndef HGS_LIST_H_INCLUDED
#define HGS_LIST_H_INCLUDED

#include <assert.h>
#include <iostream>
using namespace std;

template<typename T>
class hgsLista{

    private:

        class hgsElemLista{

            public:

                T elemento;
                hgsElemLista * sig;
                hgsElemLista * ant;

                template<typename... S>
                hgsElemLista(S&&... args) : elemento(forward<S>(args)...){
                    this->sig= nullptr;
                    this->ant= nullptr;
                }

                hgsElemLista(const T& elem) : elemento(elem){
                    this->sig= nullptr;
                    this->ant= nullptr;
                }

                hgsElemLista(T&& elem) : elemento(move(elem)){
                    this->sig= nullptr;
                    this->ant= nullptr;
                }

        };

        hgsElemLista * primero;
        hgsElemLista * ultimo;

        void push_front(hgsElemLista * elemento){
            if (primero==nullptr){
                primero= elemento;
                ultimo= elemento;
            }
            else{
                elemento->sig= primero;
                primero->ant= elemento;
                primero= elemento;
            }
        }

        void push_back(hgsElemLista * elemento){
            if (ultimo==nullptr){
                primero= elemento;
                ultimo= elemento;
            }
            else{
                elemento->ant= ultimo;
                ultimo->sig= elemento;
                ultimo= elemento;
            }
        }

        void push_order(hgsElemLista * elemento){
            if (ultimo==nullptr){
                primero= elemento;
                ultimo= elemento;
            }
            else{
                hgsElemLista * it= this->primero;
                while(it!=nullptr && elemento->elemento>it->elemento){
                    it= it->sig;
                }
                if (it==nullptr){
                    this->ultimo->sig= elemento;
                    elemento->ant= this->ultimo;
                    this->ultimo= elemento;
                }
                else{
                    hgsElemLista * izq= it->ant;
                    if (izq==nullptr){
                        this->primero->ant= elemento;
                        elemento->sig= this->primero;
                        this->primero= elemento;
                    }
                    else{
                        izq->sig= elemento;
                        it->ant= elemento;
                        elemento->ant= izq;
                        elemento->sig= it;
                    }
                }
            }
        }

        bool push_order_noRepeat(hgsElemLista * elemento){
            if (ultimo==nullptr){
                primero= elemento;
                ultimo= elemento;
            }
            else{
                hgsElemLista * it= this->primero;
                while(it!=nullptr && elemento->elemento>it->elemento){
                    it= it->sig;
                }
                if (it==nullptr){
                    this->ultimo->sig= elemento;
                    elemento->ant= this->ultimo;
                    this->ultimo= elemento;
                }
                else{
                    if (elemento->elemento==it->elemento){
                        return false;
                    }
                    hgsElemLista * izq= it->ant;
                    if (izq==nullptr){
                        this->primero->ant= elemento;
                        elemento->sig= this->primero;
                        this->primero= elemento;
                    }
                    else{
                        izq->sig= elemento;
                        it->ant= elemento;
                        elemento->ant= izq;
                        elemento->sig= it;
                    }
                }
            }

            return true;
        }

        void erase(hgsElemLista * elemento){
            assert(elemento!=nullptr);
            hgsElemLista * izq= elemento->ant;
            hgsElemLista * der= elemento->sig;
            if (izq!=nullptr)
                izq->sig= der;
            else
                this->primero= der;
            if (der!=nullptr)
                der->ant= izq;
            else
                this->ultimo= izq;
            elemento->ant= nullptr;
            elemento->sig= nullptr;
        }


    public:

        class hgsListaException{

            friend class iterator;
            friend class hgsLista<T>;

            private:

                string error;
                hgsListaException(string _error) : error(_error){}

            public:

                void print(){
                    cerr << error << endl;
                }

        };

        class iterator{

            friend class hgsLista<T>;

            private:

                hgsLista<T> * lista;
                hgsElemLista * it;

                iterator();

                iterator(hgsElemLista * _it, hgsLista<T> * _lista){
                    this->it= _it;
                    this->lista= _lista;
                }

            public:

                iterator& operator++(){
                    if (this->it==nullptr)
                        throw hgsListaException("No hay mas elementos.");
                    this->it= it->sig;
                    return *this;
                }

                void erase(){
                    if (this->it==nullptr)
                        throw hgsListaException("El iterador no apunta a ningun elemeto.");
                    this->lista->erase(this->it);
                    this->it= nullptr;
                }

                void transferFront(hgsLista<T>& destino){
                    if (this->it==nullptr)
                        throw hgsListaException("El iterador no apunta a ningun elemeto.");
                    this->lista->erase(this->it);
                    this->lista= &destino;
                    destino.push_front(this->it);
                }

                void transferBack(hgsLista<T>& destino){
                    if (this->it==nullptr)
                        throw hgsListaException("El iterador no apunta a ningun elemeto.");
                    this->lista->erase(this->it);
                    this->lista= &destino;
                    destino.push_back(this->it);
                }

                void transferOrder(hgsLista<T>& destino){
                    if (this->it==nullptr)
                        throw hgsListaException("El iterador no apunta a ningun elemeto.");
                    this->lista->erase(this->it);
                    this->lista= &destino;
                    destino.push_order(this->it);
                }

                void transferOrderNoRepeat(hgsLista<T>& destino){
                    if (this->it==nullptr)
                        throw hgsListaException("El iterador no apunta a ningun elemeto.");
                    this->lista->erase(this->it);
                    this->lista= &destino;
                    destino.push_order_noRepeat(this->it);
                }

                T& operator*(){
                    if (this->it==nullptr)
                        throw hgsListaException("El iterador no apunta a ningun elemento.");
                    return this->it->elemento;
                }

                bool operator!=(const iterator& iter){
                    return this->it!=iter.it;
                }

        };

        hgsLista(){
            this->primero= nullptr;
            this->ultimo= nullptr;
        }

        hgsLista(const hgsLista& lista){
            if (lista.primero==nullptr)
                return;
            this->primero= new hgsElemLista(lista.primero->elemento);
            this->ultimo= this->primero;
            hgsElemLista * it= lista.primero->sig;
            while(it!=nullptr){
                this->ultimo->sig= new hgsElemLista(it->elemento);
                this->ultimo= this->ultimo->sig;
                it=it->sig;
            }
        }

        hgsLista(hgsLista&& lista){
            if (this->primero!=nullptr){
                hgsElemLista * it= this->primero;
                hgsElemLista * q;
                while(it!=nullptr){
                    q= it;
                    it= it->sig;
                    delete q;
                }
            }
            this->primero= lista.primero;
            this->ultimo= lista.ultimo;
            lista.primero= nullptr;
            lista.ultimo= nullptr;
        }

        ~hgsLista(){
            hgsElemLista * it= this->primero;
            hgsElemLista * q;
            while(it!=nullptr){
                q= it;
                it= it->sig;
                delete q;
            }
        }

        bool empty(){
            return this->primero==nullptr;
        }

        T& front(){
            if (this->primero==nullptr)
                throw hgsListaException("No hay elementos en la lista.");
            return this->primero->elemento;
        }

        T& back(){
            if (this->ultimo==nullptr)
                throw hgsListaException("No hay elementos en la lista.");
            return this->ultimo->elemento;
        }

        iterator begin(){
            return iterator(this->primero,this);
        }

        iterator end(){
            return iterator(nullptr,this);
        }

        void push_front(const T& elem){
            hgsElemLista * elemento= new hgsElemLista(elem);
            this->push_front(elemento);
        }

        void push_front(T&& elem){
            hgsElemLista * elemento= new hgsElemLista(move(elem));
            this->push_front(elemento);
        }

        template<typename... S>
        void push_front(S&&... args){
            hgsElemLista * elemento= new hgsElemLista(forward<S>(args)...);
            this->push_front(elemento);
        }

        void push_back(const T& elem){
            hgsElemLista * elemento= new hgsElemLista(elem);
            this->push_back(elemento);
        }

        void push_back(T&& elem){
            hgsElemLista * elemento= new hgsElemLista(move(elem));
            this->push_back(elemento);
        }

        template<typename... S>
        void push_back(S&&... args){
            hgsElemLista * elemento= new hgsElemLista(forward<S>(args)...);
            this->push_back(elemento);
        }

        void pop_front(){
            if (this->primero==nullptr)
                throw hgsListaException("No hay elementos en la lista.");
            hgsElemLista * q= this->primero;
            hgsElemLista * der= q->sig;
            if (der==nullptr){
                this->primero= nullptr;
                this->ultimo= nullptr;
            }
            else{
                der->ant= nullptr;
                this->primero= der;
            }
            delete q;
        }

        void pop_back(){
            if (this->ultimo==nullptr)
                throw hgsListaException("No hay elementos en la lista.");
            hgsElemLista * q= this->ultimo;
            hgsElemLista * izq= q->ant;
            if (izq==nullptr){
                this->primero= nullptr;
                this->ultimo= nullptr;
            }
            else{
                izq->sig= nullptr;
                this->ultimo= izq;
            }
            delete q;
        }

        void push_order(T& elem){
            hgsElemLista * elemento= new hgsElemLista(elem);
            this->push_order(elemento);
        }

        void push_order(T&& elem){
            hgsElemLista * elemento= new hgsElemLista(move(elem));
            this->push_order(elemento);
        }

        template <typename... S>
        void push_order(S&&... args){
            hgsElemLista * elemento= new hgsElemLista(forward<S>(args)...);
            this->push_order(elemento);
        }

        void push_order_noRepeat(T& elem){
            hgsElemLista * elemento= new hgsElemLista(elem);
            if (!this->push_order_noRepeat(elemento))
                delete elemento;
        }

        void push_order_noRepeat(T&& elem){
            hgsElemLista * elemento= new hgsElemLista(move(elem));
            if (!this->push_order_noRepeat(elemento))
                delete elemento;
        }

        template <typename... S>
        void push_order_noRepeat(S&&... args){
            hgsElemLista * elemento= new hgsElemLista(forward<S>(args)...);
            this->push_order_noRepeat(elemento);
        }

        void append(hgsLista& lista){
            if (lista.primero==nullptr)
                return;
            if (this->primero==nullptr){
                this->primero= lista.primero;
                this->ultimo= lista.ultimo;
            }
            else{
                this->ultimo->sig= lista.primero;
                lista.primero->ant= this->ultimo;
                this->ultimo= lista.ultimo;
            }
            lista.primero= nullptr;
            lista.ultimo= nullptr;
        }

        void preppend(hgsLista& lista){
            if (lista.primero==nullptr)
                return;
            if (this->primero==nullptr){
                this->primero= lista.primero;
                this->ultimo= lista.ultimo;
            }
            else{
                this->primero->ant= lista.ultimo;
                lista.ultimo->sig= this->primero;
                this->primero= lista.primero;
            }
            lista.primero= nullptr;
            lista.ultimo= nullptr;
        }

        void naturalMergeSort(){
            hgsLista aux1;
            hgsLista aux2;
            hgsLista aux3;
            aux1.primero= this->primero;
            aux1.ultimo= this->ultimo;
            this->primero= nullptr;
            this->ultimo= nullptr;
            hgsElemLista * it1= aux1.primero;
            hgsElemLista * it2= aux2.primero;
            while (it1!=nullptr){
                hgsElemLista * siguiente= nullptr;
                if (it2==nullptr){
                    siguiente= it1;
                }
                else{
                    siguiente= (it2->elemento>it1->elemento) ? it1 : it2;
                }
                if (siguiente==it1){
                    bool pre= false;
                    hgsElemLista * transfer= it1;
                    it1= it1->sig;
                    if (it1->sig!=nullptr && it1->elemento>it1->sig->elemento){
                        pre= true;
                    }
                    aux1.erase(transfer);
                    aux3.push_back(transfer);
                    if (pre)
                        aux2.preppend(aux3);
                }
                else {
                    hgsElemLista * transfer= it2;
                    it2= it2->sig;
                    aux2.erase(transfer);
                    aux3.push_back(transfer);
                }
            }
            if (aux2.primero!=nullptr){
                aux3.append(aux2);
            }
            this->primero= aux3.primero;
            this->ultimo= aux3.ultimo;
            aux3.primero= nullptr;
            aux3.ultimo= nullptr;
        }


};


#endif // HGS_LIST_H_INCLUDED
