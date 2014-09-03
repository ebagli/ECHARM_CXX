//
//  ECHARM_defect_screw.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_defect_screw.hh"

ECHARM_defect_screw::ECHARM_defect_screw(double num,bool sudden = true):
ECHARM_defect(num,sudden){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_defect_screw::~ECHARM_defect_screw(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_screw::CompDispl(ECHARM_3vec* partpos,ECHARM_3vec* defpos){
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
        
        dy = atan2( x , z ) ;
        dy *= ( fBurger->GetModule() );
        dy /= ( 2. * cPi );
        
        fDispl->SetX(dx);
        fDispl->SetY(dy);
        fDispl->SetZ(dz);
    }
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_screw::ComputeBR(ECHARM_3vec* partpos,ECHARM_3vec* defpos){
    fBR->SetY(0.);
    fBR->SetZ(0.);
    
    double x = partpos->GetX() - defpos->GetX();
    double z = partpos->GetZ() - defpos->GetZ();
    
    if(x==0. &&
       z==0.){
        fBR->SetX(0.);
    }
    else{
        // (1 + (d/dz (b/(2*l)(arctan(z/x))))^2)^1.5/ (d/dzdz (b/(2*l)(arctan(z/x))))
        double xz2 = x*x + z*z;
        double b = fBurger->GetModule();
        double p = fPoissonRatio;
        
        double Rx1 = b*b+x*x;
        Rx1 /= fSquare(2.*cPi*xz2);
        Rx1 += 1.;
        
        double Rx2 = b * x * z;
        double Rx = cPi * xz2 * xz2;
        
        if(Rx2!=0){
            Rx /= Rx2;
            Rx *= pow(Rx1,1.5);
        }
        else{
            Rx = 0.;
        }
        fBR->SetX(- Rx);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
