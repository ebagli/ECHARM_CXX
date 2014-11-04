//
//  ECHARM_EC_rec.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_EC_rec_h

#include "ECHARM_EC_rec.hh"


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

ECHARM_EC_rec::ECHARM_EC_rec(std::string name,
                             ECHARM_crystal *crystal,
                             int recX,
                             int recY,
                             int recZ):
ECHARM_EC(name,
          crystal){
    
    fFTN[0] = recX;
    fFTN[1] = recY;
    fFTN[2] = recZ;
    fPhaseCos = 0.;
    fPhaseSin = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_rec::~ECHARM_EC_rec(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_EC_rec::GetIndexRe(int i0,int i1,int i2){
    return ((+i0+fFTN[0])*2+
            2.*(i1+fFTN[1])*(fFTN[0]*2+1)+
            2.*(i2+fFTN[2])*(fFTN[1]*2+1)*(fFTN[0]*2+1));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_EC_rec::GetIndexIm(int i0,int i1,int i2){
    return (GetIndexRe(i0,i1,i2)+1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_EC_rec::PrintSFtoTH(std::vector<double> cReIm,std::string name){
    if((fFTN[1]==0) &&
       (fFTN[2]==0)){
        PrintSFtoTH1(fFFC,fName);
    }
    else if(fFTN[2]==0){
        PrintSFtoTH2(fFFC,fName);
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_EC_rec::PrintSFtoTH1(std::vector<double> cReIm,std::string name){
    std::string vBaseName = fCrystal->GetAtomName();
    
    std::string vHistoName = name + "Re";
    TH1F *vHistoCRe = new TH1F(vHistoName.c_str(),vHistoName.c_str(),fFTN[0]*2+1,-float(fFTN[0]),+float(fFTN[0]));
    for(int i=-fFTN[0];i<=fFTN[0];i++){
        vHistoCRe->SetBinContent(i+fFTN[0]+1,cReIm.at(GetIndexRe(i,0,0)));
    }
    
    vHistoName = name + "Im";
    TH1F *vHistoCIm = new TH1F(vHistoName.c_str(),vHistoName.c_str(),fFTN[0]*2+1,-float(fFTN[0]),+float(fFTN[0]));
    for(int i=-fFTN[0];i<=fFTN[0];i++)
        vHistoCIm->SetBinContent(i+fFTN[0]+1,cReIm.at(GetIndexIm(i,0,0)));
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_EC_rec::PrintSFtoTH2(std::vector<double> cReIm,std::string name){
    
    std::string vHistoName = name + "Re";
    TH2F *vHistoCRe = new TH2F(vHistoName.c_str(),vHistoName.c_str(),fFTN[0]*2+1,-float(fFTN[0]),+float(fFTN[0]),fFTN[1]*2+1,-float(fFTN[1]),+float(fFTN[1]));
    for(int i1=-fFTN[1];i1<=fFTN[1];i1++)
        for(int i0=-fFTN[0];i0<=fFTN[0];i0++){
            vHistoCRe->SetBinContent(i0+fFTN[0]+1,i1+fFTN[1]+1,cReIm.at(GetIndexRe(i0,i1,0)));
        }
    
    vHistoName = name + "Im";
    TH2F *vHistoCIm = new TH2F(vHistoName.c_str(),vHistoName.c_str(),fFTN[0]*2+1,-float(fFTN[0]),+float(fFTN[0]),fFTN[1]*2+1,-float(fFTN[1]),+float(fFTN[1]));
    for(int i1=-fFTN[1];i1<=fFTN[1];i1++)
        for(int i0=-fFTN[0];i0<=fFTN[0];i0++){
            vHistoCIm->SetBinContent(i0+fFTN[0]+1,i1+fFTN[1]+1,cReIm.at(GetIndexIm(i0,i1,0)));
        }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
// std::vector<double> x -> describe  x[0]=re[0] x[1]=im[0] x[2]=re[1] x[3]=im[1] x[4]=re[2] x[5]=im[2] ...
// x[even] = re ; x[odd] = im
//
void ECHARM_EC_rec::StoreRecFF(){
    
    fFFC.clear();
    
    for(int i2=-fFTN[2];i2<=fFTN[2];i2++){
        for(int i1=-fFTN[1];i1<=fFTN[1];i1++){
            for(int i0=-fFTN[0];i0<=fFTN[0];i0++){
                double cRe = 0.0;
                double cIm = 0.0;
                
                int vIndex[3];
                if(GetIndexesSF(vIndex,i0,i1,i2)){
                    std::vector<double> sfReIm = ComputeRecFF(vIndex);
                    
                    if((vIndex[0] != 0) ||
                       (vIndex[1] != 0) ||
                       (vIndex[2] != 0)){
                        for(unsigned int j=0;j<fCrystal->GetNumBases();j++){
                            cRe += sfReIm[2*j];
                            cIm += sfReIm[2*j+1];
                        }
                    }
                }
                                
                fFFC.push_back(cRe);
                fFFC.push_back(cIm);
            }
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_rec::GetFT(double x, double y, double z, std::vector<double>& fc){
    
    double vResult = 0;
    double vAngle = 0.;
    int vIndexSF[3];
    double vIndexEC[3];

#ifdef CUDA_
    if(fFTN[1]==0 &&
       fFTN[2]==0){
        return GetFT1D_CUDA(x,fc);
    }
#endif
    
    for(int i0 = -fFTN[0]; i0 <= fFTN[0];i0++){
        for(int i1 = -fFTN[1]; i1 <= fFTN[1];i1++){
            for(int i2 = -fFTN[2]; i2 <= fFTN[2];i2++){
                if(GetIndexesSF(vIndexSF,i0,i1,i2)){
                    
                    if(GetIndexesEC(vIndexEC,vIndexSF,i0,i1,i2)){
                    
                        
                        vAngle  = fCrystal->GetRecPeriodX() * x * vIndexEC[0];
                        if(fFTN[1] != 0) {
                            vAngle += fCrystal->GetRecPeriodY() * y * vIndexEC[1];
                        }
                        if(fFTN[2] != 0) {
                            vAngle += fCrystal->GetRecPeriodZ() * z * vIndexEC[2];
                        }

                        vResult += (GetFactorRe(vIndexEC) * fc.at(GetIndexRe(i0,i1,i2)) * cos(vAngle + fPhaseCos));
                        vResult += (GetFactorIm(vIndexEC) * fc.at(GetIndexIm(i0,i1,i2)) * sin(vAngle + fPhaseSin));


                    }
                }
            }
        }
    }
    
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef CUDA_
double ECHARM_EC_rec::GetFT1D_CUDA(double x, std::vector<double>& fc){

}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif