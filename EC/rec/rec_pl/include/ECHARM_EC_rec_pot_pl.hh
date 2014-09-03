//
//  ECHARM_EC_rec_pot_pl.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_pot_pl_h
#define _ECHARM_EC_rec_pot_pl_h

#include "ECHARM_EC_rec_pot.hh"

class ECHARM_EC_rec_pot_pl: public ECHARM_EC_rec_pot
{
public:
    ECHARM_EC_rec_pot_pl(ECHARM_crystal*,int);
    ~ECHARM_EC_rec_pot_pl();

    bool GetIndexesSF(int*,int,int,int);
    bool GetIndexesEC(double*,int*,int,int,int);
};

#endif
