//
//  ECHARM_process_bethe_bloch.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_bethe_bloch_h
#define _ECHARM_process_bethe_bloch_h

#include "ECHARM_process.hh"

class ECHARM_process_bethe_bloch: public ECHARM_process
{
public:
    ECHARM_process_bethe_bloch();
    virtual ~ECHARM_process_bethe_bloch();
    
    void DoOnParticle(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);

    double ComputeElectronMaximumKineticTransfer(ECHARM_strip*,ECHARM_particle*);
    double ComputeLogarithmicTerm(ECHARM_strip*,ECHARM_particle*);
    double ComputeDensityEffectTerm(ECHARM_strip*,ECHARM_particle*);
    double ComputeMeanEnergyLoss(ECHARM_strip*,ECHARM_particle*);

protected:
    double fStdDev;
    ECHARM_distribution* fDistr;
};
#endif