//
//  ECHARM_crystal_Ge.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_crystal_Ge::ECHARM_crystal_Ge(int vMillerPl[3],int vMillerAx[3])
{
    std::vector<double> vGeExperimentalCoefficients;
    vGeExperimentalCoefficients.clear();
    
    vGeExperimentalCoefficients.push_back(9.56335/32.);
    vGeExperimentalCoefficients.push_back(7.86994/32.);
    vGeExperimentalCoefficients.push_back(7.64215/32.);
    vGeExperimentalCoefficients.push_back(3.31296/32.);
    vGeExperimentalCoefficients.push_back(2.13351/32.);
    vGeExperimentalCoefficients.push_back(1.47704/32.);
    
    vGeExperimentalCoefficients.push_back(2.21494E-20);
    vGeExperimentalCoefficients.push_back(0.14284E-20);
    vGeExperimentalCoefficients.push_back(3.86490E-20);
    vGeExperimentalCoefficients.push_back(32.69417E-20);
    vGeExperimentalCoefficients.push_back(8.94286E-20);
    vGeExperimentalCoefficients.push_back(82.15827E-20);
    
    ECHARM_atom *atom = new ECHARM_atom("Ge",32.,72.61 * amu,360.0,450.,350.0,2,vGeExperimentalCoefficients);
    ECHARM_lattice *lattice = new ECHARM_lattice("diamond");
    ECHARM_miller *miller = new ECHARM_miller(vMillerPl,vMillerAx);
    ECHARM_cell *cell = new ECHARM_cell(5.6575E-10,5.6575E-10,5.6575E-10);
    
   
    SetCell(cell);
    SetMiller(miller);
    AddBase(atom,lattice);
    
    ComputeCrystalAverageParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Ge::~ECHARM_crystal_Ge()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


const ECHARM_crystal_Ge& ECHARM_crystal_Ge::operator=(const ECHARM_crystal_Ge& right)
{
    if (this != &right)
    {
    }
    return *this;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal_Ge::operator==(const ECHARM_crystal_Ge& right) const
{
    return (this == (ECHARM_crystal_Ge*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal_Ge::operator!=(const ECHARM_crystal_Ge& right) const
{
    return (this != (ECHARM_crystal_Ge*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
