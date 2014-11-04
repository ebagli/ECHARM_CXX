//
//  ECHARM_beam_ee_discrimination.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//  Class ECHARM_beam_ee_discrimination

#ifndef _ECHARM_beam_ee_discrimination_h
#define _ECHARM_beam_ee_discrimination_h

#include "ECHARM_beam.hh"

class ECHARM_beam_ee_discrimination : public ECHARM_beam
{
public:
    ECHARM_beam_ee_discrimination(double,double,double,double,double,double );
    virtual ~ECHARM_beam_ee_discrimination();
};

#endif
