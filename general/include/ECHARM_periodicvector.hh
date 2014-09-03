//
//  ECHARM_periodicvector.hh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   Class ECHARM_periodicvector is a class derived from ECHARM_atom because it has all its characteristics averaged over the all the atom kind of the crystal.
///   It is really important to check that the ECHARM_periodicvector is ok before procede with any calculation method of this class.
///   The crystal is formed by a single ECHARM_cell, a single ECHARM_miller class, and many ECHARM_atoms and ECHARM_lattice classes.
///   Each ECHARM_atom has a linked ECHARM_lattice which describe the position of the atom in the cell and the numer of the that atom kind in a unit cell.
///   ECHARM_cell descirbes the fundamental cell properties and affect the ECHARM_lattice class because ECHARM_lattice point coordinates are expressed in terms of the ECHARM_cell base three vectors.
///   ECHARM_miller describes the planar and axial Miller vIndexes on which the calculation are going to be made.
///   Planar electric characteristics can be evaluated for any kind of crystal structures.
///   At the present time any axial characteristic can be evaluated only for cubic structures. For general orthorhombic structures only main axes can be evaluated.
///   has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_periodicvector class will average electric characteristic.
///   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.
///

#ifdef ROOT_
#include "TH1.h"
#include "TH2.h"
#endif

#ifndef _ECHARM_periodicvector_h
#define _ECHARM_periodicvector_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "ECHARM_intrp.hh"
#include "ECHARM_3vec.hh"

class ECHARM_periodicvector
{
public:
    ECHARM_periodicvector(int*,double*);
    ECHARM_periodicvector(int*,ECHARM_3vec*);
    virtual ~ECHARM_periodicvector();

    void Set(std::vector<double>);
    
    std::string PrintNameOnString(std::string);
    
    void ReadFromFile(std::string);
    void PrintToFile(std::string,std::string);

#ifdef ROOT_
    void PrintToTH(std::string,std::string = "");
    void PrintToTH1(std::string,std::string = "");
    void PrintToTH2(std::string,std::string = "");
#endif

    double GetVal1d(double);
    double GetVal2d(double,double);
    double GetVal(double,double,double);

    int ComputeIndex(int i,int j,int k);

    std::vector<double> GetNorm();
   
private:
    std::vector<double> fVec;
    std::string fName;
    
    int fNumSteps[3];
    double fPeriod[3];
    double fRecPeriod[3];
    
    double fMax;
    double fMin;
    
    ECHARM_intrp *fIntrp;

#include "ECHARM_periodicvector.hxx"
};

#endif
