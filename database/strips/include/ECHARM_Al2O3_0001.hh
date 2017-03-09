//
//  ECHARM_Al2O3_0001.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_Al2O3_0001
//

#ifndef _ECHARM_Al2O3_0001_h
#define _ECHARM_Al2O3_0001_h
#include "ECHARM_strip.hh"

class ECHARM_Al2O3_0001 : public ECHARM_strip {
public:
    ECHARM_Al2O3_0001(double length = 1000.);
    virtual ~ECHARM_Al2O3_0001();
};
#endif
