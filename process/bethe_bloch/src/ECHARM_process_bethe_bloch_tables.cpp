//
//  ECHARM_process_bethe_bloch_tables.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef _ECHARM_process_bethe_bloch_tables_h

#include "ECHARM_process_bethe_bloch_tables.hh"
#include "ECHARM_distribution_gauss.hh"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

ECHARM_process_bethe_bloch_tables::ECHARM_process_bethe_bloch_tables(std::string filename):
ECHARM_process("bethe_bloch_tables"),
fFilename(filename){
    fDistr = new ECHARM_distribution_gauss(0.,0.);
    ECHARM_dir = std::getenv("ECHARMSYS");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_bethe_bloch_tables::~ECHARM_process_bethe_bloch_tables(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_bethe_bloch_tables::LoadData(ECHARM_strip* strip){
    
    std::ifstream infile;
    infile.open(ECHARM_dir + "/process/bethe_bloch/data/pstar_" + fFilename + ".txt");
    std::string line;
    
    for(int i=0;i<8;i++){
        getline(infile,line);
    }
    
    float a, b, c;

    float density = strip->GetCrystal()->GetMassDensity() / amu * 1.660539040E-24 / 1.E6;
    std::cout << density << std::endl;
    while (infile >> a >> b >> c){
        fValueMap_dE.push_back(a*MeV);
        fValueMap_dEdX_eld.push_back(b*MeV*density/1.E-2);
        fValueMap_dEdX_nud.push_back(c*MeV*density/1.E-2);
        //std::cout <<b << " " << MeV << " " << density/1.E-2 << std::endl;
    }
    
    infile.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_bethe_bloch_tables::DoOnParticle(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){

    fEnergyLossEld = 0;

    float energy = part->GetMom()->GetModule();
    int index = -1;
    
    if(fValueMap_dEdX_eld.empty()==true){
        std::cout << "Value Not Found" << std::endl;
        LoadData(strip);
    }
    
    if(fValueMap_dEdX_eld.empty()!=true){
        
        auto it = std::find(fValueMap_dE.begin(),
                            fValueMap_dE.end(),
                            energy);
        if (it == fValueMap_dE.end()){
            auto upper = std::upper_bound(fValueMap_dE.begin(),
                                          fValueMap_dE.end(),
                                          energy);
            index = upper - fValueMap_dE.begin();
            float y0 = fValueMap_dEdX_nud[index-1];
            float y1 = fValueMap_dEdX_nud[index];
            float x0 = fValueMap_dE[index-1];
            float x1 = fValueMap_dE[index];
            fEnergyLossNud = y0 + (energy - x0)/(x1 - x0)*(y1-y0);

            y0 = fValueMap_dEdX_eld[index-1];
            y1 = fValueMap_dEdX_eld[index];
            fEnergyLossEld = y0 + (energy - x0)/(x1 - x0)*(y1-y0);
        }
        else{
            index = (it - fValueMap_dE.begin());
            fEnergyLossNud = fValueMap_dEdX_nud[index];
            fEnergyLossEld = fValueMap_dEdX_eld[index];
        }
    }
    else{
        return;
    }
    
    float loss = (fEnergyLossEld * ComputeAvgElD(strip,part)) + (fEnergyLossNud * ComputeAvgAtD(strip,part));
    loss *= part->GetStepLength();
    
    double vMomVar = energy - loss;
    if(vMomVar < 0.) vMomVar = 0.;
    
    part->GetMom()->ScaleModule(vMomVar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
