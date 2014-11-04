//
//  ECHARM_beam_H4_electron.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//  Class ECHARM_beam_H4_electron

#ifndef _ECHARM_beam_H4_electron_h
#define _ECHARM_beam_H4_electron_h

#include "ECHARM_beam.hh"

class ECHARM_beam_H4_electron : public ECHARM_beam
{
public:
    ECHARM_beam_H4_electron(double,double,double);
    virtual ~ECHARM_beam_H4_electron();
};

#endif
