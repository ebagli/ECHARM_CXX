//
//  ECHARM_defect_edge.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_defect_edge.hh"

ECHARM_defect_edge::ECHARM_defect_edge(double num,double prob = 1., bool sudden = true):
ECHARM_defect(num,prob,sudden){
    fName = "defect_edge";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_defect_edge::~ECHARM_defect_edge(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_edge::CompDispl(ECHARM_3vec* partpos,ECHARM_3vec* defpos){
    double x = partpos->GetX() - defpos->GetX();
    double z = partpos->GetZ() - defpos->GetZ();
    
    double dy = 0.0;
    double dx = 0.0;
    double dz = 0.0;
    
    if(dx==0.) dx=std::numeric_limits<double>::min();
    if(dy==0.) dy=std::numeric_limits<double>::min();
    
    if(x==0. &&
       z==0.){
        fDispl->SetX(0.);
    }
    else{
        double xz2 = x * x + z * z;
        
        dx = atan2(x , z ) ;
        dx += ( z * x / xz2 / 2.0 / ( 1.0 - fPoissonRatio ) );
        dx *= ( fBurger->GetModule() );
        dx /= ( 2. * cPi );
        
        dz = ( ( 1.0 - 2.0 * fPoissonRatio) * log(xz2));
        dz += ( ( x * x - z * z ) / xz2 );
        dz *= ( fBurger->GetModule() );
        dz /= ( 8. * cPi );
        dz /= ( 1. - fPoissonRatio );
        
        fDispl->SetX(dx);
        fDispl->SetY(dy);
        fDispl->SetZ(dz);
    }
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_edge::ComputeBR(ECHARM_3vec* partpos,ECHARM_3vec* defpos){
    fBR->SetY(0.);
    fBR->SetZ(0.);
    
    double x = partpos->GetX() - defpos->GetX();
    double z = partpos->GetZ() - defpos->GetZ();
    
    if(x==0. &&
       z==0.){
        fBR->SetX(0.);
    }
    else{
        // (1 + (d/dz (b/(2*l)(arctan(z/x)+1/(2*(1-P))*x*z/(x*x+z*z))))^2)^1.5/ (d/dzdz (b/(2*l)(arctan(z/x)+1/(2*(1-P))*x*z/(x*x+z*z))))
        double xz2 = x*x + z*z;
        double b = fBurger->GetModule();
        double p = fPoissonRatio;
        
        double Rx1 = fSquare( ( 3. - 2. * p ) * x * x + (1. - 2. * p) * z * z );
        Rx1 *= ( x * x * b * b);
        Rx1 /= (16. * cPi * cPi * fSquare( p - 1.) * xz2 * xz2 * xz2 * xz2);
        Rx1 += 1.;
        
        double Rx2 = b * x * z * ( (2. * p - 5.) * x * x + (2. * p - 1.) * z * z );
        double Rx = 2. * cPi * ( p - 1.) * xz2 * xz2 * xz2;
        
        if(Rx2!=0){
            Rx /= Rx2;
            Rx *= pow(Rx1,1.5);
        }
        else{
            Rx = 0.;
        }
        fBR->SetX(Rx);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
