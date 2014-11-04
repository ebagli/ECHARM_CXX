//
//  ECHARM_EC_direct.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_EC_direct_h

#include "ECHARM_EC_direct.hh"


#ifdef ROOT_
#include "TH1D.h"
#include "TH2D.h"
#endif

#ifdef CUDA_
#include <cuda_runtime.h>
#include <cufft.h>
#include <helper_functions.h>
#include <helper_cuda.h>
#include "convolutionFFT2D_common.h"
#endif

ECHARM_EC_direct::ECHARM_EC_direct(std::string name,
                                   ECHARM_crystal *crystal,
                                   int cellnumber = 1):
ECHARM_EC(name,
          crystal){
    fCellNumb = cellnumber;
    fStepNumbPerCell = 128;
    fLimit = 1.E-6 * AA;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_direct::~ECHARM_EC_direct(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_direct::Get(double x, double y, double z){
    
    double vResult = 0;
    
    for(int i0 = -fCellNumb; i0 <= fCellNumb;i0++){
        for(int i1 = -fCellNumb; i1 <= fCellNumb;i1++){
            for(int i2 = -fCellNumb; i2 <= fCellNumb;i2++){
                vResult += GetFunc(x + i0*fCrystal->GetCell()->GetSizes()->GetX(),y + i1*fCrystal->GetCell()->GetSizes()->GetY(),z + i2*fCrystal->GetCell()->GetSizes()->GetZ());
            }
        }
    }
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_direct::Get1d(double x){
    
    double vResult = 0;
    
    double vStepY = fCrystal->GetPeriodY()/fStepNumbPerCell;
    double vStepZ = fCrystal->GetPeriodZ()/fStepNumbPerCell;
    
    
    for(int i2 = -fCellNumb; i2 <= fCellNumb;i2++){
        for(int i1 = 0; i1 <= fStepNumbPerCell;i1++){
            for(int i0 = 0; i0 <= fStepNumbPerCell;i0++){
                vResult += GetFunc(x,vStepY *i0,vStepZ * i1);
            }
        }
    }
    return vResult / fStepNumbPerCell / fStepNumbPerCell;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_direct::Get2d(double x, double y){
    
    double vResult = 0;
    double vStepZ = fCrystal->GetPeriodZ()/fStepNumbPerCell;
    
    for(int i1 = 0; i1 <= fStepNumbPerCell;i1++){
        vResult += (Get(x,y,vStepZ * i1));
    }
    return vResult / fStepNumbPerCell;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_direct::GetFunc(double xpart, double ypart, double zpart){
    double vResult = 0;
    
    for(unsigned int j0 = 0; j0 < fCrystal->GetNumBases();j0++){
        for(int j1 = 0; j1 < fCrystal->GetLattice(j0)->GetCoordinatesNumber();j1++){
            double x = fCrystal->GetLattice(j0)->GetCoordinates().at(j1)->GetX() * fCrystal->GetCell()->GetSizes()->GetX() - xpart;
            double y = fCrystal->GetLattice(j0)->GetCoordinates().at(j1)->GetY() * fCrystal->GetCell()->GetSizes()->GetY() - ypart;
            double z = fCrystal->GetLattice(j0)->GetCoordinates().at(j1)->GetZ() * fCrystal->GetCell()->GetSizes()->GetZ() - zpart;
            double r = fSquareRoot(x*x+y*y+z*z);
            if(r > fLimit){
                vResult += fCrystal->GetAtom(j0)->ComputeFF(r) / r;
            }
        }
    }
    vResult *= cElectronLengthOnCharge; //eV*m on charge evaluated in unit of electron charge
    vResult *= (fCrystal->GetZ());
    
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
