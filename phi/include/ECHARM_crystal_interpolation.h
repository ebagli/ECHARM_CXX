//
//  ECHARM_crystal_interpolation.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   Class ECHARM_crystal_interpolation is a class derived from ECHARM_atom because it has all its characteristics averaged over the all the atom kind of the crystal.
///   It is really important to check that the ECHARM_crystal_interpolation is ok before procede with any calculation method of this class.
///   The crystal is formed by a single ECHARM_cell, a single ECHARM_miller class, and many ECHARM_atoms and ECHARM_lattice classes.
///   Each ECHARM_atom has a linked ECHARM_lattice which describe the position of the atom in the cell and the numer of the that atom kind in a unit cell.
///   ECHARM_cell descirbes the fundamental cell properties and affect the ECHARM_lattice class because ECHARM_lattice point coordinates are expressed in terms of the ECHARM_cell base three vectors.
///   ECHARM_miller describes the planar and axial Miller vIndexes on which the calculation are going to be made.
///   Planar electric characteristics can be evaluated for any kind of crystal structures.
///   At the present time any axial characteristic can be evaluated only for cubic structures. For general orthorhombic structures only main axes can be evaluated.
///   has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_crystal_interpolation class will average electric characteristic.
///   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.
///

#ifndef _ECHARM_crystal_interpolation_h
#define _ECHARM_crystal_interpolation_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cfloat>

#ifndef _ECHARM_crystal_h
#include "ECHARM_crystal.h"
#endif

#ifndef _ECHARM_interpolation_h
#include "ECHARM_interpolation.h"
#endif

class ECHARM_crystal_interpolation: public ECHARM_crystal
{
public:
    
    //
    // Constructor to Build directly
    //
    ECHARM_crystal_interpolation();
    ECHARM_crystal_interpolation(ECHARM_cell *cell, ECHARM_miller *miller, ECHARM_atom *atom, ECHARM_lattice *lattice);
    ECHARM_crystal_interpolation(ECHARM_crystal *crystal,bool bCalculateAxial = false);
    ECHARM_crystal_interpolation(ECHARM_crystal_interpolation *crystal);

    virtual ~ECHARM_crystal_interpolation();
    
    //
    // Retrieval methods
    //
    ECHARM_interpolation* GetInterpolationFunction() {return fInterpolationFunction;};

    std::vector<double> GetPlanarElectricCharacteristicVector( unsigned int vType );
    std::vector<double> GetAxialElectricCharacteristicVector( unsigned int vType );

    double GetPotentialMaximum();
    double GetPotentialMinimum();
    double GetElectricFieldMaximum();

    double GetPotentialMaximumAxial();
    double GetElectricFieldMaximumAxial();
    //
    // Set methods
    //
    void SetInterpolationFunction(ECHARM_interpolation* vInterpolationFunction) {fInterpolationFunction = vInterpolationFunction;};

    void SetElectricCharacteristicPlanar(std::vector<double> vVectorStart, std::vector<double> vVectorEnd);
    void SetElectricCharacteristicPlanar(std::vector<double> vVector, unsigned int vType);
    void SetElectricCharacteristicAxial(std::vector<double> vVectorStart, std::vector<double> vVectorEnd);
    void SetElectricCharacteristicAxial(std::vector<double> vVector, unsigned int vType);

    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal_interpolation*);
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal_interpolation&);
    
    //
    // IO methods
    //    
    void ReadPlanarElectricCharacteristicFromFileInterpolation(std::string FileInName, unsigned int vType);
    void ReadAxialElectricCharacteristicFromFileInterpolation(std::string FileInName, unsigned int vType);
    
    //
    // Calculation methods single point general
    //
    double GetPlanarElectricCharacteristicInterpolation(double x, std::vector<double> & vVector); //!<  Linear Interpolation using 2 points around selected position
    double GetAxialElectricCharacteristicInterpolation(double x, double y, std::vector<double> vVector); //!<  Linear Interpolation using 4 points around selected position

    double GetPlanarElectricCharacteristic(double x, unsigned int vType);
    double GetAxialElectricCharacteristic(double x, double y, unsigned int vType);
        
public:
    
    int operator==(const ECHARM_crystal_interpolation&) const;
    int operator!=(const ECHARM_crystal_interpolation&) const;
    
public:
    
    const ECHARM_crystal_interpolation & operator=(const ECHARM_crystal_interpolation&);
    void InitializePointersCrystalInterpolation();
    
private:
     //Electric characteristics
    std::vector<double> fPlanarPotential;
    std::vector<double> fPlanarAtomicDensity;
    std::vector<double> fPlanarElectronDensity;
    std::vector<double> fPlanarElectricFieldX;
    
    std::vector<double> fAxialPotential;
    std::vector<double> fAxialAtomicDensity;
    std::vector<double> fAxialElectronDensity;
    std::vector<double> fAxialElectricFieldX;
    std::vector<double> fAxialElectricFieldY;
    
    ECHARM_interpolation *fInterpolationFunction;
};

#endif
