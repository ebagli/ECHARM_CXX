//
//  ECHARM_crystal_Si.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_crystal_Si::ECHARM_crystal_Si(int vMillerPl[3],int vMillerAx[3])
{
    std::vector<double> vSiExperimentalCoefficients;
    vSiExperimentalCoefficients.clear();
    
    vSiExperimentalCoefficients.push_back(4.94976/14.);
    vSiExperimentalCoefficients.push_back(3.25403/14.);
    vSiExperimentalCoefficients.push_back(2.84957/14.);
    vSiExperimentalCoefficients.push_back(1.66053/14.);
    vSiExperimentalCoefficients.push_back(1.22949/14.);
    vSiExperimentalCoefficients.push_back(0.05611/14.);
    
    vSiExperimentalCoefficients.push_back(2.70254E-20);
    vSiExperimentalCoefficients.push_back(34.45314E-20);
    vSiExperimentalCoefficients.push_back(1.24059E-20);
    vSiExperimentalCoefficients.push_back(0.07201E-20);
    vSiExperimentalCoefficients.push_back(84.53648E-20);
    vSiExperimentalCoefficients.push_back(56.34208E-20);
    
    ECHARM_atom *atom = new ECHARM_atom("Si",14.,28.086 * amu,640.,450.,173.,2,vSiExperimentalCoefficients);
    atom->SetThermalVibrationConstant(0.075E-10);
    ECHARM_lattice *lattice = new ECHARM_lattice("diamond");
    ECHARM_miller *miller = new ECHARM_miller(vMillerPl,vMillerAx);
    ECHARM_cell *cell = new ECHARM_cell(5.4309E-10,5.4309E-10,5.4309E-10);
   
    SetCell(cell);
    SetMiller(miller);
    AddBase(atom,lattice);
    
    ComputeCrystalAverageParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Si::~ECHARM_crystal_Si()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


const ECHARM_crystal_Si& ECHARM_crystal_Si::operator=(const ECHARM_crystal_Si& right)
{
    if (this != &right)
    {
    }
    return *this;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal_Si::operator==(const ECHARM_crystal_Si& right) const
{
    return (this == (ECHARM_crystal_Si*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal_Si::operator!=(const ECHARM_crystal_Si& right) const
{
    return (this != (ECHARM_crystal_Si*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
