//
//  ECHARM_distribution.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_distribution_const_h
#define _ECHARM_distribution_const_h
#include "ECHARM_distribution.hh"

class ECHARM_distribution_const: public ECHARM_distribution
{
public:
    
    ECHARM_distribution_const(double);
    virtual ~ECHARM_distribution_const();
        
    double GetProbability(double);
    double GenerateNumber();
    
private:    
};

#endif
