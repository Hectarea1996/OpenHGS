#ifndef TIEMPO_H_INCLUDED
#define TIEMPO_H_INCLUDED

namespace hgs{


class Tiempo{

    private:

        double factorLambda;
        double velocidad;


    public:

        Tiempo();
        double cogerFactorLambda();
        void asignarVelocidad(double vel);
        double cogerVelocidad();
        double FPS();
        void controlarFactorLambda();


};

inline Tiempo::Tiempo(){
    this->velocidad= 1;
    this->factorLambda= 0;
}

inline double Tiempo::cogerFactorLambda(){
    return factorLambda;
}

inline void Tiempo::asignarVelocidad(double vel){
    velocidad= vel;
}

inline double Tiempo::cogerVelocidad(){
    return velocidad;
}

inline double Tiempo::FPS(){
    return 1.0/this->factorLambda;
}


}


#endif // TIEMPO_H_INCLUDED
