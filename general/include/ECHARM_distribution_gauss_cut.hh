//
//  ECHARM_distribution.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_distribution_gauss_cut_h
#define _ECHARM_distribution_gauss_cut_h
#include "ECHARM_distribution.hh"

class ECHARM_distribution_gauss_cut: public ECHARM_distribution
{
public:
    
    ECHARM_distribution_gauss_cut(double,double,double);
    virtual ~ECHARM_distribution_gauss_cut();
        
    double GetProbability(double);
    double GenerateNumber();
    
private:
    double fSecondNumber;
    bool fUseSecond;    
};

#endif
