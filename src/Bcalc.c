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

using namespace std;


double evalB(double *bfield, double *zcoord, double z, int n){
    
    int i=0;
    double b;
    double corrfact=1.005;
    
    // B is calculated in the region, where zcoord is defined. Elsewhere it is set to 0
    
    if (z>zcoord[0]){
        
        if (z<=zcoord[n-1]) {
            
            while (zcoord[i]<z && i<n) {
                i++;
            }
            
            // B is approximated assuming linearity between the given values
            b=bfield[i-1]+(z-zcoord[i-1])/(zcoord[i]-zcoord[i-1])*(bfield[i]-bfield[i-1]);
            b*=corrfact;
            
        }else{
            
            b=0;
            
        }
    }else{
        b=0;
    }
    
    //cout << "B=" << b << endl;
    
    return(b);
    
}

bool bMap(double I, double *bcurr, double *zcoord){
    
    ifstream inp;
    ofstream outp;
    double in1,in2,in3,in4;
    
    
    double bfield[15][117]={0};
    double Iarr[15]={0};
    
    
    // Readout all the FieldMaps
    
    char filename[200];
    
    for (int i=1; i<15; i++) {
        
        sprintf(filename, "md_corr_edit/md365.%02d1.4", i);
        
        inp.open(filename);
        
        char buff[100];
        
        for (int j=0; j<6; j++) {
            inp.getline(buff, 100);
        }
        
        // Read data:
        int icount=0;
        
        while (inp >> in1 >> in2 >> in3 >> in4) {

            if(i==1)zcoord[icount]=(in1);
            
            bfield[i][icount]=(in2/10000.);
            
            icount++;
        }
        
        inp.close();
        
        Iarr[i]=100.*i;
        
    }
    
    // Interpolate the field and write it into bcurr[]
    
    int icount=0;
    
    // B is calculated in the region, where zcoord is defined. Elsewhere it is set to 0
    
    
    bool hitcurr=0;
    
    // Did we hit a measured current?
    for (int i=0; i<15; i++) {
        if (I==Iarr[i]){
            for (int j=0; j<117; j++) {
                bcurr[j]=bfield[i][j];
            }
            hitcurr=1;
        }
        
    }
    
    if (hitcurr==0){
        if (I>Iarr[0]){
        
            if (I<=Iarr[14]) {
            
                while (Iarr[icount]<I && icount<15) {
                    icount++;
                }
            
                // B is approximated assuming linearity between the given currents
            
                for (int j=0; j<117; j++) {
                    bcurr[j]=bfield[icount-1][j]+(I-Iarr[icount-1])/(Iarr[icount]-Iarr[icount-1])*(bfield[icount][j]-bfield[icount-1][j]);
                }
            
            }else{
            
                cout << "Magnetic Field not known for your current current!" << endl;
            
            }
        }else{
            cout << "Magnetic Field not known for your current current!" << endl;
        }
    }
    
    //cout << "Current is between " << Iarr[icount-1] << " and " << Iarr[icount] << endl;
    //std::cout << "BField at z=" << zcoord[56] << " is " << bcurr[56] << std::endl;
    
    return 0;
    
}





