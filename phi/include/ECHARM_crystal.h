//
//  ECHARM_crystal.h
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

#ifdef ROOT_
#include "TH1.h"
#include "TH2.h"
#endif

#ifndef _ECHARM_crystal_h
#define _ECHARM_crystal_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <cfloat>

#ifndef _ECHARM_constants_h
#include "ECHARM_constants.h"
#endif

#ifndef _ECHARM_atom_h
#include "ECHARM_atom.h"
#endif

#ifndef _ECHARM_lattice_h
#include "ECHARM_lattice.h"
#endif

#ifndef _ECHARM_miller_h
#include "ECHARM_miller.h"
#endif

#ifndef _ECHARM_cell_h
#include "ECHARM_cell.h"
#endif


class ECHARM_crystal: public ECHARM_atom
{
public:
    
    //
    // Constructor to Build directly
    //
    ECHARM_crystal();
    ECHARM_crystal(ECHARM_cell *cell, ECHARM_miller *miller, ECHARM_atom *atom, ECHARM_lattice *lattice);
    
    virtual ~ECHARM_crystal();
    
    //
    // Retrieval methods
    //    
    ECHARM_atom* GetAtom(unsigned int vIndex);
    ECHARM_lattice* GetLattice(unsigned int vIndex);
    float GetPercentage(unsigned int vIndex);
    ECHARM_miller* GetMiller();
    ECHARM_cell* GetCell();
    
    unsigned int GetNumberOfBases() {return fAtom.size();};

    unsigned int GetIntegrationStepNumberPlanar() {return fIntegrationStepNumberPlanar;};
    unsigned int GetIntegrationStepNumberAxialX() {return fIntegrationStepNumberAxialX;};
    unsigned int GetIntegrationStepNumberAxialY() {return fIntegrationStepNumberAxialY;};

    double GetStepPlanar() {return (fDirectPeriodPlanar / fIntegrationStepNumberPlanar);};
    double GetStepAxialX() {return (fDirectPeriodAxialX / fIntegrationStepNumberAxialX);};
    double GetStepAxialY() {return (fDirectPeriodAxialY / fIntegrationStepNumberAxialY);};
 
    double GetDirectPeriodPlanar() {return fDirectPeriodPlanar;};
    double GetDirectPeriodAxialX() {return fDirectPeriodAxialX;};
    double GetDirectPeriodAxialY() {return fDirectPeriodAxialY;};
    
    double GetReciprocalPeriodPlanar() {return fReciprocalPeriodPlanar;};
    double GetReciprocalPeriodAxialX() {return fReciprocalPeriodAxialX;};
    double GetReciprocalPeriodAxialY() {return fReciprocalPeriodAxialY;};
    
    double GetNucleiDensity() {return fNumberOfCoordinatesTotal/GetCell()->FindVolume();};
    double GetNuclearDensity() {return GetZ() * fNumberOfCoordinatesTotal/GetCell()->FindVolume();};
    double GetMassDensity() {return GetA() * fNumberOfCoordinatesTotal/GetCell()->FindVolume();};
    
    virtual double GetPotentialMaximum() {return fPotentialMaximum;};
    virtual double GetPotentialCritical() {return GetPotentialDifference(2.5 * GetThermalVibrationConstant(),fDirectPeriodPlanar / 2.0);};
    virtual double GetPotentialMinimum() {return fPotentialMinimum;};
    virtual double GetElectricFieldMaximum() {return fElectricFieldMaximum;};
    virtual double GetElectricFieldCritical() {return GetPlanarElectricCharacteristic(2.5 * GetThermalVibrationConstant(),3);};

    virtual double GetPotentialMaximumAxial() {return fPotentialMaximum;};
    virtual double GetElectricFieldMaximumAxial() {return fElectricFieldMaximum;};
    
    double GetPotentialDifference(double vFirstPoint,double vSecondPoint);
    double GetPotentialDifferenceAxial(double vFirstPointX,double vFirstPointY,double vSecondPointX,double vSecondPointY);

    double GetValueInPeriodicUnit(double vX, double &vPeriod);

    inline double GetValueInPeriodicUnitPlanar(double vX) {return GetValueInPeriodicUnit(vX,fDirectPeriodPlanar);};
    inline double GetValueInPeriodicUnitAxialX(double vX) {return GetValueInPeriodicUnit(vX,fDirectPeriodAxialX);};
    inline double GetValueInPeriodicUnitAxialY(double vY) {return GetValueInPeriodicUnit(vY,fDirectPeriodAxialY);};

    //
    // Set methods
    //
    void AddBase(ECHARM_atom *atom, ECHARM_lattice *lattice,float percentage = 1.);
    void SetBase(unsigned int vIndex,ECHARM_atom *atom, ECHARM_lattice *lattice,float percentage = 1.);
    void SetAtom(unsigned int vIndex,ECHARM_atom *atom);
    void SetPercentage(unsigned int vIndex,float percentage);
    void SetLattice(unsigned int vIndex, ECHARM_lattice *lattice);
    void SetMiller(ECHARM_miller* miller);
    void SetCell(ECHARM_cell* cell);
    
    void SetIntegrationStepNumberPlanar(unsigned int NumberOfSteps) {fIntegrationStepNumberPlanar = NumberOfSteps;};
    void SetIntegrationStepNumberAxialX(unsigned int NumberOfSteps) {fIntegrationStepNumberAxialX = NumberOfSteps;};
    void SetIntegrationStepNumberAxialY(unsigned int NumberOfSteps) {fIntegrationStepNumberAxialY = NumberOfSteps;};
    
    void SetDirectPeriodPlanar(double Period) {fDirectPeriodPlanar = Period;};
    void SetDirectPeriodAxialX(double Period) {fDirectPeriodAxialX = Period;};
    void SetDirectPeriodAxialY(double Period) {fDirectPeriodAxialY = Period;};
    
    void SetReciprocalPeriodPlanar(double Period) {fReciprocalPeriodPlanar = Period;};
    void SetReciprocalPeriodAxialX(double Period) {fReciprocalPeriodAxialX = Period;};
    void SetReciprocalPeriodAxialY(double Period) {fReciprocalPeriodAxialY = Period;};
    
    void SetPotentialMaximum(double vPotential) {fPotentialMaximum = vPotential;};
    void SetElectricFieldMaximum(double vElectricField) {fElectricFieldMaximum = vElectricField;};
    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal*);
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal&);
    void PrintPropertiesOfBase(unsigned int vIndex);
    void PrintPropertiesCrystal();
    std::string GetCharacteristicType(unsigned int vType);

    std::vector<double> ReadPlanarElectricCharacteristicFromFile(std::string FileInName);
    std::vector<double> ReadAxialElectricCharacteristicFromFile(std::string FileInName);

    void PrintPlanarElectricCharacteristicToFile(std::string FileOut, std::vector<double> vVector, std::string vOptions = "");
    void PrintAxialElectricCharacteristicToFile(std::string FileOut, std::vector<double> vVector, std::string vOptions = "");
   
#ifdef ROOT_
    void PrintPlanarElectricCharacteristicToTH1(std::string vName, std::vector<double> vVector, std::string vOptions = "");
    void PrintAxialElectricCharacteristicToTH2(std::string vName, std::vector<double> vVector, std::string vOptions = "");
#endif
    
    //
    // Check methods
    //
    bool CheckCrystal(); //!< Check if all the element of the crystal class has been initialized correctly.

    //
    // Calculation methods structure factor coefficients
    //
    std::vector<double> FindStructureFactorCoefficient(int vIndex[3]);
    std::vector<double> FindStructureFactorCoefficient(int vIndex00,int vIndex01,int vIndex02);

    //
    // Calculation methods single point general
    //
    virtual double GetPlanarElectricCharacteristic(double x, unsigned int vType) {return 0.0;};
    virtual double GetAxialElectricCharacteristic(double x, double y, unsigned int vType) {return 0.0;};
    
    std::vector<double> NormalizeElectricCharacteristic(std::vector<double> vVector);

    //
    // Calculation methods all points general
    //
    std::vector<double> FindPlanarElectricCharacteristic(unsigned int vType, std::string vOptions = ""); //!< Calculate and save in the output vector the values of the selected electrical component averaged along a planar direction
    std::vector<double> FindAxialElectricCharacteristic(unsigned int vType, std::string vOptions = "");//!< Calculate and save in the output vector the values of the selected electrical component averaged along an axial direction

    
    //
    // Calculation methods coefficients
    //
    void ComputeCrystalAverageParameters(); //!< Compute the crystal average parameters starting from the atom properties of the bases.
    int ComputeAxialVectorIndex(int i,int j, int vTermNumberX, int vTermNumberX0 = 0,int vTermNumberY0 = 0);
    
public:
    
    int operator==(const ECHARM_crystal&) const;
    int operator!=(const ECHARM_crystal&) const;
    
public:
    
    ECHARM_crystal(ECHARM_crystal&);
    ECHARM_crystal(const ECHARM_crystal&);
    const ECHARM_crystal & operator=(const ECHARM_crystal&);
    void InitializePointersCrystal();
    
protected:
    ECHARM_cell *fCell;
    ECHARM_miller *fMiller;
    std::vector<ECHARM_atom*> fAtom;
    std::vector<ECHARM_lattice*> fLattice;
    std::vector<float> fPercentage;
    unsigned int fNumberOfCoordinatesTotal;
    
    unsigned int fIntegrationStepNumberPlanar;
    unsigned int fIntegrationStepNumberAxialX;
    unsigned int fIntegrationStepNumberAxialY;
    
    double fDirectPeriodPlanar;
    double fDirectPeriodAxialX;
    double fDirectPeriodAxialY;
    
    double fReciprocalPeriodPlanar;
    double fReciprocalPeriodAxialX;
    double fReciprocalPeriodAxialY;
    
    double fPotentialMaximum;
    double fPotentialMinimum;
    double fElectricFieldMaximum;

    double fPotentialMaximumAxial;
    double fElectricFieldMaximumAxial;

};

#endif
