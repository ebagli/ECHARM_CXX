//
//  ECHARM_EC_rec_eld.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_eld_h
#define _ECHARM_EC_rec_eld_h

#include "ECHARM_EC_rec.hh"

class ECHARM_EC_rec_eld: public ECHARM_EC_rec
{
public:
    ECHARM_EC_rec_eld(ECHARM_crystal*,int,int,int);
    ~ECHARM_EC_rec_eld();
    
    std::vector<double> ComputeRecFF(int[3],double[3]);
    inline double GetFactorRe(double*) {return 1.;};
    inline double GetFactorIm(double*) {return 1.;};
    double Get(double,double,double);

    virtual bool GetIndexesSF(int*,int,int,int);
    virtual bool GetIndexesEC(double*,int*,int,int,int);
};

#endif
