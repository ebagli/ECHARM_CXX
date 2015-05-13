//
//  ECHARM_atom.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_atom_h
#include "ECHARM_atom.hh"

ECHARM_atom::ECHARM_atom(std::string  AtomName,
                         double Z,
                         double A,
                         double DebyeTemperature,
                         double AverageIonizationConstant)
{
    fAtomName = AtomName;
    fZ = Z;
    fA = A;
    fDebyeTemperature = DebyeTemperature;
    fAverageIonizationConstant = AverageIonizationConstant;
    
    fTemperature = 273;
    
    fThermalVibrationConstant = ComputeThermalVibration();
    fThomasFermiRadius = ComputeThomasFermiRadius();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom::ECHARM_atom(std::string File_Atom)
{
    std::ifstream File_Atom_In;
    
    File_Atom_In.open(File_Atom.c_str());
    if(File_Atom_In)
    {
        if(File_Atom_In.good()) File_Atom_In >> fAtomName;
        if(File_Atom_In.good()) File_Atom_In >> fZ;
        if(File_Atom_In.good()) File_Atom_In >> fA;
        fA *= amu;
        if(File_Atom_In.good()) File_Atom_In >> fDebyeTemperature;
        if(File_Atom_In.good()) File_Atom_In >> fAverageIonizationConstant;
    }
    else std::cout << "ECHARM_atom ERROR - file does not exist" << std::endl;
    File_Atom_In.close();
    
    ComputeThermalVibration();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom::~ECHARM_atom(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_atom::Print()
{
    std::cout << "ECHARM_atom - Print " << fAtomName << " Properties" << std::endl;
    std::cout << "AtomName                       " << std::setw(10) << fAtomName << std::endl;
    std::cout << "A                              " << std::setw(10) << fA/amu << std::endl;
    std::cout << "Z                              " << std::setw(10) << fZ << std::endl;
    std::cout << "Debye Temperature           [K]" << std::setw(10) << fDebyeTemperature << std::endl;
    std::cout << "Ionization Constant        [eV]" << std::setw(10) << fAverageIonizationConstant << std::endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::ComputeThermalVibration()
{
    double ThermalVibrationConstant = 0.;
    
    if(fDebyeTemperature==0.0) {
        ThermalVibrationConstant = 0.0;
    }
    else{
        double Constant = ( (3 * cPlanckConstant * cPlanckConstant) / (4 * cBoltzmanConstant * fA * GetDebyeTemperature()));
        double Integral = 0.0;
        
        int i;
        int IntegrationStepNumber = 8192;
        double y_var_0 = GetDebyeTemperature() / GetTemperature() / IntegrationStepNumber;
        double y_var = 0.0;
        double y_value = 0.0;
        for(i=1;i<IntegrationStepNumber;i++){
            y_var = i * y_var_0;
            y_value = ( y_var / (exp(y_var) - 1));
            Integral += (y_value * y_var_0 );
        }
        ThermalVibrationConstant = fSquareRoot( Constant * ( 1 + 4 * Integral * fSquare(GetTemperature()/GetDebyeTemperature())) );
    }
    
    fThermalVibrationConstant = ThermalVibrationConstant;
    return ThermalVibrationConstant;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::ComputeThomasFermiRadius()
{
    double BohrRadius = 0.529177E-10;
    double ThomasFermiRadius = BohrRadius * 0.8853 / pow (fZ , 0.333333333);
    return ThomasFermiRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif