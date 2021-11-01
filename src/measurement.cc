#include "../include/measurement.h"


using namespace std;

Measurement::Measurement(double icurrent, double ikink){
  current = icurrent;
  kink = ikink;
  zrange = 2500.;
  haveMomentum = false;

  verbose = false;

  precision = 0.0001;
}

Measurement::Measurement(double icurrent, double ikink, double irange){
  current = icurrent;
  kink = ikink;
  zrange = irange + 1166.;
  haveMomentum = false;

  verbose = false;

  precision = 0.0001;
}

void Measurement::findMomentum(){

  size_t count = 0;

  double momentumLow = 0.5;
  double momentumHigh = 7.0;

  double cangle = 0;
  double cmomentum;

  double estimatedPrecision = 8.;
  
  while(estimatedPrecision > precision && count < 1000){

    cmomentum = (momentumLow+momentumHigh)/2.;
    
    Electron* elec = new Electron(cmomentum, current, angleIn);
    elec->setPrecisionZ(0.0002);
    elec->setZrange(zrange);

    
    elec->deflection();

    cangle = elec->getAngleOut();
    

    if(cangle < kink){
      momentumHigh = cmomentum;
    }else{
      momentumLow = cmomentum;
    }

    if(verbose){
      cout << "Angle: " << cangle << endl;
      cout << "Momentum: " << cmomentum << endl;
    }
    
    estimatedPrecision = momentumHigh-momentumLow;

    delete elec;
    count++;
  }

  momentum = cmomentum;

  haveMomentum = true;

}


