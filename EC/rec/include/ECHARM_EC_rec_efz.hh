//
//  ECHARM_EC_rec_efz.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_efz_h
#define _ECHARM_EC_rec_efz_h

#include "ECHARM_EC_rec.hh"

class ECHARM_EC_rec_efz: public ECHARM_EC_rec
{
public:
    ECHARM_EC_rec_efz(ECHARM_crystal*,int,int,int);
    ~ECHARM_EC_rec_efz();
    
    std::vector<double> ComputeRecFF(int[3],double[3]);
    double GetFactorRe(double*);
    inline double GetFactorIm(double* index) {return -GetFactorRe(index);};
    double Get(double,double,double);
    
    virtual bool GetIndexesSF(int*,int,int,int);
    virtual bool GetIndexesEC(double*,int*,int,int,int);
};

#endif
