//
//  ECHARM_atom_lindhard.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   This class has to be filled with atomic parameters only.
///   Thermal vibration amplitude is automatically evaluated.
///   No input from standard databases are implemented right now.
///

#ifndef _ECHARM_atom_lindhard_h
#define _ECHARM_atom_lindhard_h

#include "ECHARM_atom.hh"

class ECHARM_atom_lindhard: public ECHARM_atom
{
public:
    ECHARM_atom_lindhard(std::string AtomName,
                        double Z,
                        double A,
                        double DebyeTemperature,
                        double AverageIonizationConstant);
    virtual ~ECHARM_atom_lindhard();
    
    double ComputeRecFF(double RecVec2);
    double ComputeFF(double Vec2);
    double ComputeFFDerivate(double Vec);
};
#endif
