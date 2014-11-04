//
//  ECHARM_EC_direct.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_direct_h
#define _ECHARM_EC_direct_h

#include "ECHARM_EC.hh"
#include "ECHARM_constants.hh"

class ECHARM_EC_direct: public ECHARM_EC
{
public:
    ECHARM_EC_direct(std::string,ECHARM_crystal*,int);
    ~ECHARM_EC_direct();
    
    double Get(double,double,double);
    double Get1d(double);
    double Get2d(double,double);
    virtual double GetFunc(double,double,double);
    
protected:
    int fCellNumb;
    int fStepNumbPerCell;
    double fLimit;
#include "ECHARM_EC_direct.hxx"
};
#endif
