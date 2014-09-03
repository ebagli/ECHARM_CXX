//
//  ECHARM_crystal.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#include <cfloat>
#include <limits>
#include "ECHARM_crystal.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......ECHARM_crystal::ECHARM_crystal(ECHARM_cell *cell,

ECHARM_crystal::ECHARM_crystal():
ECHARM_atom("crystal",
            -1,
            -1,
            -1,
            -1){
    fAtom.clear();
    fLattice.clear();
    fPercentage.clear();
    
    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,0};

    fMiller = new ECHARM_miller(vMillerX,vMillerY);
    fCell = new ECHARM_cell(1.*AA,1.*AA,1.*AA);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......ECHARM_crystal::ECHARM_crystal(ECHARM_cell *cell,

ECHARM_crystal::ECHARM_crystal(ECHARM_cell *cell,
                               ECHARM_miller *miller,
                               ECHARM_atom *atom,
                               ECHARM_lattice *lattice):
ECHARM_atom("crystal",
            -1,
            -1,
            -1,
            -1){
    fAtom.clear();
    fLattice.clear();
    fPercentage.clear();
    
    fCell = cell;
    fMiller = miller;
    AddBase(atom,lattice);

    ComputeParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal::~ECHARM_crystal(){
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_crystal::CheckCrystal(){
    if(GetCell()->CheckCell()){
        if(fAtom.size() > 0){
            if(fAtom.size() == fLattice.size()){
                return 1;
            }
            else std::cout << "ECHARM_crystal ERROR - There is a different number of atoms and lattices" << std::endl;
        }
        else std::cout << "ECHARM_crystal ERROR - There are no Miller vIndexes" << std::endl;
    }
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::PrintBase(unsigned int vIndex){
    fAtom[vIndex]->Print();
    fLattice[vIndex]->Print();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::PrintTot(){
    std::cout << "ECHARM_crystal - Crystal Properties" << std::endl;
    Print();
    fMiller->Print();
    fCell->Print();
    for(unsigned int vIndex=0; vIndex < GetNumBases();vIndex++) {
        PrintBase(vIndex);
    }
    std::cout << "Interplanar Distance X [A] " << std::setw(8) << fPeriod[0]*1.E10 << std::endl;
    std::cout << "                     Y [A] " << std::setw(8) << fPeriod[1]*1.E10 << std::endl;
    std::cout << "                     Z [A] " << std::setw(8) << fPeriod[2]*1.E10 << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::string ECHARM_crystal::PrintNameOnString(std::string vAddition = ""){
    std::string vHistoName;
    vHistoName = GetAtomName() + GetMiller()->GetTextX() + GetMiller()->GetTextY() + GetMiller()->GetTextZ()   + vAddition;
    return vHistoName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::AddBase(ECHARM_atom *atom,ECHARM_lattice *lattice, float percentage)
{
    fAtom.push_back(atom);
    fLattice.push_back(lattice);
    fPercentage.push_back(percentage);
    ComputeParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::ComputeParameters()
{
    double vZ = 0.0;
    double vA = 0.0;
    double vAvIonConst = 0.0;
    double vDT = 0.0;
    double vTemp = 0.0;
    double vTV = 0.0;
    int vNumCoord = 0;
    
    for(unsigned int i=0;i<GetNumBases();i++){
        double vNumCoordAtom = double(GetLattice(i)->GetCoordinatesNumber()) * GetPercentage(i);
        
        vNumCoord += vNumCoordAtom;
        vZ += GetAtom(i)->GetZ() * vNumCoordAtom;
        vA += GetAtom(i)->GetA() * vNumCoordAtom;
        vDT += GetAtom(i)->GetDebyeTemperature() * vNumCoordAtom;
        vTemp += GetAtom(i)->GetTemperature() * vNumCoordAtom;
        vTV += GetAtom(i)->GetThermalVibrationConstant() * vNumCoordAtom;
        vAvIonConst += GetAtom(i)->GetAverageIonizationConstant() * vNumCoordAtom;
    }
    
    fNumCoord = vNumCoord;
    
    vZ /= fNumCoord;
    vA /= fNumCoord;
    vDT /= fNumCoord;
    vTemp /= fNumCoord;
    vAvIonConst /= fNumCoord;
    vTV /= fNumCoord;
        
    SetZ(vZ);
    SetA(vA);
    SetA(vA);
    SetDebyeTemperature(vDT);
    SetAverageIonizationConstant(vAvIonConst);
    SetTemperature(vTemp);
    SetThermalVibrationConstant(vTV);
    
    fPeriod[0] = fCell->ComputePeriod(fMiller->GetX());
    fPeriod[1] = fCell->ComputePeriod(fMiller->GetY());
    fPeriod[2] = fCell->ComputePeriod(fMiller->GetZ());
    
    fRecPeriod[0] = fCell->ComputeRecPeriod(fMiller->GetX());
    fRecPeriod[1] = fCell->ComputeRecPeriod(fMiller->GetY());
    fRecPeriod[2] = fCell->ComputeRecPeriod(fMiller->GetZ());
    
    ComputeRadLength();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::ComputeSF(int vIndex[3]){
    std::vector<double> SF;
    std::vector<double> SF_lattice;
    
    for(unsigned int i=0;i<GetNumBases();i++){
        SF_lattice = GetLattice(i)->ComputeSF(vIndex);
        SF.push_back(SF_lattice.at(0) * GetPercentage(i));
        SF.push_back(SF_lattice.at(1) * GetPercentage(i));
    }
    return SF;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::ComputeRecFFAtDEld(int vIndex[3])
{
    std::vector<double> FC;
    std::vector<double> SF = ComputeSF(vIndex);

    double FormFactor = 0.0;
    double ThermalVibration = 0.0;
    double RecVec2 = GetCell()->ComputeRecVec2(vIndex);
    
    for(unsigned int i=0;i<GetNumBases();i++){
        FormFactor = GetAtom(i)->ComputeRecFF(RecVec2);
        ThermalVibration = exp( - fSquare(GetAtom(i)->GetThermalVibrationConstant()) * RecVec2 / 2);
        
        FC.push_back(FormFactor * SF[2*i] * GetAtom(i)->GetZ() * ThermalVibration / RecVec2);
        FC.push_back(FormFactor * SF[2*i+1] * GetAtom(i)->GetZ() * ThermalVibration / RecVec2);
    }
    return FC;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::ComputeRecFFAtD(int vIndex[3])
{
    std::vector<double> FC;
    std::vector<double> SF = ComputeSF(vIndex);
    
    double ThermalVibration = 0.0;
    double RecVec2 = GetCell()->ComputeRecVec2(vIndex);
    
    for(unsigned int i=0;i<GetNumBases();i++){
        ThermalVibration = exp( - fSquare(GetAtom(i)->GetThermalVibrationConstant()) * RecVec2 / 2);
        
        FC.push_back(SF[2*i] * ThermalVibration);
        FC.push_back(SF[2*i+1] * ThermalVibration);
    }
    return FC;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::ComputeRecFFElD(int vIndex[3])
{
    std::vector<double> FC;
    std::vector<double> SF = ComputeSF(vIndex);
    
    double FormFactor = 0.0;
    double ThermalVibration = 0.0;
    double RecVec2 = GetCell()->ComputeRecVec2(vIndex);
    
    for(unsigned int i=0;i<GetNumBases();i++){
        FormFactor = GetAtom(i)->ComputeRecFF(RecVec2);
        ThermalVibration = exp( - fSquare(GetAtom(i)->GetThermalVibrationConstant()) * RecVec2 / 2);
        
        FC.push_back((1 - FormFactor) * SF[2*i] * GetAtom(i)->GetZ() * ThermalVibration);
        FC.push_back((1 - FormFactor) * SF[2*i+1] * GetAtom(i)->GetZ() * ThermalVibration);
    }
    return FC;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::ComputeRadLength(){
    
    double InvRadLength = (4 * cFineStructureConstant * fSquare(cElectronRadius));
    double L_rad = log(184.15 * pow(GetZ(),-0.3333333333333));
    double L_rad_i = log(1194 * pow(GetZ(),-0.6666666666666));
    
    if(GetZ()==1) {L_rad=5.31; L_rad_i=6.144;}
    else if(GetZ()==2) {L_rad=4.79; L_rad_i=5.621;}
    else if(GetZ()==3) {L_rad=4.74; L_rad_i=5.805;}
    else if(GetZ()==4) {L_rad=4.71; L_rad_i=5.924;}
    
    double Z_alfa_sq = fSquare(cFineStructureConstant * GetZ());
    
    double ScreeningFunction = Z_alfa_sq * ( 1. / (1. + Z_alfa_sq) + 0.20206 - 0.0369 * Z_alfa_sq + 0.0083 * fSquare(Z_alfa_sq) - 0.002* fSquare(Z_alfa_sq) * Z_alfa_sq);
    
    InvRadLength *= (fSquare(GetZ()) * (L_rad - ScreeningFunction) +  GetZ() * L_rad_i);
    InvRadLength /= GetA();
    InvRadLength *= GetMassDensity();
    
    fRadLength = 1./InvRadLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

