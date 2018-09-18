//
//  ECHARM_crystal_reciprocal.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef ROOT_
#include "TH1.h"
#include "TH2.h"
#endif

#ifndef _ECHARM_crystal_reciprocal_h
#define _ECHARM_crystal_reciprocal_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#ifdef OPENMP_
#include <omp.h>
#endif

#ifndef _ECHARM_crystal_h
#include "ECHARM_crystal.h"
#endif

class ECHARM_crystal_reciprocal: public ECHARM_crystal
{
public:
    
    //
    // Constructor to Build directly
    //
    ECHARM_crystal_reciprocal();
    ECHARM_crystal_reciprocal(ECHARM_cell *cell, ECHARM_miller *miller, ECHARM_atom *atom, ECHARM_lattice *lattice);
    ECHARM_crystal_reciprocal(ECHARM_crystal *crystal);
    
    virtual ~ECHARM_crystal_reciprocal();
    
    //
    // Retrieval methods
    //
    int GetFourierTermNumberPlanr() {return fFourierTermNumberPlanar;};
    int GetFourierTermNumberAxialX() {return fFourierTermNumberAxialX;};
    int GetFourierTermNumberAxialY() {return fFourierTermNumberAxialY;};

    std::vector< std::vector<double> > GetPlanarFourierCoefficient(unsigned int vType);
    std::vector< std::vector< std::vector<double> > > GetAxialFourierCoefficient(unsigned int vType);
    
    //
    // Set methods
    //
    void SetFourierTermNumberPlanar(int NumberOfTerms) {fFourierTermNumberPlanar = NumberOfTerms;};
    void SetFourierTermNumberAxialX(int NumberOfTerms) {fFourierTermNumberAxialX = NumberOfTerms;};
    void SetFourierTermNumberAxialY(int NumberOfTerms) {fFourierTermNumberAxialY = NumberOfTerms;};
    
    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal_reciprocal*);
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal_reciprocal&);

    //
    // Calculation methods reciprocal
    //
    std::vector<double> FindFourierCoefficient(int vIndex[3], unsigned int vType); //!< Find an array with all the coefficient of the Fourier transform of the selected averaged electric characteristic. Even = Re; Odd = Im. To select electric characteristic one can choose: 0= Potential Energy [eV] ; 3 = Electrical Field [eV/m] on Planar Direction or on first Axial direction;  4 = Electrical Field [eV/m] on the second Axial direction; 1 = atomic density [1/m^3];  "ALD" = electron density [1/m^3]
    std::vector<double> FindFourierCoefficient(int vIndex00,int vIndex01,int vIndex02, unsigned int vType);
    
    std::vector< std::vector<double> > FindPlanarFourierCoefficient(unsigned int vType); //!< Calculate and save in the output vector the Fourier coefficients for a subsequent calculation of the planar electrical component
    std::vector< std::vector< std::vector<double> > > FindAxialFourierCoefficient(unsigned int vType); //!< Calculate and save in the output vector the Fourier coefficients for a subsequent calculation of the planar electrical component

    void FindPlanarFourierCoefficient();//!< Calculate and save in the fFourierCoefficientPlanar***** vectors the Fourier coefficients for a subsequent calculation of the planar electrical component
    void FindAxialFourierCoefficient(); //!< Calculate and save in the fFourierCoefficientAxial***** vectors the Fourier coefficients for a subsequent calculation of the axial electrical component
   
    //
    // Calculation methods single point general
    //
    double GetPlanarElectricCharacteristic(double x, unsigned int vType); //!< Calculation method described in PRE 81, 026708 (2010)
    double GetAxialElectricCharacteristic(double x, double y, unsigned int vType); //!< Calculation method described in PRE 81, 026708 (2010)
    
 
public:
    
    int operator==(const ECHARM_crystal_reciprocal&) const;
    int operator!=(const ECHARM_crystal_reciprocal&) const;
    
public:
    
    ECHARM_crystal_reciprocal(ECHARM_crystal_reciprocal&);
    ECHARM_crystal_reciprocal(const ECHARM_crystal_reciprocal&);
    const ECHARM_crystal_reciprocal & operator=(const ECHARM_crystal_reciprocal&);
    void InitializePointersCrystalReciprocal();
    
private:
    //Reciprocal coefficient
    int fFourierTermNumberPlanar;
    int fFourierTermNumberAxialX;
    int fFourierTermNumberAxialY;

    std::vector< std::vector<double> > fFourierCoefficientPlanarPotential;
    std::vector< std::vector<double> > fFourierCoefficientPlanarAtomicDensity;
    std::vector< std::vector<double> > fFourierCoefficientPlanarElectronDensity;
    std::vector< std::vector<double> > fFourierCoefficientPlanarElectricFieldX;
    
    std::vector< std::vector< std::vector<double> > > fFourierCoefficientAxialPotential;
    std::vector< std::vector< std::vector<double> > > fFourierCoefficientAxialAtomicDensity;
    std::vector< std::vector< std::vector<double> > > fFourierCoefficientAxialElectronDensity;
    std::vector< std::vector< std::vector<double> > > fFourierCoefficientAxialElectricFieldX;
    std::vector< std::vector< std::vector<double> > > fFourierCoefficientAxialElectricFieldY;
};

#endif
