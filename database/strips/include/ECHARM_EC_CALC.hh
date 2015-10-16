//
//  ECHARM_EC_CALC.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_EC_CALC
//

#ifndef _ECHARM_EC_CALC_h
#define _ECHARM_EC_CALC_h
#include "ECHARM_strip.hh"

class ECHARM_EC_CALC : public ECHARM_strip {
public:
    ECHARM_EC_CALC(ECHARM_crystal*,bool,int,int,int,bool);
    virtual ~ECHARM_EC_CALC();
};
#endif
