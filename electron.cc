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
#include <string>

#include "electron.h"


using namespace std;



void Electron::deflection(){
    
    const double c=299792458.;
    const double pi=3.14159265359;
    const double q=1.6e-19;
    const double m=510999.;
    
    
    // get the FieldMap
    const int n=117;
    
    double bfield[n]={0};
    double zcoord[n]={0};
    
    bMap(current, bfield, zcoord);
    
    // Simulate the particles trajectory inside the magnetic field
    
    
    double x1,z1,vx1,vx2,vz1,vz2,vtot;
    
    double dt=precisionZ/c; // equivalent stepsize in s


    double p=momentum*1.e9;
    
    //Get the total velocity
    vtot=p*c/sqrt(pow(m,2)+pow(p,2))*1000.; // Factor 1000: Talking in millimeters
    
    // Calculate vx and vz out of vtot and the incident angle (given in rad)
    vx1=vtot*sin(angleIn);
    vz1=vtot*cos(angleIn);
    
    double gamma=1./sqrt(1-pow(vtot/1000./c,2));
    
    x1=posIn;
    //z1=-1360.+410.; // distance between collimator and magnet: 1360, then subtracting the z coordinate of the FieldMap at which the magnet is starting, approx. 0410
    z1=-10.; // Starting from right before the magnet
    
    
    double kon;
    
    // Here we go, using the Boris Method (according to http://www.particleincell.com/2011/vxb-rotation/)
    
    int i=0;


    //while (z1<3928.-950.) {
    while (z1<zrange) {
        
        
        //usually there would be a minus in front of the evalB, but i choose the field to be the other way round.
        kon=evalB(bfield, zcoord, z1, n)*dt/(2.*gamma*m/pow(c,2));

        vx2=vx1+2.*kon/(1+1.*pow(kon,2))*(-vz1-vx1*kon);
        vz2=vz1+2.*kon/(1+1.*pow(kon,2))*(vx1-vz1*kon);
        
        x1+=vx2*dt;
        z1+=vz2*dt;
        
        i++;
        
        vx1=vx2;
        vz1=vz2;
        
        
    }
    
    angleOut=abs(atan(vx1/vz1));
    posOut=x1;
        
}
