//
//  ECHARM_intrp.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_intrp_h

#include "ECHARM_intrp.hh"
#include <math.h>

ECHARM_intrp::ECHARM_intrp(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_intrp::~ECHARM_intrp(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_intrp::Get2d (double &x,double &y,double &p00,double &p01, double &p02,double &p03,double &p10,double &p11, double &p12,double &p13,double &p20,double &p21, double &p22,double &p23,double &p30,double &p31, double &p32,double &p33){
    
    double aa0=Get1d(y,p00,p01,p02,p03);
    double aa1=Get1d(y,p10,p11,p12,p13);
    double aa2=Get1d(y,p20,p21,p22,p23);
    double aa3=Get1d(y,p30,p31,p32,p33);
    
    return Get1d(y,aa0,aa1,aa2,aa3);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_intrp::Get1d(double &x, double &p0,double &p1, double &p2,double &p3){
    double a0, a1 , a2 , a3 , x2;
    x2 = x * x;
    a0 = -0.5 * p0 + 1.5 * p1 - 1.5 * p2 + 0.5 * p3;
    a1 = p0 - 2.5 * p1 + 2.0 * p2 - 0.5 * p3;
    a2 = -0.5 * p0 + 0.5 * p2;
    a3 = p1;

    return (a0 * x * x2 + a1 * x2 + a2 * x + a3);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_intrp::GetXinUnitPeriod(double x, double &vPeriod){
    double vX = x;
    if (vX < 0.0) {
        vX += ((int( - vX / vPeriod) + 1.0 ) * vPeriod);
    }
    else if( vX > vPeriod ){
        vX -= ( int( vX / vPeriod) * vPeriod );
    }
    return vX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_intrp::GetXinUnitOne(double vX, double &vPeriod){
    return GetXinUnitPeriod(vX,vPeriod)/vPeriod;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_intrp::GetIndexes(int* index, int& ntot){
    if( (index[1]) == (ntot - 1) ){
        index[0] = ntot - 2;
        index[2] = 0;
        index[3] = 1;
    }
    else if(index[1] == (ntot - 2) )
    {
        index[0] = ntot - 3;
        index[2] = ntot - 1;
        index[3] = 0;
    }
    else if(index[1] == 0){
        index[0] = ntot - 1;
        index[2] = 1;
        index[3] = 2;
    }
    else{
        index[0] = index[1] - 1;
        index[2] = index[1] + 1;
        index[3] = index[1] + 2;
    }

    if(index[1] > ntot) std::cout << "ECHARM_intrp - ERROR: " << index[1] << " " << ntot << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif



