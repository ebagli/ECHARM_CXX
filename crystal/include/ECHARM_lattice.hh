//
//  ECHARM_lattice.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_lattice is a container of the coordinate of lattice points expressed as a ratio on the main cell size
//   It is forbidden to have a difference number of vIndexes for the three coordinate vector.
//   The coordinate are not expressed in an orthogonal base but in the cell base which will be selected in the ECHARM_crystal class.

#ifndef _ECHARM_Lattice_h
#define _ECHARM_Lattice_h

#include "ECHARM_3vec.hh"

class ECHARM_lattice
{
public:
    
    ECHARM_lattice();
    ~ECHARM_lattice();
    
    void ReadFile(std::string vFileName);
    void ReadFile(std::string vFileName, ECHARM_3vec *vSize);

    void Print();
    
    std::vector<double> ComputeSF(int vIndex[3]); //Compute Structure Factor
    std::vector<double> ComputeSF(int vIndex00,int vIndex01,int vIndex02); //Compute Structure Factor

private:
    std::vector<ECHARM_3vec*> fLatticeCoordinates;

#include "ECHARM_lattice.hxx"
};

#endif
