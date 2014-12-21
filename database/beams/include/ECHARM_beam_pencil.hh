//
//  ECHARM_beam_pencil.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//  Class ECHARM_beam_pencil

#ifndef _ECHARM_beam_pencil_h
#define _ECHARM_beam_pencil_h

#include "ECHARM_beam.hh"

class ECHARM_beam_pencil : public ECHARM_beam
{
public:
    ECHARM_beam_pencil(double,double,double);
    virtual ~ECHARM_beam_pencil();
};

#endif
