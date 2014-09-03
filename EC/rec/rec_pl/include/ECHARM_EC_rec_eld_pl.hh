//
//  ECHARM_EC_rec_eld_pl.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_eld_pl_h
#define _ECHARM_EC_rec_eld_pl_h

#include "ECHARM_EC_rec_eld.hh"

class ECHARM_EC_rec_eld_pl: public ECHARM_EC_rec_eld
{
public:
    ECHARM_EC_rec_eld_pl(ECHARM_crystal*,int);
    ~ECHARM_EC_rec_eld_pl();

    bool GetIndexesSF(int*,int,int,int);
    bool GetIndexesEC(double*,int*,int,int,int);
};

#endif
