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

#ifndef _ECHARM_Latticeh
#define _ECHARM_Latticeh
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <iomanip>

#ifndef _ECHARM_threevector_h
#include "ECHARM_threevector.h"
#endif

class ECHARM_lattice
{
public:
    
    //
    // Constructors
    //
    ECHARM_lattice();
    ECHARM_lattice(std::string LatticeType);
    ~ECHARM_lattice();
    
    //
    // Retrieval methods
    //
    std::string  GetLatticeType()   const {return fLatticeType;};
    int  GetNumberOfCoordinates()   const {return fLatticeCoordinates.size();};
    std::vector< ECHARM_threevector* > GetLatticeCoordinates() {return fLatticeCoordinates;};
    void ReadCoordinatesFromFile(std::string vFileName);
    void ReadCoordinatesNotNormalizedFromFile(std::string vFileName, ECHARM_threevector *vSize);

    //
    // Printing methods
    //    
    friend std::ostream& operator<<(std::ostream&, ECHARM_lattice*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_lattice&);    
    void PrintLatticeCoordinates();
    void PrintLatticeCoordinates(std::string Axis);
    void SetLatticeCoordinates(std::vector<ECHARM_threevector*> vLatticeCoordinates) {fLatticeCoordinates = vLatticeCoordinates;};

    //
    // Set methods
    //    
    void SetLatticeType(std::string LatticeType)  {fLatticeType = LatticeType; FindLatticePoints();};
    void SetCell(std::string File_Cell);
    
    void AddThreeVector(double X, double Y, double Z);
    void DeleteThreeVector(unsigned int vIndex);

    //
    // Calculation methods
    //    
    std::vector<double> FindStructureFactor(int vIndex[3]);
    std::vector<double> FindStructureFactor(int vIndex00,int vIndex01,int vIndex02);

public:
    
    int operator==(const ECHARM_lattice&) const;
    int operator!=(const ECHARM_lattice&) const;
    
public:
    
    ECHARM_lattice(ECHARM_lattice&);
    ECHARM_lattice(const ECHARM_lattice&);
    const ECHARM_lattice & operator=(const ECHARM_lattice&);

private:
    void InitializePointersLattice();
    void FindLatticePoints();
    std::string fLatticeType;       
    std::vector<ECHARM_threevector*> fLatticeCoordinates;
};

#endif
