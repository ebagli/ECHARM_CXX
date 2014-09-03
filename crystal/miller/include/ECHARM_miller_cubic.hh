//
//  ECHARM_miller_cubic.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_miller_cubic has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_crystal class will average electric characteristic.
//   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.

#ifndef _ECHARM_miller_cubic_h
#define _ECHARM_miller_cubic_h

#include "ECHARM_miller.hh"

class ECHARM_miller_cubic : public ECHARM_miller
{
public:
    ECHARM_miller_cubic(int MillerX[3],int MillerY[3],int MillerZ[3]);
    ECHARM_miller_cubic(int MillerX[3],int MillerZ[3]);
    ECHARM_miller_cubic(int MillerZ[3]);
    virtual ~ECHARM_miller_cubic();

public:
    void ReverseMillerOrder(int MillerReversed[3]);

private:
    void ReverseMillerOrderForCubicAxialCalculations(int MillerReversed[3]);

protected:
    virtual void ComputeMiller();
    virtual bool CheckOrthogonalityToAxis(int MillerOrthogonal[3]);
    virtual bool CheckOrthogonality();
};

#endif
