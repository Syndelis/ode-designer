#ifndef H_InteractiveSimulation
#define H_InteractiveSimulation

#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <boost/numeric/odeint.hpp>

using namespace std;
using namespace boost::numeric::odeint;

typedef struct TODE {    
public:
    float ti, tf, dt, t;    
    std::string output_file;
    std::ofstream fp;
    std::vector<std::string> names;
    std::vector<double> u;
    std::function<void (const std::vector<double> &u, std::vector<double> &dudt, const double /* t */)> odeSystem;
    runge_kutta_cash_karp54<std::vector<double>> stepper;
    controlled_runge_kutta< runge_kutta_cash_karp54<std::vector<double>> > c_stepper;
    
    TODE(float tini, float tfinal, float deltat, std::string out, std::vector<std::string> n,
        std::function<void (const std::vector<double> &u, std::vector<double> &dudt, const double /* t */)> s){
        ti = tini;
        tf = tfinal;
        dt = deltat;
        output_file = out;
        names = n;
        odeSystem = s;        
        fp.open(out);
    }
    ~TODE(){}

    std::vector<double> advanceStep(){    
        c_stepper.stepper().do_step(odeSystem, u, t, dt);
        return u;
    }

    void initializeSolver(std::vector<double> values){
        fp << "time";
        for (auto v : names){
            fp << "," << v;
        }
        fp << endl;
        u = values;//initial condition 
        t = ti;
        c_stepper = make_controlled(1.E-08, 1.E-08, stepper);
        save(); //save initial condition
    }

    void save(){
        fp << t;
        for (double v : u){
            fp << "," << (v);
        }
        fp << endl;
    }

    void finishSimulation(){
        fp.close();
        std::cout << "Simulation finished " << std::endl;
    }
    
} ODE; 

//globals
extern std::vector<double> params;
extern bool flag_simulation;
extern struct TODE* ode;

#endif