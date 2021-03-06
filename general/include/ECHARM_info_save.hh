//
//  ECHARM_info_save.hh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   Class ECHARM_info_save is a class derived from ECHARM_atom because it has all its characteristics averaged over the all the atom kind of the crystal.
///   It is really important to check that the ECHARM_info_save is ok before procede with any calculation method of this class.
///   The crystal is formed by a single ECHARM_cell, a single ECHARM_miller class, and many ECHARM_atoms and ECHARM_lattice classes.
///   Each ECHARM_atom has a linked ECHARM_lattice which describe the position of the atom in the cell and the numer of the that atom kind in a unit cell.
///   ECHARM_cell descirbes the fundamental cell properties and affect the ECHARM_lattice class because ECHARM_lattice point coordinates are expressed in terms of the ECHARM_cell base three vectors.
///   ECHARM_miller describes the planar and axial Miller vIndexes on which the calculation are going to be made.
///   Planar electric characteristics can be evaluated for any kind of crystal structures.
///   At the present time any axial characteristic can be evaluated only for cubic structures. For general orthorhombic structures only main axes can be evaluated.
///   has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_info_save class will average electric characteristic.
///   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.
///

#ifndef _ECHARM_info_save_h
#define _ECHARM_info_save_h

#include <vector>
#include "ECHARM_constants.hh"
#include "ECHARM_3vec.hh"
#include "ECHARM_particle.hh"

class ECHARM_info_save
{
public:
    ECHARM_info_save();
    virtual ~ECHARM_info_save();
public:
    void SetRadEmEn(int,double,double);
    void AddRadEmEn(double);
    
    void Reset();
    void SavePartStruct(ECHARM_particle*,ECHARM_Particle_Save&);
    void Print();
    
    void SavePartIn(ECHARM_particle* part);
    void SavePartOut(ECHARM_particle* part);
    void SavePart(ECHARM_particle*,double,double,double,double,double);

private:
    int fPartNum;
    
    std::vector<double> fRadEmEn;
    std::vector<double> fRadEmProb;

    std::vector<double> fEmittedPhEn;
    
    ECHARM_Particle_Save fPartIn;
    ECHARM_Particle_Save fPartOut;
    ECHARM_Particle_Save fPart;
    std::vector<ECHARM_Particle_Save> fPartVec;
    
    double fCharge;
    double fMass;
    
    std::vector<double> fPot;
    std::vector<double> fEFX;
    std::vector<double> fKin;

    std::vector<double> fDisplX;
    std::vector<double> fDisplY;
    std::vector<double> fDisplZ;
    ECHARM_3vec* fDispl;
    ECHARM_3vec* fBR;
    ECHARM_3vec* fBeamSize;

    std::vector<double> fAtD;
    double fAvgAtD;

    std::vector<double> fElD;
    double fAvgElD;
    
    std::vector<int> fChInitialTot;
    int fChInitial;
    std::vector<int> fChTimesTot;
    int fChTimes;
    std::vector<int> fDechTimesTot;
    int fDechTimes;
    
#include "ECHARM_info_save.hxx"
};

#endif
