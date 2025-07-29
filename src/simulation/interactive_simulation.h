#ifndef H_InteractiveSimulation
#define H_InteractiveSimulation

#include <iostream>
#include <fstream> 
#include <vector>
#include <string>

using namespace std;

typedef struct TODE {    
public:
    float ti, tf, dt, t;    
    std::ofstream fp;
    
    TODE(float tini, float tfinal, float deltat, std::string out, std::vector<std::string> n,

    }
    ~TODE(){}

    std::vector<double> advanceStep(){    

        return u;
    }

    void initializeSolver(std::vector<double> values){
    }

    void save(){

    }

    void finishSimulation(){

    }
    
} ODE; 

//globals
extern std::vector<double> params;
extern bool flag_simulation;
extern struct TODE* ode;

#endif