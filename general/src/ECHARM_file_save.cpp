//
//  ECHARM_file_save.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_file_save_h

#include "ECHARM_file_save.hh"

ECHARM_file_save::ECHARM_file_save(std::string name){
    fFilename = name;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_file_save::~ECHARM_file_save(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_file_save::UpdateInfo(ECHARM_info_save* info){
    
    partNum = info->GetPartNum();
    
    charge = info->GetCharge();
    mass = info->GetMass();
    
    atd= info->GetAvgAtD();
    eld= info->GetAvgElD();
    
    displx = info->GetDispl()->GetX();
    disply = info->GetDispl()->GetY();
    displz = info->GetDispl()->GetZ();

    dchTimes = info->GetDechTimes();
    chTimes = info->GetChTimes();
    chIn = info->GetChInitial();
    
    partIn = info->GetPartIn();
    partOut = info->GetPartOut();
    
    enBin = int(info->GetRadEmEnProb().size());
    
    for(int i0=0;i0<enBin;i0++){
        enVec[i0] = info->GetRadEmEnProb().at(i0);
        enVecX[i0] = info->GetRadEmEn().at(i0);
    }
    for(int i0=enBin;i0<MAX_EN_BIN;i0++){
        enVec[i0] = 0.;
        enVecX[i0] = 0.;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_file_save::UpdateInfoTraj(ECHARM_info_save* info,int i0){
        partStep = info->GetPartVec().at(i0);
        atd = info->GetAtD().at(i0);
        eld = info->GetElD().at(i0);
        brstep = 0.;
        displx = 0.;
        disply = 0.;
        displz = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_file_save::Open(){
    std::cout << "Opening Out File... " << fFilename;
    fFileOut.open(fFilename.c_str());
    std::cout << " ...Opened" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_file_save::Save(ECHARM_info_save* info){
    UpdateInfo(info);

    for(unsigned int i0=0;i0<info->GetAtD().size();i0++){
        UpdateInfoTraj(info,i0);
    }
    
    fFileOut << partIn.angx << " " << partIn.angy << " " << partOut.angx  << " " << partOut.angy << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_file_save::Analysis(){

    std::ifstream vFileHistoIn;
    vFileHistoIn.open(fFilename.c_str());

    double angXin,angYin,angXout,angYout;
    
    int vBinNumber = 512;
    double vBinMin = -1024.;
    double vBinMax = +1024.;
    double vBinStep = (vBinMax-vBinMin)/double(vBinNumber);
    int vBinContent[vBinNumber];
    
    int vBin;
    for(int i=0;i<vBinNumber;i++){
        vBinContent[i] = 0;
    }
    
    while(vFileHistoIn >> angXin){
        vFileHistoIn >> angYin >> angXout >> angYout;
        vBin = int((-(angXout-angXin)-vBinMin)/(vBinStep));
        vBinContent[vBin]++;
    }
    vFileHistoIn.close();

    std::ofstream vFileHistoOut;
    std::string vFilename;
    vFilename = fFilename + ".histo.txt";
    vFileHistoOut.open(vFilename.c_str());
    for(int i=0;i<vBinNumber;i++){
        vFileHistoOut << (vBinMin + vBinStep * (i + 1.5))/1000. << " " << vBinContent[i] << std::endl;
    }
    vFileHistoOut.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_file_save::Close(){
    std::cout << "Closing Out File... " << fFilename;
    fFileOut.close();
    std::cout << " ...Closed" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif