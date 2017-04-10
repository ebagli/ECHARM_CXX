//
//  ECHARM_beam_general.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//  Class ECHARM_beam_general

#ifndef _ECHARM_beam_general_h
#define _ECHARM_beam_general_h

#include "ECHARM_beam.hh"

class ECHARM_beam_general : public ECHARM_beam
{
public:
    ECHARM_beam_general(ECHARM_particle*,double,double,double,double,double);
    virtual ~ECHARM_beam_general();
};

#endif
