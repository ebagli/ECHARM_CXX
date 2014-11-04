//
//  ECHARM_EC_const.hh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_const_h
#define _ECHARM_EC_const_h

#include "ECHARM_EC.hh"

class ECHARM_EC_const: public ECHARM_EC
{
public:
    ECHARM_EC_const(std::string,ECHARM_crystal*,double);
    ~ECHARM_EC_const();
    
public:
    double Get(double,double,double) {return fConst;};
    
    void ComputeMax() {fMax = fConst;};
    void ComputeMin() {fMin = fConst;};
private:
    double fConst;
};

#endif
