//
//  ECHARM_periodicvector.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#include <cfloat>
#include <limits>
#include "ECHARM_periodicvector.hh"

#ifdef ROOT_
#include "TH1D.h"
#include "TH2D.h"
#endif

ECHARM_periodicvector::ECHARM_periodicvector(int* vNumSteps,double* vPeriod){
    fVec.clear();
    
    fNumSteps[0] = vNumSteps[0];
    fNumSteps[1] = vNumSteps[1];
    fNumSteps[2] = vNumSteps[2];
    
    fPeriod[0] = vPeriod[0];
    fPeriod[1] = vPeriod[1];
    fPeriod[2] = vPeriod[2];
    
    fIntrp = new ECHARM_intrp();
    
    fMax = DBL_MAX;
    fMin = DBL_MAX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_periodicvector::ECHARM_periodicvector(int* vNumSteps,ECHARM_3vec* vPeriod){
    fVec.clear();
    
    fNumSteps[0] = vNumSteps[0];
    fNumSteps[1] = vNumSteps[1];
    fNumSteps[2] = vNumSteps[2];
    
    fPeriod[0] = vPeriod->Get(0);
    fPeriod[1] = vPeriod->Get(1);
    fPeriod[2] = vPeriod->Get(2);
    
    fIntrp = new ECHARM_intrp();
    
    fMax = DBL_MAX;
    fMin = DBL_MAX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_periodicvector::~ECHARM_periodicvector(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_periodicvector::Set(std::vector<double> vVec){
    fVec = vVec;
    fMax = *std::min_element(fVec.begin(),fVec.end());
    fMin = *std::max_element(fVec.begin(),fVec.end());
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_periodicvector::ReadFromFile(std::string FileInName){
    std::ifstream FileIn;
    FileIn.open(FileInName.c_str());
    
    if(FileIn.good()) std::cout << "Opening " << FileInName << std::endl;
    if(FileIn.good()) FileIn >> fNumSteps[0] >> fNumSteps[1] >> fNumSteps[2];
    if(FileIn.good()) FileIn >> fPeriod[0] >> fPeriod[1] >> fPeriod[2];
    
    double vDummy;
    
    fVec.clear();
    
    for(int i2=0;i2<fNumSteps[2];i2++){
        for(int i1=0;i1<fNumSteps[1];i1++){
            for(int i0=0;i0<fNumSteps[0];i0++){
                if(FileIn.good()){
                    FileIn >> vDummy;
                    fVec.push_back(vDummy);
                }
            }
        }
    }
    
    FileIn.close();
    
    fMax = *std::min_element(fVec.begin(),fVec.end());
    fMin = *std::max_element(fVec.begin(),fVec.end());
    
    std::cout << "Min val is " << std::setw(10) << fMin << " ---------- " << " Max val is " << std::setw(10) << fMax << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_periodicvector::PrintToFile(std::string FileOutName,std::string vOptions = ""){
    std::ofstream FileOut;
    FileOut.open(FileOutName.c_str());
    
    double vShift = 0;
    if(vOptions != ""){
        vShift = *std::min_element(fVec.begin(),fVec.end());
    }
    
    for(int i2=0;i2<fNumSteps[2];i2++){
        for(int i1=0;i1<fNumSteps[1];i1++){
            for(int i0=0;i0<fNumSteps[0];i0++){
                if(FileOut.good()){
                    FileOut << double(i0)/double(fNumSteps[0])*double(fPeriod[0]) << " ";
                    if(fNumSteps[1] > 1){
                        FileOut << double(i1)/double(fNumSteps[1])*double(fPeriod[1]) << " ";
                    }
                    if(fNumSteps[2] > 1){
                        FileOut << double(i2)/double(fNumSteps[2])*double(fPeriod[2]) << " ";
                    }
                    FileOut << fVec.at(ComputeIndex(i0,i1,i2)) - vShift << std::endl;
                }
            }
        }
    }
    FileOut.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_periodicvector::PrintToTH(std::string vName, std::string vOptions)
{
    if(fNumSteps[1]==1 &&
       fNumSteps[2]==1){
        PrintToTH1(vName,vOptions);
    }
    else if(fNumSteps[2]==1){
        PrintToTH2(vName,vOptions);
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_periodicvector::PrintToTH1(std::string vName, std::string vOptions)
{
    double vAxisXmax = fPeriod[0]/AA;
    std::string vAxisName = vName + ";Horizontal Impact Position [#AA];Electric Characteristic";
    
    if(vOptions == "n"){
        vAxisXmax = 1.;
        vAxisName.clear();
        vAxisName = vName + ";Horizontal Impact Parameter [x/d_{p}];Electric Characteristic";
    }
    double vShift = 0.;
    if(vOptions != ""){
        vShift = *std::min_element(fVec.begin(),fVec.end());
    }
    
    TH1D *vHisto = new TH1D(vName.c_str(),vAxisName.c_str(),fVec.size(),0.0,vAxisXmax);
    for(unsigned int i=0;i <fVec.size();i++){
        vHisto->SetBinContent(i+1,fVec.at(i) - vShift);
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_periodicvector::PrintToTH2(std::string vName, std::string vOptions)
{
    double vAxisXmax = fPeriod[0]/AA;
    double vAxisYmax = fPeriod[1]/AA;
    std::string vAxisName = vName + ";Horizontal Impact Position [#mum];Vertical Impact Position [#mum];Electric Characteristic";
    
    if(vOptions == "n"){
        vAxisXmax = 1.;
        vAxisYmax = 1;
        vAxisName.clear();
        vAxisName = vName + ";Horizontal Impact Parameter [x/d_{px}];Vertical Impact Paramter [y/d_{py}];Electric Characteristic";
    }
    
    double vShift = 0.;
    if(vOptions != ""){
        vShift = *std::min_element(fVec.begin(),fVec.end());
    }
    
    TH2D *vHisto = new TH2D(vName.c_str(),vAxisName.c_str(),fNumSteps[0],0.0,vAxisXmax,fNumSteps[1],0.0,vAxisYmax);
    
    for(int i1=0;i1<fNumSteps[1];i1++){
        for(int i0=0;i0<fNumSteps[0];i0++){
            vHisto->SetBinContent(i0+1,i1+1,fVec.at(ComputeIndex(i0,i1,0)) - vShift);
        }
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_periodicvector::ComputeIndex(int i0,int i1 = 0, int i2 = 0){
    return i0 + fNumSteps[0] * i1 + fNumSteps[1] * fNumSteps[0] * i2;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_periodicvector::GetNorm(){
    std::vector<double> vVec;
    vVec.clear();
    double vSum = 0.0;
    double vElCh = 0.0;
    for(unsigned int i=0;i<fVec.size();i++) {
        vSum += fVec.at(i);
    }
    vSum *= fVec.size();
    for(unsigned int i=0;i<fVec.size();i++){
        vElCh = fVec.at(i) / vSum * fVec.size();
        vVec.push_back(vElCh);
    }
    return vVec;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_periodicvector::GetVal1d(double vX){
    
    double x = fIntrp->GetXinUnitPeriod(vX,fPeriod[0]);
    double stepX = GetStepX();
    int vInt[4];
    vInt[1] = int( x / stepX );
    fIntrp->GetIndexes(vInt,fNumSteps[0]);
    x -= vInt[1] * stepX;

    if(x == 0.0) {
        return fVec.at(vInt[1]);
    }
    else{
        x /= stepX;
        return fIntrp->Get1d(x,fVec.at(vInt[0]),fVec.at(vInt[1]),fVec.at(vInt[2]),fVec.at(vInt[3]));
    }
    
    return 0.0;
    
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_periodicvector::GetVal2d(double vX,double vY){
    
    double x = fIntrp->GetXinUnitPeriod(vX,fPeriod[0]);
    double stepX = GetStepX();
    int vIntX[4];
    vIntX[1] = int( x / stepX );
    fIntrp->GetIndexes(vIntX,fNumSteps[0]);
    x -= vIntX[1] * stepX;
    
    double y = fIntrp->GetXinUnitPeriod(vY,fPeriod[1]);
    double stepY = GetStepY();
    int vIntY[4];
    vIntY[1] = int( y / stepY );
    fIntrp->GetIndexes(vIntY,fNumSteps[1]);
    y -= vIntY[1] * stepY;
    
    if(x == 0.0 && y == 0.0){
        return fVec.at(ComputeIndex(vIntX[0],vIntY[0]));
    }
    else{
        x /= stepX;
        y /= stepY;
        if(DEBUG){
            std::cout << "X " << vIntX[0] << " " << vIntX[1] << " " << vIntX[2] << " " << vIntX[3] << std::endl;
            std::cout << "Y " << vIntY[0] << " " << vIntY[1] << " " << vIntY[2] << " " << vIntY[3] << std::endl;
            std::cout << ComputeIndex(vIntX[0],vIntY[0],0) << std::endl;
            std::cout << ComputeIndex(vIntX[1],vIntY[0],0) << std::endl;
            std::cout << ComputeIndex(vIntX[0],vIntY[1],0) << std::endl;
            std::cout << ComputeIndex(vIntX[1],vIntY[1],0) << std::endl;
            std::cout << fVec.size() << std::endl;
            std::cout << " STOP " << fNumSteps[0] << " " << fNumSteps[1] << std::endl;
        }

        
        double result = fIntrp->Get2d(x,
                                      y,
                                      fVec.at(ComputeIndex(vIntX[0],vIntY[0])),
                                      fVec.at(ComputeIndex(vIntX[0],vIntY[1])),
                                      fVec.at(ComputeIndex(vIntX[0],vIntY[2])),
                                      fVec.at(ComputeIndex(vIntX[0],vIntY[3])),
                                      fVec.at(ComputeIndex(vIntX[1],vIntY[0])),
                                      fVec.at(ComputeIndex(vIntX[1],vIntY[1])),
                                      fVec.at(ComputeIndex(vIntX[1],vIntY[2])),
                                      fVec.at(ComputeIndex(vIntX[1],vIntY[3])),
                                      fVec.at(ComputeIndex(vIntX[2],vIntY[0])),
                                      fVec.at(ComputeIndex(vIntX[2],vIntY[1])),
                                      fVec.at(ComputeIndex(vIntX[2],vIntY[2])),
                                      fVec.at(ComputeIndex(vIntX[2],vIntY[3])),
                                      fVec.at(ComputeIndex(vIntX[3],vIntY[0])),
                                      fVec.at(ComputeIndex(vIntX[3],vIntY[1])),
                                      fVec.at(ComputeIndex(vIntX[3],vIntY[2])),
                                      fVec.at(ComputeIndex(vIntX[3],vIntY[3])));
        return result;
    }
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_periodicvector::GetVal(double vX,double vY,double vZ){
    
    if((fNumSteps[1]==1) &&
       (fNumSteps[2]==1)){
        return GetVal1d(vX);
    }
    else if(fNumSteps[2]==1){
        return GetVal2d(vX,vY);
    }
    else{
        return 0.;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

