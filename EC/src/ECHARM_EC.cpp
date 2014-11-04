//
//  ECHARM_EC.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_EC_h

#include "ECHARM_EC.hh"
#ifdef ROOT_
#include "TH1D.h"
#include "TH2D.h"
#endif

ECHARM_EC::ECHARM_EC(std::string name,ECHARM_crystal *crystal){
    fCrystal = crystal;
    fName = name;
    fMax = 0.;
    fMin = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC::~ECHARM_EC(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_EC::PrintToTH(std::string vOptions)
{
    PrintToTH1(vOptions);
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_EC::PrintToTH1(std::string vOptions)
{
    double vAxisXmax = fCrystal->GetPeriodX()/AA;
    
    std::string vAxisName = fName + ";Horizontal Impact Position [#AA];Electric Characteristic";
    
    if(vOptions == "n"){
        vAxisXmax = 1.;
        vAxisName.clear();
        vAxisName = fName + ";Horizontal Impact Parameter [x/d_{p}];Electric Characteristic";
    }
    double vShift = 0.;
    if(vOptions != ""){
        vShift = atof(vOptions.c_str());
    }
    int nsteps = 4096;
    
    TH1D *vHisto = new TH1D(fName.c_str(),vAxisName.c_str(),nsteps,0.0,vAxisXmax);
    for(int i0=0;i0<nsteps;i0++){
        double x = double(i0)/double(nsteps)*double(fCrystal->GetPeriod(0));
        vHisto->SetBinContent(i0+1,Get(x,0,0) - vShift);
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_EC::PrintToTH2(std::string vOptions){
    int nsteps[2] = {512,512};

    double vAxisXmax = fCrystal->GetPeriod(0)/AA;
    double vAxisYmax = fCrystal->GetPeriod(1)/AA;
    std::string vAxisName = fName + ";Horizontal Impact Position [#mum];Vertical Impact Position [#mum];Electric Characteristic";
    
    if(vOptions == "n"){
        vAxisXmax = 1.;
        vAxisYmax = 1;
        vAxisName.clear();
        vAxisName = fName + ";Horizontal Impact Parameter [x/d_{px}];Vertical Impact Paramter [y/d_{py}];Electric Characteristic";
    }
    
    double vShift = 0.;
    if(vOptions != ""){
        vShift = atof(vOptions.c_str());
    }
    
    TH2D *vHisto = new TH2D(fName.c_str(),vAxisName.c_str(),nsteps[0],0.0,vAxisXmax,nsteps[1],0.0,vAxisYmax);
    
    for(int i1=0;i1<nsteps[1];i1++){
        double y = double(i1)/double(nsteps[1])*double(fCrystal->GetPeriod(1));
        for(int i0=0;i0<nsteps[0];i0++){
            double x = double(i0)/double(nsteps[0])*double(fCrystal->GetPeriod(0));
            vHisto->SetBinContent(i0+1,i1+1,Get(x,y,0) - vShift);
        }
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_EC::PrintToFile(std::string vAddition = "",
                            std::string vOptions = "",
                            std::string vFolder = "ECHARM"){
    std::string vFileName;
    if(vFolder != ""){
        vFileName = vFolder + "/";
    }
    
    int nsteps[3] = {128,128,128};
    
    vFileName += fCrystal->PrintNameOnString(vAddition);
    vFileName += fName;
    vFileName += ".txt";
    
    std::ofstream FileOut;
    FileOut.open(vFileName.c_str());
    
    double vShift = 0;
    if(vOptions != ""){
        vShift = atof(vOptions.c_str());
    }
    
    for(int i2=0;i2<nsteps[2];i2++){
        double z = double(i2)/double(nsteps[2])*double(fCrystal->GetPeriod(2));
        for(int i1=0;i1<nsteps[1];i1++){
            double y = double(i1)/double(nsteps[1])*double(fCrystal->GetPeriod(1));
            for(int i0=0;i0<nsteps[0];i0++){
                double x = double(i0)/double(nsteps[0])*double(fCrystal->GetPeriod(0));
                if(FileOut.good()){
                    FileOut << x << " ";
                    if(nsteps[1] > 1){
                        FileOut << y << " ";
                    }
                    if(nsteps[2] > 1){
                        FileOut << z << " ";
                    }
                    FileOut << Get(x,y,z) - vShift << std::endl;
                }
            }
        }
    }
    
    FileOut.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif