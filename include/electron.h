//
//  
//
//  Created by Paul Schütze
//
//

#include <fstream>
#include <cmath>
#include <iostream>
#include <vector>
#include "Bcalc.h"

using namespace std;


class Electron{

 public:

  Electron(double imomentum, double icurrent, double iangleIn = 0., double iposIn = 0.){
    momentum = imomentum;
    current = icurrent;
    angleIn = iangleIn;
    posIn = iposIn;
    precisionZ = 0.001;
  }
  
  void deflection();

  double getPosOut(){return posOut;};
  double getAngleOut(){return angleOut;};

  void setPrecisionZ(double val){precisionZ = val;};
  void setZrange(double val){zrange = val;};
  
 private:
  
  double momentum;
  double current;
  double angleIn;
  double angleOut;
  double posIn;
  double posOut;

  double precisionZ;
  double zrange;



};
