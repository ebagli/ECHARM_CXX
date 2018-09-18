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
    
    double vPeriod[3];
    int vNumStep[3];
    
    for(unsigned int i=0;i<3;i++){
        vPeriod[i] = fCrystal->GetPeriod(i);
        if(fFTN[i]==0) vNumStep[i]=1;
        else vNumStep[i]=fFTN[i];
    }
    
    fVec = new ECHARM_periodicvector(vNumStep,vPeriod);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_rec::~ECHARM_EC_rec(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_EC_rec::GetIndex(int i0,int i1,int i2){
    return ((+i0+fFTN[0])+
            (i1+fFTN[1])*(fFTN[0]+1)+
            (i2+fFTN[2])*(fFTN[1]+1)*(fFTN[0]+1));
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
                double vIndexEC[3];
                if(GetIndexesSF(vIndex,i0,i1,i2)){
                    if(GetIndexesEC(vIndexEC,vIndex,i0,i1,i2)){
                    std::vector<double> sfReIm = ComputeRecFF(vIndex,vIndexEC);
                    
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

void ECHARM_EC_rec::PrintCoeffToFile(std::string filename,bool invertReIm = false,std::string ectype = ""){
    if(fFFC.size() == 0){
        StoreRecFF();
    }
    std::ofstream myfileRe;
    std::ofstream myfileIm;
    std::string filenameOutRe = filename + "_Re.txt";
    std::string filenameOutIm = filename + "_Im.txt";
    if(invertReIm==false){
        myfileRe.open (filenameOutRe);
        myfileIm.open (filenameOutIm);
    }
    else{
        myfileRe.open (filenameOutIm);
        myfileIm.open (filenameOutRe);
    }
    
    double coeff = 1.;
    
    if(ectype=="pot" || ectype=="efx" || ectype=="efy" || ectype=="efz"){
        coeff *= cElectronLengthOnCharge; //eV*m on charge evaluated in unit of electron charge
        coeff /= fCrystal->GetCell()->GetVolume();
    }
    else if(ectype=="atd"){
        coeff /= (fCrystal->GetNumCoord());
    }
    else if(ectype=="eld"){
        coeff /= (fCrystal->GetNumCoord() * fCrystal->GetZ());
    }

    if(fFTN[2]==0 and fFTN[1]==0){
        for(int i0=-fFTN[0];i0<fFTN[0];i0++){
            if(i0==0 && ectype=="atd"){
                myfileRe << i0 << " " << 1 << std::endl;
                myfileIm << i0 << " " << 0. << std::endl;
            }
            else if(i0==0 && ectype=="eld"){
                myfileRe << i0 << " " << 1 << std::endl;
                myfileIm << i0 << " " << 0. << std::endl;
            }
            else{
                myfileRe << i0 << " " << coeff*fFFC.at(GetIndexRe(i0,0,0)) << std::endl;
                myfileIm << i0 << " " << coeff*fFFC.at(GetIndexIm(i0,0,0)) << std::endl;
            }
        }
    }
    else{
        for(int i1=-fFTN[1];i1<fFTN[1];i1++){
            for(int i0=-fFTN[0];i0<fFTN[0];i0++){
                if(i0==0 && i1==0){
                    if(ectype=="atd"){
                        myfileRe << i0 << " " << i1 << " " << 1. << std::endl;
                        myfileIm << i0 << " " << i1 << " " << 0. << std::endl;
                    }
                    else if(ectype=="eld"){
                        myfileRe << i0 << " " << i1 << " " << 1. << std::endl;
                        myfileIm << i0 << " " << i1 << " " << 0. << std::endl;
                    }
                    else{
                        myfileRe << i0 << " " << i1 << " " << 0. << std::endl;
                        myfileIm << i0 << " " << i1 << " " << 0. << std::endl;
                    }
                }
                else{
                    myfileRe << i0 << " " << i1 << " " << coeff*fFFC.at(GetIndexRe(i0,i1,0)) << std::endl;
                    myfileIm << i0 << " " << i1 << " " << coeff*fFFC.at(GetIndexIm(i0,i1,0)) << std::endl;
                }
                /*
                 myfileRe << fFFC.at(GetIndexRe(i0,i1,0));
                 if(i0!=fFTN[0]-1) myfileRe << ",";
                 else myfileRe << std::endl;
                 
                 myfileIm << fFFC.at(GetIndexIm(i0,i1,0));
                 if(i0!=fFTN[0]-1) myfileIm << ",";
                 else myfileIm << std::endl;
                 */
            }
        }
    }
    myfileRe.close();
    myfileIm.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ECHARM_EC_rec::StoreValues(){
#ifdef USE_FFWT3
    if(fFTN[2]==0 and fFTN[1]==0){
        std::cout << "1D" << std::endl;
        int Nx = int(fFTN[0]*2);
        
        fftw_complex in[Nx];
        fftw_complex out[Nx];
        fftw_plan p;
        
        p = fftw_plan_dft_1d(Nx, &in[0], &out[0], FFTW_BACKWARD, FFTW_MEASURE);
        
        int j0 = 0;
        for(int i0=0;i0<Nx;i0++){
            j0 = i0;
            if(i0>fFTN[0]){
                j0 = i0 - Nx;
            }
            in[i0][0] = fFFC.at(GetIndexRe(j0,0,0));
            in[i0][1] = fFFC.at(GetIndexIm(j0,0,0));
            
            if(i0>fFTN[0])
            std::cout << i0 << " " << in[i0][0] << std::endl;
        }
        
        fftw_execute(p); /* repeat as needed */
        
        std::vector<double> vec;
        for(int i0=0;i0<Nx;i0++){
            vec.push_back(out[i0][0]*2.);
        }

        fVec->Set(vec);
        fftw_destroy_plan(p);
    }
    else if(fFTN[2]==0){
        std::cout << "2D" << std::endl;
        int NxDouble  = fFTN[0]*2;
        int NyDouble  = fFTN[1]*2;
        int Nx = NxDouble*0.5;
        int Ny = NyDouble*0.5;
        
        fftw_complex in00[NxDouble][NyDouble];
        fftw_complex out00[NxDouble][NyDouble];

        fftw_plan p00;
        
        int vIndexSF[3];
        double vIndexEC[3];
        
        //std::cout << fFFC.size() << std::endl;


        for(int j1=-Ny;j1<0;j1++){
            for(int j0=-Nx;j0<0;j0++){
                if(GetIndexesSF(vIndexSF,j0,j1,0)){
                    if(GetIndexesEC(vIndexEC,vIndexSF,j0,j1,0)){
                        in00[Nx+j0][Ny+j1][0] = fFFC.at(GetIndexRe(j0,j1,0));
                        in00[Nx+j0][Ny+j1][1] = fFFC.at(GetIndexIm(j0,j1,0));
                    }
                }
            }
        }
        
        for(int j1=-Ny;j1<0;j1++){
            for(int j0=0;j0<Nx;j0++){
                if(GetIndexesSF(vIndexSF,j0,j1,0)){
                    if(GetIndexesEC(vIndexEC,vIndexSF,j0,j1,0)){
                        in00[-Nx+j0][Ny+j1][0] = fFFC.at(GetIndexRe(j0,j1,0));
                        in00[-Nx+j0][Ny+j1][1] = fFFC.at(GetIndexIm(j0,j1,0));
                    }
                }
            }
        }

        for(int j1=0;j1<Ny;j1++){
            for(int j0=-Nx;j0<0;j0++){
                if(GetIndexesSF(vIndexSF,j0,j1,0)){
                    if(GetIndexesEC(vIndexEC,vIndexSF,j0,j1,0)){
                        in00[+Nx+j0][-Ny+j1][0] = fFFC.at(GetIndexRe(j0,j1,0));
                        in00[+Nx+j0][-Ny+j1][1] = fFFC.at(GetIndexIm(j0,j1,0));
                    }
                }
            }
        }

        for(int j1=0;j1<Ny;j1++){
            for(int j0=0;j0<Nx;j0++){
                if(GetIndexesSF(vIndexSF,j0,j1,0)){
                    if(GetIndexesEC(vIndexEC,vIndexSF,j0,j1,0)){
                        in00[-Nx+j0][-Ny+j1][0] = fFFC.at(GetIndexRe(j0,j1,0));
                        in00[-Nx+j0][-Ny+j1][1] = fFFC.at(GetIndexIm(j0,j1,0));
                    }
                }
            }
        }
        
        for(int j1=0;j1<NyDouble;j1++){
            for(int j0=0;j0<NxDouble;j0++){
                out00[j0][j1][0] = 0.;
                out00[j0][j1][1] = 0.;
            }
        }
        p00 = fftw_plan_dft_2d(NxDouble, NyDouble, &in00[0][0], &out00[0][0], FFTW_BACKWARD, FFTW_ESTIMATE);
        fftw_execute(p00);
        fftw_destroy_plan(p00);

        std::cout << "OK5" << std::endl;


        std::vector<double> vec;
        for(int i1=0;i1<NyDouble;i1++){
            for(int i0=0;i0<NxDouble;i0++){
                double res=0.;
                res += out00[i0][i1][1];
                vec.push_back(res);
            }
        }
        fVec->Set(vec);

    }
    else{
        std::cout << "3D" << std::endl;
        int Nx  = fFTN[0]*2;
        int Ny  = fFTN[1]*2;
        int Nz  = fFTN[2]*2;
        
        int Nxh = Nx*0.5;
        int Nyh = Ny*0.5;
        int Nzh = Nz*0.5;

        fftw_complex *in;
        fftw_complex *out;

        in = (fftw_complex*) fftw_malloc ( sizeof ( fftw_complex ) * Nx * Ny * Nz);
        out = (fftw_complex*) fftw_malloc ( sizeof ( fftw_complex ) * Nx * Ny * Nz );

        fftw_plan p;
        
        int vIndexSF[3];
        double vIndexEC[3];
        
        int i0,i1,i2;
        std::cout << fFFC.size() << std::endl;
        std::cout << Nx * Ny * Nz << std::endl;

        for(int j2=0;j2<Nz;j2++){
            for(int j1=0;j1<Ny;j1++){
                for(int j0=0;j0<Nx;j0++){
                    i0 = j0;
                    i1 = j1;
                    i2 = j2;
                    
                    if(j0>=Nxh) i0 = -Nx+j0;
                    if(j1>=Nyh) i1 = -Ny+j1;
                    if(j2>=Nzh) i2 = -Nz+j2;
                    /*
                    std::cout << (j0*Ny+j1)*Nz+j2 << std::endl;
                    std::cout << j0 << " " << j1 << " " << j2 << std::endl;
                    std::cout << i0 << " " << i1 << " " << i2 << std::endl;
                    */
                    in[(j0*Ny+j1)*Nz+j2][0] = 0.;
                    in[(j0*Ny+j1)*Nz+j2][1] = 0.;
                    
                    if(GetIndexesSF(vIndexSF,i0,i1,i2)){
                        if(GetIndexesEC(vIndexEC,vIndexSF,i0,i1,i2))
                        {
                            /*
                            std::cout << vIndexEC[0] << " " << vIndexEC[1] << " " << vIndexEC[2] << std::endl;
                            std::cout << vIndexSF[0] << " " << vIndexSF[1] << " " << vIndexSF[2] << std::endl;
                            std::cout << GetIndexRe(i0,i1,i2) << " " << GetIndexIm(i0,i1,i2) << std::endl;
                            std::cout << std::endl;
                            */
                            in[(j0*Ny+j1)*Nz+j2][0] = fFFC.at(GetIndexRe(i0,i1,i2));
                            in[(j0*Ny+j1)*Nz+j2][1] = fFFC.at(GetIndexIm(i0,i1,i2));
                        }
                    }
                }
            }
        }
        
        p = fftw_plan_dft_3d(Nx, Ny, Nz, in,out, FFTW_BACKWARD, FFTW_ESTIMATE);
        
        fftw_execute(p); /* repeat as needed */
        
        std::vector<double> vec;
        for(int j2=0;j2<Nz;j2++){
            for(int j1=0;j1<Ny;j1++){
                for(int j0=0;j0<Nx;j0++){
                    vec.push_back(out[(j0*Ny+j1)*Nz+j2][0]);
                }
            }
        }
        fVec->Set(vec);
        fftw_destroy_plan(p);
    }
    
#endif
    return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_rec::GetFT(double x, double y, double z, std::vector<double>& fc){
    
#ifdef USE_FFWT3
    return fVec->GetVal(x,y,z);
#endif
    
    double vResult = 0;
    double vAngle = 0.;
    int vIndexSF[3];
    double vIndexEC[3];
    
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
                        
                        vResult += (+ (fc.at(GetIndexRe(i0,i1,i2))) * cos(vAngle + fPhaseCos));
                        vResult += (- (fc.at(GetIndexIm(i0,i1,i2))) * sin(vAngle + fPhaseSin));
                        
                        
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
