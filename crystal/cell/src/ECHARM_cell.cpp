//
//  ECHARM_cell.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_cell.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_cell::ECHARM_cell(double Size00, double Size01, double Size02, double Angle00, double Angle01, double Angle02)
{
    fSize = new ECHARM_3vec();
    fAngle = new ECHARM_3vec();
    
    fSize->Set(Size00,Size01,Size02);
    fAngle->Set(Angle00*deg,Angle01*deg,Angle02*deg);

    fVolume = ComputeVolume();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_cell::ECHARM_cell(double Size00, double Size01, double Size02)
{
    fSize = new ECHARM_3vec();
    fAngle = new ECHARM_3vec();
    fVolume = 0.;
    
    fSize->Set(Size00,Size01,Size02);
    fAngle->Set(cPiHalf,cPiHalf,cPiHalf);

    fVolume = ComputeVolume();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_cell::~ECHARM_cell(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_cell::CheckCell()
{
    if(fSize->Get(0)!=0.0)
        if(fSize->Get(1)!=0.0)
            if(fSize->Get(2)!=0.0)
                if(fAngle->Get(0) > 0.0)
                    if(fAngle->Get(1) > 0.0)
                        if(fAngle->Get(2) > 0.0)
                            return 1;
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_cell::IsOrthogonal()
{
    if(fAngle->Get(0) == cPiHalf)
        if(fAngle->Get(1) == cPiHalf)
            if(fAngle->Get(2) == cPiHalf)
                return 1;
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_cell::Print()
{
    std::cout << "ECHARM_cell - Print Cell Properties" << std::endl;
    std::cout << "Size      X_0 [A]   Y_0 [A]   Z_0 [A]"<< std::endl;
    fSize->Print(1./AA);
    std::cout << "Angles   Alfa [°]  Beta [°] Gamma [°]" << std::endl;
    fAngle->Print(1./deg);
    std::cout << "Volume      [A^3]"<< std::endl;
    std::cout << "       " << std::setw(10) << std::setprecision(3) << fVolume/AA/AA/AA << std::endl;
    if(IsOrthogonal()) {
        std::cout << "Is Orthogonal" << std::endl;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::ComputeVolume()
{
    double vResult = fSize->Get(0)*fSize->Get(1)*fSize->Get(2);
    if(!IsOrthogonal()){
        double cosA = cos(fAngle->Get(0));
        double cosB = cos(fAngle->Get(1));
        double cosC = cos(fAngle->Get(2));
        vResult *= fSquareRoot(1.+2.*cosA*cosB*cosC-cosA*cosA-cosB*cosB-cosC*cosC);
    }
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::ComputeRecVec2(int vIndex[3])
{
    double double_result = 0.0;
    double double_temp[6];
    int i;
    
    if(IsOrthogonal()){
        for(i=0;i<3;i++) double_result += fSquare(vIndex[i] / fSize->Get(i));
    }
    else{
        double_temp[0] = fSize->Get(1) * fSize->Get(2) * sin(fAngle->Get(1));
        double_temp[1] = fSize->Get(0) * fSize->Get(2) * sin(fAngle->Get(0));
        double_temp[2] = fSize->Get(0) * fSize->Get(1) * sin(fAngle->Get(2));
        double_temp[3] = fSize->Get(0) * fSize->Get(1) * fSize->Get(2) * fSize->Get(2) * (cos(fAngle->Get(0)) * cos(fAngle->Get(1)) - cos(fAngle->Get(2)));
        double_temp[4] = fSize->Get(0) * fSize->Get(1) * fSize->Get(1) * fSize->Get(2) * (cos(fAngle->Get(2)) * cos(fAngle->Get(0)) - cos(fAngle->Get(1)));
        double_temp[5] = fSize->Get(0) * fSize->Get(0) * fSize->Get(1) * fSize->Get(2) * (cos(fAngle->Get(1)) * cos(fAngle->Get(2)) - cos(fAngle->Get(0)));
        
        for(i=0;i<3;i++){
            double_temp[i] = double_temp[i] * double_temp[i] * vIndex[i] * vIndex[i];
        }
        double_temp[3] *= (2 * vIndex[0] * vIndex[1]);
        double_temp[4] *= (2 * vIndex[2] * vIndex[0]);
        double_temp[5] *= (2 * vIndex[2] * vIndex[2]);
        
        for(i=0;i<6;i++){
            double_result += double_temp[i];
        }
        
        double_result /= (fVolume * fVolume);
    }
    
    double_result *= (4 * cPi * cPi);
    return double_result;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::ComputeRecVec2(int vIndex00,int vIndex01, int vIndex02)
{
    int vIndex_vector[3] = {vIndex00,vIndex01,vIndex02};
    return ComputeRecVec2(vIndex_vector);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::ComputeVec2(int vIndex[3])
{
    return 1./ComputeRecVec2(vIndex)*4.*cPi*cPi;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::ComputeVec2(int vIndex00,int vIndex01, int vIndex02)
{
    int vIndex_vector[3] = {vIndex00,vIndex01,vIndex02};
    return ComputeVec2(vIndex_vector);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::ComputePeriod(int vIndex[3]){
    return fSquareRoot(1./ComputeRecVec2(vIndex))*2.*cPi;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::ComputePeriod(int vIndex00,int vIndex01, int vIndex02){
    int vIndex_vector[3] = {vIndex00,vIndex01,vIndex02};
    return ComputePeriod(vIndex_vector);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::ComputeRecPeriod(int vIndex[3]){
    return fSquareRoot(ComputeRecVec2(vIndex));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::ComputeRecPeriod(int vIndex00,int vIndex01, int vIndex02)
{
    int vIndex_vector[3] = {vIndex00,vIndex01,vIndex02};
    return ComputeRecPeriod(vIndex_vector);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
