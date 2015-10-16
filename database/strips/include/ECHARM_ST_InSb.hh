//
//  ECHARM_ST_InSb.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_ST_InSb
//

#ifndef _ECHARM_ST_InSb_h
#define _ECHARM_ST_InSb_h
#include "ECHARM_strip.hh"

class ECHARM_ST_InSb : public ECHARM_strip {
public:
    ECHARM_ST_InSb(double,bool,int,int,int);
    virtual ~ECHARM_ST_InSb();
};
#endif
