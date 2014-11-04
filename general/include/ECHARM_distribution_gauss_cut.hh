//
//  ECHARM_distribution.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_distribution_gauss_h
#define _ECHARM_distribution_gauss_h
#include "ECHARM_distribution.hh"

class ECHARM_distribution_gauss: public ECHARM_distribution
{
public:
    
    ECHARM_distribution_gauss(double,double);
    virtual ~ECHARM_distribution_gauss();
        
    double GetProbability(double);
    double GenerateNumber();
    
private:
    double fSecondNumber;
    bool fUseSecond;    
};

#endif
