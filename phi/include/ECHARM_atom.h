//
//  ECHARM_atom.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   This class has to be filled with atomic parameters only.
///   Thermal vibration amplitude is automatically evaluated.
///   No input from standard databases are implemented right now.
///

#ifndef _ECHARM_atom_h
#define _ECHARM_atom_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <iomanip>

#ifndef _ECHARM_constants_h
#include "ECHARM_constants.h"
#endif

class ECHARM_atom
{
public:
    
    //
    // Constructor to Build an element directly; no reference to isotopes
    //
    ECHARM_atom();
    
    ECHARM_atom(std::string AtomName,
                double Z,
                double A,
                double DebyeTemperature,
                double Temperature,
                double AverageIonizationConstant,
                unsigned int FormFactorType = 1,
                std::vector<double> ExperimentalFormFactorParameters = std::vector<double>()
                ); //!< Create an atom from its properties. The input unit are amu for A, K for Temperature and Debye Temperature, eV for Ionization constant.
    
    ECHARM_atom(std::string File_Atom);    //!< Read an atom from a file. The sequence of the variable is: name, Z, A [amu], Debye temperature [K], temperature [K], Ionization constant [eV], Form Factor type [0/1/2 see GetFormFactorType()].

    virtual ~ECHARM_atom();
    
    //
    // Retrieval methods
    //
    std::string  GetAtomName()   const {return fAtomName;} //!< Get name.
    double GetZ() const {return fZ;}      //!< Get atomic number Z.
    double GetA() const {return fA;}    //!< Get atomic A in amu.
    double GetDebyeTemperature() const {return fDebyeTemperature;}   //!< Get Debye Temperature in K.
    double GetTemperature() const {return fTemperature;}   //!< Get Temperature in K.
    double GetAverageIonizationConstant() const {return fAverageIonizationConstant;}    //!< Get Ionization Constant in eV.
    unsigned int GetFormFactorType() const {return fFormFactorType;}   //!< Get Form Factor type: 0 = Simple negative exponential; 1 = Moliere Approximation; 2 = Form Factor from experimental coefficients;
    double GetThermalVibrationConstant()      const {return fThermalVibrationConstant;}     //!< Get Thermal Vibration Amplitude in meter.
    std::vector<double> GetExperimentalFormFactorParameters() {return fExperimentalFormFactorParameters;}  //!< Get Experimental Coefficients for Form Factor.
    double GetExperimentalFormFactorParameter(int vIndex) {return fExperimentalFormFactorParameters[vIndex];}  //!< Get Experimental Coefficients for Form Factor at vIndex.

    //
    // Set methods
    //
    void SetAtomName(std::string AtomName)    {fAtomName=AtomName;} //!< Set name.
    void SetZ(double Z) {fZ=Z;}         //!< Set atomic number Z.
    void SetA(double A) {fA=A;}     //!< Set atomic weight in amu.
    void SetDebyeTemperature(double DebyeTemperature) {fDebyeTemperature=DebyeTemperature; ComputeThermalVibration();}    //!< Set Debye Temperature in K.
    void SetTemperature(double Temperature) {fTemperature=Temperature; ComputeThermalVibration();}     //!< Set Temperature in K.
    void SetAverageIonizationConstant(double AverageIonizationConstant) {fAverageIonizationConstant=AverageIonizationConstant;}      //!< Set Ionization Constant in eV.
    void SetFormFactorType(unsigned int FormFactorType) {fFormFactorType=FormFactorType;}  //!< Set Form Factor type: 0 = Simple negative exponential; 1 = Moliere Approximation; 2 = Form Factor from experimental coefficients;
    void SetThermalVibrationConstant(double ThermalVibrationConstant) {fThermalVibrationConstant=ThermalVibrationConstant;}     //!< Set Thermal Vibration Amplitude in meter.
    void SetExperimentalFormFactorParameters(std::vector<double> ExperimentalFormFactorParameters) {fExperimentalFormFactorParameters=ExperimentalFormFactorParameters;}  //!< Set Experimental Coefficients for Form Factor.
    void SetExperimentalFormFactorParameter(int vIndex,double ExperimentalFormFactorParameter) {fExperimentalFormFactorParameters[vIndex]=ExperimentalFormFactorParameter;} //!< Set Experimental Coefficients for Form Factor at vIndex.

    
    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_atom*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_atom&);    
    void PrintAtomProperties(); //!< Print properties of the atom.

    
    //
    // Calculate methods
    //
    double FindThomasFermiRadius();
    double FindFormFactorReciprocal(double ReciprocalVectorSquared); //!< Evaluate the reciprocal Form Factor value giving a reciprocal vector squared. The atom is centered at (0.,0.,0.).
    double FindFormFactorReciprocalSimple(double ReciprocalVectorSquared); //!< Evaluate the reciprocal Form Factor value giving a reciprocal vector squared. The atom is centered at (0.,0.,0.).
    double FindFormFactorReciprocalMoliere(double ReciprocalVectorSquared); //!< Evaluate the reciprocal Form Factor value giving a reciprocal vector squared. The atom is centered at (0.,0.,0.).
    double FindFormFactorReciprocalExperimental(double ReciprocalVectorSquared); //!< Evaluate the reciprocal Form Factor value giving a reciprocal vector squared. The atom is centered at (0.,0.,0.).
    double FindFormFactorReciprocalLindhard(double ReciprocalVectorSquared); //!< Evaluate the reciprocal Form Factor value giving a reciprocal vector squared. The atom is centered at (0.,0.,0.).
    
    double FindFormFactorDirect(double DirectVectorSquared);//!< Evaluate the direct Form Factor value giving a direct vector squared. The atom is centered at (0.,0.,0.).
    double FindFormFactorDirectSimple(double DirectVector);//!< Evaluate the direct Form Factor value giving a direct vector. The atom is centered at (0.,0.,0.).
    double FindFormFactorDirectMoliere(double DirectVector);//!< Evaluate the direct Form Factor value giving a direct vector. The atom is centered at (0.,0.,0.).
    double FindFormFactorDirectLindhard(double DirectVector);//!< Evaluate the direct Form Factor value giving a direct vector. The atom is centered at (0.,0.,0.).
    double FindFormFactorDirectExperimental(double DirectVector);//!< Evaluate the direct Form Factor value giving a direct vector. The atom is centered at (0.,0.,0.).
    double FindFormFactorDirectMoliereAveragedOverTemperature(double DirectVector); //!< Evaluate the direct Form Factor value giving a direct vector. The atom is centered at (0.,0.,0.).
 
    double FindFormFactorDirectSimpleDerivate(double DirectVector);//!<
    double FindFormFactorDirectMoliereDerivate(double DirectVector);//!< .
    double FindFormFactorDirectLindhardDerivate(double DirectVector);//!< 
    double FindFormFactorDirectExperimentalDerivate(double DirectVector);//!<
    
    void ComputeThermalVibration();//!< Compute Thermal Vibration Constant.

public:
    
    int operator==(const ECHARM_atom&) const;
    int operator!=(const ECHARM_atom&) const;
    
public:
    
    ECHARM_atom(ECHARM_atom&);
    ECHARM_atom(const ECHARM_atom&);
    const ECHARM_atom & operator=(const ECHARM_atom&);
    void InitializePointersAtom();//!< Initialize pointers of the atom.
    
private:
    
    std::string  fAtomName;        
    double fZ;            
    double fA;             
    double fDebyeTemperature;          
    double fTemperature;          
    double fAverageIonizationConstant;              
    unsigned int fFormFactorType;
    double fThermalVibrationConstant;            
    std::vector<double> fExperimentalFormFactorParameters;
};

#endif
