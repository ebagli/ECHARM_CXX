//
//  ECHARM_EC_rec_efz_ax.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_efz_ax_h
#define _ECHARM_EC_rec_efz_ax_h

#include "ECHARM_EC_rec_efz.hh"

class ECHARM_EC_rec_efz_ax: public ECHARM_EC_rec_efz
{
public:
    ECHARM_EC_rec_efz_ax(ECHARM_crystal*,int,int);
    ~ECHARM_EC_rec_efz_ax();
    
    bool GetIndexesSF(int*,int,int,int);
    inline bool GetIndexesEC(double*,int*,int,int,int) {return false;};
};

#endif
