//
//  ECHARM_crystal_LiNbO3_supercell.hh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   Class ECHARM_crystal_LiNbO3_supercell is a class derived from ECHARM_atom because it has all its characteristics averaged over the all the atom kind of the crystal.
///   It is really important to check that the ECHARM_crystal_LiNbO3_supercell is ok before procede with any calculation method of this class.
///   The crystal is formed by a single ECHARM_cell, a single ECHARM_miller class, and many ECHARM_atoms and ECHARM_lattice classes.
///   Each ECHARM_atom has a linked ECHARM_lattice which describe the position of the atom in the cell and the numer of the that atom kind in a unit cell.
///   ECHARM_cell descirbes the fundamental cell properties and affect the ECHARM_lattice class because ECHARM_lattice point coordinates are expressed in terms of the ECHARM_cell base three vectors.
///   ECHARM_miller describes the planar and axial Miller vIndexes on which the calculation are going to be made.
///   Planar electric characteristics can be evaluated for any kind of crystal structures.
///   At the present time any axial characteristic can be evaluated only for cubic structures. For general orthorhombic structures only main axes can be evaluated.
///   has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_crystal_LiNbO3_supercell class will average electric characteristic.
///   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.
///

#ifndef _ECHARM_crystal_LiNbO3_supercell_h
#define _ECHARM_crystal_LiNbO3_supercell_h

#include "ECHARM_crystal.hh"

class ECHARM_crystal_LiNbO3_supercell: public ECHARM_crystal
{
public:
    ECHARM_crystal_LiNbO3_supercell();
    virtual ~ECHARM_crystal_LiNbO3_supercell();
};

#endif
