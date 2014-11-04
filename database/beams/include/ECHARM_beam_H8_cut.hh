//
//  ECHARM_beam_H8_cut.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//  Class ECHARM_beam_H8_cut

#ifndef _ECHARM_beam_H8_cut_h
#define _ECHARM_beam_H8_cut_h

#include "ECHARM_beam.hh"

class ECHARM_beam_H8_cut : public ECHARM_beam
{
public:
    ECHARM_beam_H8_cut(double,double,double);
    virtual ~ECHARM_beam_H8_cut();
};

#endif
