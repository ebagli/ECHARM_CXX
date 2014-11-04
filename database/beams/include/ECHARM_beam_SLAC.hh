//
//  ECHARM_beam_SLAC.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//  Class ECHARM_beam_SLAC

#ifndef _ECHARM_beam_SLAC_h
#define _ECHARM_beam_SLAC_h

#include "ECHARM_beam.hh"

class ECHARM_beam_SLAC : public ECHARM_beam
{
public:
    ECHARM_beam_SLAC(double,double,double);
    virtual ~ECHARM_beam_SLAC();
};

#endif
