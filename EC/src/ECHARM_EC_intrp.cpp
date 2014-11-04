//
//  ECHARM_EC_intrp.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#include <cfloat>
#include <limits>
#include "ECHARM_EC_intrp.hh"


ECHARM_EC_intrp::ECHARM_EC_intrp(std::string name,
                                                 ECHARM_crystal *crystal,
                                                 int StepX,
                                                 int StepY,
                                                 int StepZ):
ECHARM_EC(name,
          crystal){

    fNumSteps[0] = StepX;
    fNumSteps[1] = StepY;
    fNumSteps[2] = StepZ;
    
    double vPeriod[3];

    for(unsigned int i=0;i<3;i++){
        fStep[i] = ComputeStep(i);
        vPeriod[i] = fCrystal->GetPeriod(i);
    }
    
    fVec = new ECHARM_periodicvector(fNumSteps,vPeriod);
    fVec->SetName(name);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_intrp::~ECHARM_EC_intrp(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_EC_intrp::PrintToTH(std::string vOptions)
{
    if(fNumSteps[1]==1){
        PrintToTH1(vOptions);
    }
    else{
        PrintToTH2(vOptions);
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_EC_intrp::Store(ECHARM_EC* vEC){
    
    std::vector<double> vec;
    for(int i2=0;i2<fNumSteps[2];i2++){
        double z = double(i2) * fStep[2];
        
        for(int i1=0;i1<fNumSteps[1];i1++){
            double y = double(i1) * fStep[1];
            for(int i0=0;i0<fNumSteps[0];i0++){
                double x = double(i0) * fStep[0];
                vec.push_back(vEC->Get(x,y,z));
            }
            if(fNumSteps[1] > 1){
                std::cout << "Computing... " << i1 << " of " << fNumSteps[1] << std::endl;
            }
        }
    }
    fVec->Set(vec);
    std::cout << fName << " Map Stored" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
double ECHARM_EC_intrp::Get(double x,double y,double z){
    return fVec->GetVal(x,y,z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
