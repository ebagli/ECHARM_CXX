//
//  ECHARM_STtest.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_STtest
//

#ifndef _ECHARM_STtest_h
#define _ECHARM_STtest_h
#include "ECHARM_strip.hh"

class ECHARM_STtest : public ECHARM_strip {
public:
    ECHARM_STtest(double,double,double,int,int,int);
    virtual ~ECHARM_STtest();
};
#endif
