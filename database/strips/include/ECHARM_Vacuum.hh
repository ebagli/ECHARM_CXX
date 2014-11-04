//
//  ECHARM_Vacuum.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_Vacuum
//

#ifndef _ECHARM_Vacuum_h
#define _ECHARM_Vacuum_h
#include "ECHARM_strip.hh"

class ECHARM_Vacuum : public ECHARM_strip {
public:
    ECHARM_Vacuum(double,double,double,double,double,double,double);
    virtual ~ECHARM_Vacuum();
};
#endif
