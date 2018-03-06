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

ECHARM_process_bethe_bloch_tables::ECHARM_process_bethe_bloch_tables():
ECHARM_process("bethe_bloch_tables"){
    fDistr = new ECHARM_distribution_gauss(0.,0.);
    ECHARM_dir = std::getenv("ECHARMSYS");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_bethe_bloch_tables::~ECHARM_process_bethe_bloch_tables(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_bethe_bloch_tables::LoadData(ECHARM_strip* strip){
    
    std::ifstream infile;
    infile.open(ECHARM_dir + "/process/bethe_bloch/data/pstar_Si.txt");
    std::string line;
    
    for(int i=0;i<8;i++){
        getline(infile,line);
    }
    
    float a, b, c;
    std::vector<float> dE;
    std::vector<float> dEdX_eld;
    std::vector<float> dEdX_nud;

    float density = strip->GetCrystal()->GetMassDensity() / amu * 1.660539040E-24 / 1.E6;
    while (infile >> a >> b >> c){
        dE.push_back(a*MeV);
        dEdX_eld.push_back(b*MeV*density/1.E-2);
        dEdX_nud.push_back(c*MeV*density/1.E-2);
    }
    
    
    fValueMap_dE[int(strip->GetCrystal()->GetZ())] = dE;
    fValueMap_dEdX_eld[int(strip->GetCrystal()->GetZ())] = dEdX_eld;
    fValueMap_dEdX_nud[int(strip->GetCrystal()->GetZ())] = dEdX_nud;
    
    infile.close();
    std::cout << "Value Loaded from file: " << ECHARM_dir + "/process/bethe_bloch/data/pstar_Si.txt" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_bethe_bloch_tables::DoOnParticle(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){

    fEnergyLossEld = 0;

    int Z = int(strip->GetCrystal()->GetZ());
    float energy = part->GetMom()->GetModule();
    int index = -1;
    
    
    if(fValueMap_dEdX_eld.count(Z)){
        
        auto it = std::find(fValueMap_dE[Z].begin(),
                                     fValueMap_dE[Z].end(),
                                     energy);
        if (it == fValueMap_dE[Z].end()){
            auto upper = std::upper_bound(fValueMap_dE[Z].begin(),
                                          fValueMap_dE[Z].end(),
                                          energy);
            index = upper - fValueMap_dE[Z].begin();
            float y0 = fValueMap_dEdX_nud[Z][index-1];
            float y1 = fValueMap_dEdX_nud[Z][index];
            float x0 = fValueMap_dE[Z][index-1];
            float x1 = fValueMap_dE[Z][index];
            fEnergyLossNud = y0 + (energy - x0)/(x1 - x0)*(y1-y0);

            y0 = fValueMap_dEdX_eld[Z][index-1];
            y1 = fValueMap_dEdX_eld[Z][index];
            fEnergyLossEld = y0 + (energy - x0)/(x1 - x0)*(y1-y0);
        }
        else{
            index = (it - fValueMap_dE[Z].begin());
            fEnergyLossNud = fValueMap_dEdX_eld[Z][index];
            fEnergyLossEld = fValueMap_dEdX_nud[Z][index];
        }
    }
    else{
        std::cout << "Value Not Found" << std::endl;
        LoadData(strip);
    }
    
    float loss = (fEnergyLossEld * ComputeAvgElD(strip,part)) + (fEnergyLossNud * ComputeAvgAtD(strip,part));
    loss *= part->GetStepLength();
    
    double vMomVar = energy - loss;
    if(vMomVar < 0.) vMomVar = 0.;
    part->GetMom()->ScaleModule(vMomVar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
