
#include "Tiempo.h"
#include "../OpenHGS.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace hgs;

void Tiempo::controlarFactorLambda(){

    using namespace std::chrono;

    static steady_clock::time_point t1= steady_clock::now();
    static steady_clock::time_point t2= steady_clock::now();
    static int ciclos= 500000;

    t2= steady_clock::now();

    if (t2!=t1){
        duration<double> duracion= duration_cast<duration<double>>(t2-t1);
        this->factorLambda= this->velocidad*duracion.count()/ciclos;
        t1= t2;
        ciclos=1;
    }
    else ciclos++;

}
