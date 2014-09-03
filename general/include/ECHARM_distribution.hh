//
//  ECHARM_distribution.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_distribution_h
#define _ECHARM_distribution_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include "ECHARM_3vec.hh"

class ECHARM_distribution
{
public:
    
    ECHARM_distribution();
    virtual ~ECHARM_distribution();
    
    void Print();
    
    virtual double GetProbability(double);
    virtual double GenerateNumber();
    
protected:
    std::vector<double> fPar;
    std::vector<std::string> fParNames;

#include "ECHARM_distribution.hxx"
    
};

#endif
