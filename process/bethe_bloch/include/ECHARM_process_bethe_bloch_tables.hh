//
//  ECHARM_process_bethe_bloch_tables.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_bethe_bloch_tables_h
#define _ECHARM_process_bethe_bloch_tables_h

#include "ECHARM_process.hh"
#include <map>
#include <tuple>

class ECHARM_process_bethe_bloch_tables: public ECHARM_process
{
public:
    ECHARM_process_bethe_bloch_tables(std::string);
    virtual ~ECHARM_process_bethe_bloch_tables();
    
    void DoOnParticle(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    void LoadData(ECHARM_strip*);
    
protected:
    std::vector<float> fValueMap_dEdX_eld;
    std::vector<float> fValueMap_dE;
    std::vector<float> fValueMap_dEdX_nud;
    
    double fEnergyLossNud;
    double fEnergyLossEld;
    
    ECHARM_distribution* fDistr;

    double fStdDev;
    
    std::string ECHARM_dir;
    std::string fFilename;
};
#endif
