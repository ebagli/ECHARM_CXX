//
//  ECHARM_miller.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_miller has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_crystal class will average electric characteristic.
//   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.

#ifndef _ECHARM_miller_h
#define _ECHARM_miller_h

class ECHARM_miller
{
public:
    ECHARM_miller();
    ECHARM_miller(int MillerX[3],int MillerY[3],int MillerZ[3]);
    ECHARM_miller(int MillerX[3],int MillerZ[3]);
    ECHARM_miller(int MillerZ[3]);
    virtual ~ECHARM_miller();
    
    std::string GetText(int vMiller[3]);

    void Print();

    bool IsMainAxis();

    double GetModuleSquared(int vIndex);
public:
    virtual void ComputeMiller();
    virtual bool CheckOrthogonalityToAxis(int MillerOrthogonal[3]);
    virtual bool CheckOrthogonality();
    virtual void ReverseMillerOrder(int MillerReversed[3]);

protected:
    int fMiller[3][3];
  
#include "ECHARM_miller.hxx"
};

#endif
