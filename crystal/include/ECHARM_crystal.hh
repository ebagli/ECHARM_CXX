//
//  ECHARM_crystal.hh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   Class ECHARM_crystal is a class derived from ECHARM_atom because it has all its characteristics averaged over the all the atom kind of the crystal.
///   It is really important to check that the ECHARM_crystal is ok before procede with any calculation method of this class.
///   The crystal is formed by a single ECHARM_cell, a single ECHARM_miller class, and many ECHARM_atoms and ECHARM_lattice classes.
///   Each ECHARM_atom has a linked ECHARM_lattice which describe the position of the atom in the cell and the numer of the that atom kind in a unit cell.
///   ECHARM_cell descirbes the fundamental cell properties and affect the ECHARM_lattice class because ECHARM_lattice point coordinates are expressed in terms of the ECHARM_cell base three vectors.
///   ECHARM_miller describes the planar and axial Miller vIndexes on which the calculation are going to be made.
///   Planar electric characteristics can be evaluated for any kind of crystal structures.
///   At the present time any axial characteristic can be evaluated only for cubic structures. For general orthorhombic structures only main axes can be evaluated.
///   has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_crystal class will average electric characteristic.
///   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.
///

#ifndef _ECHARM_crystal_h
#define _ECHARM_crystal_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <cfloat>

#include "ECHARM_constants.hh"
#include "ECHARM_atom.hh"
#include "ECHARM_lattice.hh"
#include "ECHARM_miller.hh"
#include "ECHARM_cell.hh"

class ECHARM_crystal: public ECHARM_atom
{
public:
    ECHARM_crystal();
    ECHARM_crystal(ECHARM_cell*, ECHARM_miller*, ECHARM_atom*, ECHARM_lattice*);
    virtual ~ECHARM_crystal();
    
    bool CheckCrystal(); //!< Check if all the element of the crystal class has been initialized correctly.
    
    void AddBase(ECHARM_atom*,ECHARM_lattice*,float percentage = 1.);
    void PrintBase(unsigned int);
    
    void PrintTot();
    std::string PrintNameOnString(std::string);
    
    void ComputeParameters(); //!< Compute the crystal average parameters starting from the atom properties of the bases.
    void ComputeRadLength();
    
    std::vector<double> ComputeSF(int[3]);
    std::vector<double> ComputeRecFFAtDEld(int[3]);
    std::vector<double> ComputeRecFFAtD(int[3]);
    std::vector<double> ComputeRecFFElD(int[3]);//!< Find an array with all the coefficient of the Fourier transform of the selected averaged electric characteristic. Even = Re; Odd = Im. To select electric characteristic one can choose: "Pot = Potential Energy [eV] ; EFi = Electrical Field [eV/m] on Planar Direction or on first Axial direction; "AlD" = atomic density [1/m^3];  "ElD" = electron density [1/m^3]
    
protected:
    ECHARM_cell *fCell;
    ECHARM_miller *fMiller;
    std::vector<ECHARM_atom*> fAtom;
    std::vector<ECHARM_lattice*> fLattice;
    std::vector<float> fPercentage;
    double fRadLength;

    double fNumCoord;
    
    double fPeriod[3];
    double fRecPeriod[3];
    
#include "ECHARM_crystal.hxx"
};

#endif
