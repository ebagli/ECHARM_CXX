//
//  ECHARM_ROOT_save.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_ROOT_save_h

#include "ECHARM_ROOT_save.hh"

ECHARM_ROOT_save::ECHARM_ROOT_save(std::string name):ECHARM_file_save(name){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_ROOT_save::~ECHARM_ROOT_save(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_ROOT_save::Open(){
    std::cout << "Opening ROOT File... " << fFilename;
    vRootFile = new TFile(fFilename.c_str(),"RECREATE");
    
    fTree = new TTree("sim","DYNECHARM Simulation");
    
    fTree->Branch("partIn",&partIn,"posXin/D:posYin/D:posZin/D:angXin/D:angYin/D:momZin/D");
    fTree->Branch("partOut",&partOut,"posXout/D:posYout/D:posZout/D:angXout/D:angYout/D:momZout/D");
    fTree->Branch("enBin", &enBin, "enBin/I");
    fTree->Branch("enVec",&enVec,"enVec[enBin]/D");
    fTree->Branch("enVecX",&enVecX,"enVecX[enBin]/D");
    fTree->Branch("atd",&atd,"atd/D");
    fTree->Branch("eld",&eld,"eld/D");
    fTree->Branch("ch",&chTimes,"ch/I");
    fTree->Branch("chin",&chIn,"chin/I");
    fTree->Branch("dch",&dchTimes,"dch/I");
    fTree->Branch("num",&partNum,"num/I");
    fTree->Branch("mass",&mass,"mass/D");
    fTree->Branch("charge",&charge,"charge/D");
    fTree->Branch("displX",&displx,"displX/D");
    fTree->Branch("displY",&disply,"displY/D");
    fTree->Branch("displZ",&displz,"displZ/D");
    fTree->Branch("beamX",&beamx,"beamX/D");
    fTree->Branch("beamY",&beamy,"beamY/D");
    fTree->Branch("beamZ",&beamz,"beamZ/D");
    
    fTreeTraj = new TTree("traj","DYNECHARM Simulation");
    fTreeTraj->Branch("step",&partStep,"posX/D:posY/D:posZ/D:angX/D:angY/D:momZ/D");
    fTreeTraj->Branch("partIn",&partIn,"posXin/D:posYin/D:posZin/D:angXin/D:angYin/D:momZin/D");
    fTreeTraj->Branch("atd",&atd,"atd/D");
    fTreeTraj->Branch("eld",&eld,"eld/D");
    fTreeTraj->Branch("strip",&brstep,"br/D");
    fTreeTraj->Branch("pot",&pot,"pot/D");
    fTreeTraj->Branch("kin",&kin,"kin/D");
    fTreeTraj->Branch("efx",&efx,"efx/D");
    fTreeTraj->Branch("ch",&chTimes,"ch/I");
    fTreeTraj->Branch("chin",&chIn,"chin/I");
    fTreeTraj->Branch("dch",&dchTimes,"dch/I");
    fTreeTraj->Branch("displX",&displx,"displX/D");
    fTreeTraj->Branch("displY",&disply,"displY/D");
    fTreeTraj->Branch("displZ",&displz,"displZ/D");
    fTreeTraj->Branch("num",&partNum,"num/I");

    std::cout << " ...Opened" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_ROOT_save::Save(ECHARM_info_save* info){
    
    UpdateInfo(info);
    
    for(unsigned int i0=0;i0<info->GetAtD().size();i0++){
        UpdateInfoTraj(info,i0);
        fTreeTraj->Fill();
    }
    
    fTree->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_ROOT_save::Analysis(){
    
    long part_num = fTree->GetEntries();
    
    
    TBranch* bEnBin = fTree->GetBranch("enBin");
    int vEnBin;
    bEnBin->SetAddress(&vEnBin);
    fTree->GetEntry(0);
    if(part_num>0){
        TBranch* bChIn = fTree->GetBranch("chin");
        int vChIn;
        bChIn->SetAddress(&vChIn);
        
        TBranch* bCh = fTree->GetBranch("ch");
        int vCh;
        bCh->SetAddress(&vCh);
        
        TBranch* bDch = fTree->GetBranch("dch");
        int vDch;
        bDch->SetAddress(&vDch);
        
        double vY[vEnBin];
        double vX[vEnBin];
        
        double vYtemp[vEnBin];
        double vXtemp[vEnBin];
        
        TBranch* bEnVec = fTree->GetBranch("enVec");
        TBranch* bEnVecX = fTree->GetBranch("enVecX");
        
        bEnVec->SetAddress(&vYtemp);
        bEnVecX->SetAddress(&vXtemp);
        
        int parttot = 0;
        
        // All particles
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] = 0.;
            vX[i0] = 0.;
        }
        
        for(int i1=0;i1<part_num;i1++){
            fTree->GetEntry(i1);
            for(int i0=0;i0<vEnBin;i0++){
                vY[i0] += vYtemp[i0];
            }
        }
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= MeV / part_num;
            vX[i0] = vXtemp[i0] / MeV;
        }
        
        TGraph* hRad = new TGraph(vEnBin,vX,vY);
        hRad->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRad->GetYaxis()->SetTitle("Spectral Intensity [1/MeV]");
        hRad->Write("hRad");
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= vXtemp[i0] / MeV;
        }
        
        TGraph* hRadE = new TGraph(vEnBin,vX,vY);
        hRadE->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRadE->GetYaxis()->SetTitle("Radiation Emission Probability");
        hRadE->Write("hRadE");
        
        // Channeled particles
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] = 0.;
            vX[i0] = 0.;
        }
        
        parttot = 0;
        for(int i1=0;i1<part_num;i1++){
            fTree->GetEntry(i1);
            if(vChIn==1 && vDch==0 && vCh==1){
                for(int i0=0;i0<vEnBin;i0++){
                    vY[i0] += vYtemp[i0];
                }
                parttot++;
            }
        }
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= MeV / parttot;
            vX[i0] = vXtemp[i0] / MeV;
        }
        
        TGraph* hRadCh = new TGraph(vEnBin,vX,vY);
        hRadCh->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRadCh->GetYaxis()->SetTitle("Spectral Intensity [1/MeV]");
        hRadCh->Write("hRadCh");
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= vXtemp[i0] / MeV;
        }
        
        TGraph* hRadChE = new TGraph(vEnBin,vX,vY);
        hRadChE->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRadChE->GetYaxis()->SetTitle("Radiation Emission Probability");
        hRadChE->Write("hRadChE");
        
        // Rechanneled particles
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] = 0.;
            vX[i0] = 0.;
        }
        
        parttot = 0;
        for(int i1=0;i1<part_num;i1++){
            fTree->GetEntry(i1);
            if(!(vChIn==1 && vDch==0 && vCh==1)){
                if((vCh-vDch)==1){
                    for(int i0=0;i0<vEnBin;i0++){
                        vY[i0] += vYtemp[i0];
                    }
                    parttot++;
                }
            }
        }
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= MeV / parttot;
            vX[i0] = vXtemp[i0] / MeV;
        }
        
        TGraph* hRadRech = new TGraph(vEnBin,vX,vY);
        hRadRech->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRadRech->GetYaxis()->SetTitle("Spectral Intensity [1/MeV]");
        hRadRech->Write("hRadRech");
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= vXtemp[i0] / MeV;
        }
        
        TGraph* hRadRechE = new TGraph(vEnBin,vX,vY);
        hRadRechE->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRadRechE->GetYaxis()->SetTitle("Radiation Emission Probability");
        hRadRechE->Write("hRadRechE");
        
        // Channeled + Rechanneled particles
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] = 0.;
            vX[i0] = 0.;
        }
        
        parttot = 0;
        for(int i1=0;i1<part_num;i1++){
            fTree->GetEntry(i1);
            if((vCh-vDch)==1){
                for(int i0=0;i0<vEnBin;i0++){
                    vY[i0] += vYtemp[i0];
                }
                parttot++;
            }
        }
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= MeV / parttot;
            vX[i0] = vXtemp[i0] / MeV;
        }
        
        TGraph* hRadChRech = new TGraph(vEnBin,vX,vY);
        hRadChRech->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRadChRech->GetYaxis()->SetTitle("Spectral Intensity [1/MeV]");
        hRadChRech->Write("hRadChRech");
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= vXtemp[i0] / MeV;
        }
        
        TGraph* hRadChRechE = new TGraph(vEnBin,vX,vY);
        hRadChRechE->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRadChRechE->GetYaxis()->SetTitle("Radiation Emission Probability");
        hRadChRechE->Write("hRadChRechE");
        
        // No Channeled or Rechanneled particles
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] = 0.;
            vX[i0] = 0.;
        }
        
        parttot = 0;
        for(int i1=0;i1<part_num;i1++){
            fTree->GetEntry(i1);
            if(vCh==0){
                for(int i0=0;i0<vEnBin;i0++){
                    vY[i0] += vYtemp[i0];
                }
                parttot++;
            }
        }
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= MeV / parttot;
            vX[i0] = vXtemp[i0] / MeV;
        }
        
        TGraph* hRadNoCh = new TGraph(vEnBin,vX,vY);
        hRadNoCh->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRadNoCh->GetYaxis()->SetTitle("Spectral Intensity [1/MeV]");
        hRadNoCh->Write("hRadNoCh");
        
        for(int i0=0;i0<vEnBin;i0++){
            vY[i0] *= vXtemp[i0] / MeV;
        }
        
        TGraph* hRadNoChE = new TGraph(vEnBin,vX,vY);
        hRadNoChE->GetXaxis()->SetTitle("Photon Energy [MeV]");
        hRadNoChE->GetYaxis()->SetTitle("Radiation Emission Probability");
        hRadNoChE->Write("hRadNoChE");
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_ROOT_save::Close(){
    std::cout << "Closing ROOT File... " << fFilename;
    vRootFile->Write(); // write ROOT file
    vRootFile->Close(); // close ROOT file
    std::cout << " ...Closed" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
