//
//  ECHARM_atom_xray.h
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

#ifndef _ECHARM_atom_xray_h
#define _ECHARM_atom_xray_h

#include "ECHARM_atom.hh"

class ECHARM_atom_xray: public ECHARM_atom
{
public:
    ECHARM_atom_xray(std::string AtomName,
                     double Z,
                     double A,
                     double DebyeTemperature,
                     double AverageIonizationConstant,
                     double ExperimentalFormFactorParameters[12]);
    
    ECHARM_atom_xray(std::string AtomName,
                     double Z,
                     double A,
                     double DebyeTemperature,
                     double AverageIonizationConstant);
    
    ECHARM_atom_xray(std::string File_Atom);    //!< Read an atom from a file.
    virtual ~ECHARM_atom_xray();
        
    double ComputeRecFF(double RecVec2);
    double ComputeFF(double Vec2);
    double ComputeFFDerivate(double Vec);
    
private:
    double fExperimentalFormFactorParameters[12];
};

#endif
