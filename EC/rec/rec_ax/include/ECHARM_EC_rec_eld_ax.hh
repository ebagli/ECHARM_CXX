//
//  ECHARM_EC_rec_eld_ax.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_eld_ax_h
#define _ECHARM_EC_rec_eld_ax_h

#include "ECHARM_EC_rec_eld.hh"

class ECHARM_EC_rec_eld_ax: public ECHARM_EC_rec_eld
{
public:
    ECHARM_EC_rec_eld_ax(ECHARM_crystal*,int,int);
    ~ECHARM_EC_rec_eld_ax();

    bool GetIndexesSF(int*,int,int,int);
    bool GetIndexesEC(double*,int*,int,int,int);
};

#endif
