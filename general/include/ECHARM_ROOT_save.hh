//
//  ECHARM_ROOT_save.hh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   Class ECHARM_ROOT_save is a class derived from ECHARM_atom because it has all its characteristics averaged over the all the atom kind of the crystal.
///   It is really important to check that the ECHARM_ROOT_save is ok before procede with any calculation method of this class.
///   The crystal is formed by a single ECHARM_cell, a single ECHARM_miller class, and many ECHARM_atoms and ECHARM_lattice classes.
///   Each ECHARM_atom has a linked ECHARM_lattice which describe the position of the atom in the cell and the numer of the that atom kind in a unit cell.
///   ECHARM_cell descirbes the fundamental cell properties and affect the ECHARM_lattice class because ECHARM_lattice point coordinates are expressed in terms of the ECHARM_cell base three vectors.
///   ECHARM_miller describes the planar and axial Miller vIndexes on which the calculation are going to be made.
///   Planar electric characteristics can be evaluated for any kind of crystal structures.
///   At the present time any axial characteristic can be evaluated only for cubic structures. For general orthorhombic structures only main axes can be evaluated.
///   has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_ROOT_save class will average electric characteristic.
///   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.
///

#ifndef _ECHARM_ROOT_save_h
#define _ECHARM_ROOT_save_h

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"


#include "ECHARM_file_save.hh"

class ECHARM_ROOT_save: public ECHARM_file_save
{
public:
    ECHARM_ROOT_save(std::string);
    virtual ~ECHARM_ROOT_save();
    
public:
    void Save(ECHARM_info_save *info);

    void Open();
    void Analysis();
    void Close();
    
    inline TTree* GetTree() {return fTree;};
private:
    //ROOT
    TFile *vRootFile;
    
    TTree *fTree;
    TTree *fTreeTraj;
};

#endif
