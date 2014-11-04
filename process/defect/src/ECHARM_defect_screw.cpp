//
//  ECHARM_defect_screw.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_defect_screw.hh"

ECHARM_defect_screw::ECHARM_defect_screw(double num,double prob = 1.,bool sudden = true):
ECHARM_defect(num,prob,sudden){
    fName = "defect_screw";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_defect_screw::~ECHARM_defect_screw(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_screw::ComputeDispl(ECHARM_3vec* partpos,ECHARM_3vec* defpos){
    double x = partpos->GetX() - defpos->GetX();
    double z = partpos->GetZ() - defpos->GetZ();
    
    fDispl->SetX(0.);
    fDispl->SetZ(0.);

    double dy = 0.0;
    
    if(x==0. &&
       z==0.){
        fDispl->SetY(0.);
    }
    else{        
        dy = atan2( x , z ) ;
        dy *= ( fBurger );
        dy /= ( 2. * cPi );
        
        fDispl->SetY(dy);
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
        double b = fBurger;
        
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
