//
//  ECHARM_EC_rec_efy_pl.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_efy_pl_h
#define _ECHARM_EC_rec_efy_pl_h

#include "ECHARM_EC_rec_efy.hh"

class ECHARM_EC_rec_efy_pl: public ECHARM_EC_rec_efy
{
public:
    ECHARM_EC_rec_efy_pl(ECHARM_crystal*,int);
    ~ECHARM_EC_rec_efy_pl();
    
    bool GetIndexesSF(int*,int,int,int);
    inline bool GetIndexesEC(double*,int*,int,int,int) {return false;};
};

#endif
