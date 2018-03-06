//
//  ECHARM_STtestAxial.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_STtestAxial
//

#ifndef _ECHARM_STtestAxial_h
#define _ECHARM_STtestAxial_h
#include "ECHARM_strip.hh"

class ECHARM_STtestAxial : public ECHARM_strip {
public:
    ECHARM_STtestAxial(double,double,double,int,int,int);
    virtual ~ECHARM_STtestAxial();
};
#endif
