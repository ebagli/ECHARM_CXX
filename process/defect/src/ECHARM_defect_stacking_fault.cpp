//
//  ECHARM_defect_stacking_fault.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_defect_stacking_fault.hh"

ECHARM_defect_stacking_fault::ECHARM_defect_stacking_fault(double num,double prob = 1.):
ECHARM_defect(num,prob,true){
    fName = "defect_stacking_fault";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_defect_stacking_fault::~ECHARM_defect_stacking_fault(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_stacking_fault::CompDispl(ECHARM_3vec* partpos,ECHARM_3vec* defpos){
    double z = partpos->GetZ()-defpos->GetZ();
    if(z>0.){
        fDispl->SetX(fBurger->GetModule() * 0.5);
    }
    else{
        fDispl->SetX(0.);
    }
    fDispl->SetY(0.);
    fDispl->SetZ(0.);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_stacking_fault::ComputeBR(ECHARM_3vec* partpos,ECHARM_3vec* defpos){
    fBR->SetX(0.);
    fBR->SetY(0.);
    fBR->SetZ(0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
