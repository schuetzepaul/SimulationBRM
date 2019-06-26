#ifndef MEASUREMENT_H
#include "../include/measurement.h"
#endif

int main(int argc, char *argv[]){

  double target = 0.07784;
  double current = 1400.;
  double zrange = 2500.;

  if (argc==3) {
    target=atof(argv[1]);
    current=atof(argv[2]);
  }else if(argc==4){
    target=atof(argv[1]);
    current=atof(argv[2]);
    zrange=atof(argv[3]);
  }else{
    cout << "Usage:" << endl << "./findMomentum [deflection angle in radian] [magnet current in A] ([position in z])" << endl;
    return 0;
  }

  Measurement meas(current, target, zrange);
    

  meas.findMomentum();
  cout << "The momentum was: " << meas.getMomentum() << endl;

}
