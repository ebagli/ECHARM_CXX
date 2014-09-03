//
//  ECHARM_EC_rec_efy.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_efy_h
#define _ECHARM_EC_rec_efy_h

#include "ECHARM_EC_rec.hh"

class ECHARM_EC_rec_efy: public ECHARM_EC_rec
{
public:
    ECHARM_EC_rec_efy(ECHARM_crystal*,int,int,int);
    ~ECHARM_EC_rec_efy();
    
    std::vector<double> ComputeRecFF(int[3]);
    double GetFactorRe(double*);
    inline double GetFactorIm(double* index) {return GetFactorRe(index);};
    double Get(double,double,double);
    
    virtual bool GetIndexesSF(int*,int,int,int) = 0;
    virtual bool GetIndexesEC(double*,int*,int,int,int) = 0;
};

#endif
