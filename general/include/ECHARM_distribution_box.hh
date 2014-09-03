//
//  ECHARM_distribution.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_distribution_box_h
#define _ECHARM_distribution_box_h
#include "ECHARM_distribution.hh"

class ECHARM_distribution_box: public ECHARM_distribution
{
public:
    
    ECHARM_distribution_box(double,double);
    virtual ~ECHARM_distribution_box();
        
    double GetProbability(double);
    double GenerateNumber();
    
private:    
};

#endif
