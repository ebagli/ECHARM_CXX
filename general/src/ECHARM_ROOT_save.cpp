//
//  ECHARM_ROOT_save.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_ROOT_save.hh"

ECHARM_ROOT_save::ECHARM_ROOT_save(std::string name){
    
    vRootFile = new TFile(name.c_str(),"RECREATE");
    
    fTree = new TTree("sim","DYNECHARM Simulation");
    
    fTree->Branch("partIn",&partIn,"posXin/D:posYin/D:posZin/D:angXin/D:angYin/D:momZin/D");
    fTree->Branch("partOut",&partOut,"posXout/D:posYout/D:posZout/D:angXout/D:angYout/D:momZout/D");
    fTree->Branch("enBin", &enBin, "enBin/I");
    fTree->Branch("enVec",&enVec,"enVec[enBin]/D");
    fTree->Branch("enVecX",&enVecX,"enVecX[enBin]/D");
    fTree->Branch("atd",&atd,"atd/D");
    fTree->Branch("eld",&eld,"eld/D");
    
    fTreeTraj = new TTree("traj","DYNECHARM Simulation");
    fTreeTraj->Branch("step",&partStep,"posX/D:posY/D:posZ/D:angX/D:angY/D:momZ/D");
    fTreeTraj->Branch("atd",&atd,"atd/D");
    fTreeTraj->Branch("eld",&eld,"eld/D");
    fTreeTraj->Branch("strip",&brstep,"br/D");
    fTreeTraj->Branch("displX",&displx,"displX/D");
    fTreeTraj->Branch("displY",&disply,"displY/D");
    fTreeTraj->Branch("displZ",&displz,"displZ/D");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_ROOT_save::~ECHARM_ROOT_save(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_ROOT_save::Save(ECHARM_info_save* info){
    
    atd= info->GetAvgAtD();
    eld= info->GetAvgElD();

    partIn = info->GetPartIn();
    partOut = info->GetPartOut();
    
    enBin = info->GetRadEmEnProb().size();
    
    for(int i0=0;i0<enBin;i0++){
        enVec[i0] = info->GetRadEmEnProb().at(i0);
        enVecX[i0] = info->GetRadEmEn().at(i0);
    }
    for(int i0=enBin;i0<MAX_EN_BIN;i0++){
        enVec[i0] = 0.;
        enVecX[i0] = 0.;
    }
    
    for(unsigned int i0=0;i0<info->GetAtD().size();i0++){
        partStep = info->GetPartVec().at(i0);
        atd = info->GetAtD().at(i0);
        eld = info->GetElD().at(i0);
        brstep = 0.;
        displx = 0.;
        disply = 0.;
        displz = 0.;
        fTreeTraj->Fill();
    }
    
    fTree->Fill();
    //fTree->AutoSave();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_ROOT_save::Analysis(){
    
    long part_num = fTree->GetEntries();
    
    double vX[enBin];
    double vY[enBin];
    
    for(int i0=0;i0<enBin;i0++){
        vY[i0] = enVec[i0] * MeV / part_num;
        vX[i0] = enVecX[i0] / MeV;
    }

    TGraph* hRad = new TGraph(enBin,vX,vY);
    hRad->GetXaxis()->SetTitle("Photon Energy [MeV]");
    hRad->GetYaxis()->SetTitle("Spectral Intensity [1/MeV]");
    hRad->Write("hRad");

    for(int i0=0;i0<enBin;i0++){
        vY[i0] = enVec[i0] * enVecX[i0] / part_num;
        vX[i0] = enVecX[i0] / MeV;
    }
    
    TGraph* hRadE = new TGraph(enBin,vX,vY);
    hRadE->GetXaxis()->SetTitle("Photon Energy [MeV]");
    hRadE->GetYaxis()->SetTitle("Radiation Emission Probability");
    hRadE->Write("hRadE");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_ROOT_save::Close(){
    
    vRootFile->Write(); // write ROOT file
    vRootFile->Close(); // close ROOT file
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
