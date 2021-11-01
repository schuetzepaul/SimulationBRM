//
//  
//
//  Created by Paul Schütze
//
//

#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sys/time.h>

#include "../include/electron.h"

using namespace std;



int main(int argc, char *argv[]){
    
    timeval start1, end1;
    gettimeofday(&start1, 0);
    
    // Interpolating the magnetic field from the different FieldMap files
    
    double I=235.;
    double p=4.;
    double xin=0.;
    double thetain=0.0;
    double dx=0.0001; // dx in mm
    double xout, thetaout;
    
    // Parameter:
    
    int nruns=1;
    
    double zstop;
    
    if (argc==4) {
        p=atof(argv[1]);
	I=atof(argv[2]);
	zstop=atof(argv[3]);
    }else if (argc==6) {
        p=atof(argv[1]);
	I=atof(argv[2]);
	zstop=atof(argv[3]);
	xin=atof(argv[4]);
	thetain=atof(argv[5]);
    }else{
        cout << "Usage:" << endl << "./BRMeval [momentum in GeV] [magnet current in A] [end of tracking in mm]" << endl;
        cout << "Note: The end of tracking is defined in reference to the center of the magnet" << endl;
        
        return 0;
    }

    zstop += 1166.;
    
    char buffer[100];
     //cout << buffer << endl;
    
    for (int i=0; i<nruns; i++) {

      Electron elec(p,I,thetain,xin);
      elec.setPrecisionZ(dx);
      elec.setZrange(zstop);
                
      elec.deflection();

      thetaout = elec.getAngleOut();
      xout = elec.getPosOut();


    }

    cout << "p=" << p << " GeV\tIb=" << I << " A\tx=" << xout << " mm\ttheta=" << thetaout << " rad (" << thetaout*180./M_PI << " deg)" << endl;
    
    gettimeofday(&end1, 0);
    
    double timediff1 = (end1.tv_sec-start1.tv_sec)+(end1.tv_usec-start1.tv_usec)/1000000.;
    
    //cout << "Dauer: " << timediff1 << "s" << endl;
    
    
    return 0;
        
}
