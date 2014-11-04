//
//  ECHARM_atom.h
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

#ifndef _ECHARM_atom_h
#define _ECHARM_atom_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <iomanip>

#include "ECHARM_constants.hh"

class ECHARM_atom
{
public:
    
    //
    // Constructor to Build an element directly; no reference to isotopes
    //
    // Average ionization energies available at http://www.srim.org/SRIM/SRIMPICS/IONIZ.htm

    ECHARM_atom(std::string AtomName,
                double Z,
                double A,
                double DebyeTemperature,
                double AverageIonizationConstant); //!< Create an atom from its properties.
    
    ECHARM_atom(std::string File_Atom);    //!< Read an atom from a file.
    virtual ~ECHARM_atom();
    
    void Print(); //!< Print properties of the atom.

    double ComputeThomasFermiRadius();
    double ComputeThermalVibration();//!< Compute Thermal Vibration Constant.
 
    virtual double ComputeRecFF(double RecVec2)  {return -1.;}; //!< Evaluate the reciprocal Form Factor value giving a reciprocal vector squared. The atom is centered at (0.,0.,0.).
    
    virtual double ComputeFF(double Vec2)  {return -1.;};//!< Evaluate the direct Form Factor value giving a direct vector squared. The atom is centered at (0.,0.,0.).
 
    virtual double ComputeFFDerivate(double Vec) {return -1.;};//!<
    

    
private:
    std::string  fAtomName;        
    double fZ;            
    double fA;             
    double fDebyeTemperature;          
    double fAverageIonizationConstant;

private:
    double fTemperature;
    double fThermalVibrationConstant;
    double fThomasFermiRadius;
    
#include "ECHARM_atom.hxx"
};

#endif
