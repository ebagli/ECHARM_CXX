//
//  ECHARM_crystal.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#include <cfloat>
#include <limits>

ECHARM_crystal::ECHARM_crystal()
{
    InitializePointersCrystal();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal::ECHARM_crystal(ECHARM_cell *cell, ECHARM_miller *miller, ECHARM_atom *atom, ECHARM_lattice *lattice)
{
    InitializePointersCrystal();
    SetCell(cell);
    SetMiller(miller);
    AddBase(atom,lattice);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ECHARM_crystal::~ECHARM_crystal()
{
    if (&fAtom)         { delete &fAtom; }
    if (&fLattice)         { delete &fLattice; }
    if (&fPercentage)         { delete &fPercentage; }
    if (&fMiller)         { delete &fMiller; }
    if (&fCell)         { delete &fCell; }
    if (&fAtom)         { delete &fAtom; }
    if (&fDirectPeriodPlanar) { delete &fDirectPeriodPlanar; }
    if (&fDirectPeriodAxialX) { delete &fDirectPeriodAxialX; }
    if (&fDirectPeriodAxialY) { delete &fDirectPeriodAxialY; }
    if (&fReciprocalPeriodPlanar) { delete &fReciprocalPeriodPlanar; }
    if (&fReciprocalPeriodAxialX) { delete &fReciprocalPeriodAxialX; }
    if (&fReciprocalPeriodAxialY) { delete &fReciprocalPeriodAxialY; }
    if (&fElectricFieldMaximum) { delete &fElectricFieldMaximum; }
    if (&fPotentialMaximum) { delete &fPotentialMaximum; }
    if (&fPotentialMinimum) { delete &fPotentialMinimum; }
    if (&fElectricFieldMaximumAxial) { delete &fElectricFieldMaximumAxial; }
    if (&fPotentialMaximumAxial) { delete &fPotentialMaximumAxial; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::InitializePointersCrystal()
{
    InitializePointersAtom();
    
    fAtom.clear();
    fLattice.clear();
    fPercentage.clear();

    fMiller = new ECHARM_miller();
    fCell = new ECHARM_cell();
    
    fIntegrationStepNumberPlanar = 2048;
    fIntegrationStepNumberAxialX = fIntegrationStepNumberAxialY = 32;
    
    fDirectPeriodPlanar = fDirectPeriodAxialX = fDirectPeriodAxialY = 0.0;
    fReciprocalPeriodPlanar = fReciprocalPeriodAxialX = fReciprocalPeriodAxialY = 0.0;
        
    fPotentialMaximum = DBL_MAX;
    fPotentialMinimum = DBL_MAX;
    fElectricFieldMaximum = DBL_MAX;
    
    fPotentialMaximumAxial = DBL_MAX;
    fElectricFieldMaximumAxial = DBL_MAX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_crystal::CheckCrystal()
{
    if(fCell)
    {
        if(GetCell()->CheckCell())
        {
            if(fMiller)
            {
                if(fAtom.size() > 0)
                {
                    if(fAtom.size() == fLattice.size())
                    {
                        //std::cout << "ECHARM_crystal - Crystal Check Completed" << std::endl;
                        return 1;
                    }
                    else std::cout << "ECHARM_crystal ERROR - There is a different number of atoms and lattices" << std::endl;
                }
                else std::cout << "ECHARM_crystal ERROR - There are no atoms " << std::endl;
            }
            else std::cout << "ECHARM_crystal ERROR - There are no Miller vIndexes" << std::endl;
        }
        else std::cout << "ECHARM_crystal ERROR - There is no Cell" << std::endl;
    }
    
    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom* ECHARM_crystal::GetAtom(unsigned int vIndex)
{
    if(vIndex < fAtom.size()) return fAtom[vIndex];
    else std::cout << "ECHARM_crystal ERROR - Atom "<< vIndex << " does not exist" << std::endl;
    ECHARM_atom *vAtom = new ECHARM_atom();
    return vAtom;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_lattice* ECHARM_crystal::GetLattice(unsigned int vIndex)
{
    if(vIndex < fLattice.size()) return fLattice[vIndex];
    else std::cout << "ECHARM_crystal ERROR - ERROR Lattice "<< vIndex << " does not exist" << std::endl;
    ECHARM_lattice *vLattice = new ECHARM_lattice();
    return vLattice;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

float ECHARM_crystal::GetPercentage(unsigned int vIndex)
{
    if(vIndex < fPercentage.size()) return fPercentage[vIndex];
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller* ECHARM_crystal::GetMiller()
{
    if(fMiller) return fMiller;
    else std::cout << "ECHARM_crystal ERROR - Miller does not exist" << std::endl;
    ECHARM_miller *vMiller = new ECHARM_miller();
    return vMiller;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_cell* ECHARM_crystal::GetCell()
{
    if(fCell) return fCell;
    else std::cout << "ECHARM_crystal ERROR - Cell does not exist" << std::endl;
    ECHARM_cell *vCell = new ECHARM_cell();
    return vCell;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::PrintPropertiesOfBase(unsigned int vIndex)
{
    if(vIndex < fLattice.size())
    {
        std::cout << "ECHARM_crystal - Base " << vIndex << " Properties" << std::endl;
        fAtom[vIndex]->PrintAtomProperties();
        fLattice[vIndex]->PrintLatticeCoordinates();
    }
    else std::cout << "ECHARM_crystal ERROR - Atom does not exist" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::PrintPropertiesCrystal()
{
    if(CheckCrystal())
    {
        std::cout << "ECHARM_crystal - Crystal Properties" << std::endl;
        PrintAtomProperties();
        if(fMiller) fMiller->PrintMiller();
        else std::cout << "ECHARM_crystal ERROR - Miller does not exist" << std::endl;
        if(fCell) fCell->PrintCellProperties();
        else std::cout << "ECHARM_crystal ERROR - Cell does not exist" << std::endl;
        for(unsigned int vIndex=0; vIndex < fAtom.size();vIndex++) PrintPropertiesOfBase(vIndex);
        if(fMiller && fCell) std::cout << "Interplanar Distance [A] " << std::setw(8) << fDirectPeriodPlanar*1.E10 << std::endl;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::string ECHARM_crystal::GetCharacteristicType(unsigned int vType)
{
    std::string vTypeName;
    switch (vType) {
        case 0:
            return vTypeName = "POT";
            break;
        case 1:
            return vTypeName = "ATD";
            break;
        case 2:
            return vTypeName = "ELD";
            break;
        case 3:
            return vTypeName = "EFX";
            break;
        case 4:
            return vTypeName = "EFY";
            break;
        default:
            break;
    }
    return vTypeName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::ReadPlanarElectricCharacteristicFromFile(std::string FileInName)
{
    double vTempD;
    
    std::vector<double> PotentialVector;
    PotentialVector.clear();
    
    std::ifstream FileIn;
    FileIn.open(FileInName.c_str());
    
    if(FileIn.good()) std::cout << "Opening " << FileInName << std::endl;
    if(FileIn.good()) FileIn >> fIntegrationStepNumberPlanar;
    if(FileIn.good()) FileIn >> fDirectPeriodPlanar;
    
    PotentialVector.clear();
    for(unsigned int j=0;j <fIntegrationStepNumberPlanar;j++)
        if(FileIn.good())
        {
            FileIn >> vTempD;
            PotentialVector.push_back(vTempD);
        }
    FileIn.close();
    return PotentialVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::ReadAxialElectricCharacteristicFromFile(std::string FileInName)
{
    double vTempD;
    std::vector<double> PotentialVector;
    
    PotentialVector.clear();
    
    std::ifstream FileIn;
    FileIn.open(FileInName.c_str());
    
    if(FileIn.good()) std::cout << "Opening " << FileInName << std::endl;
    if(FileIn.good()) FileIn >> fIntegrationStepNumberAxialX;
    if(FileIn.good()) FileIn >> fIntegrationStepNumberAxialY;
    if(FileIn.good()) FileIn >> fDirectPeriodAxialX;
    if(FileIn.good()) FileIn >> fDirectPeriodAxialY;
    
    for(unsigned int j=0;j<fIntegrationStepNumberAxialY;j++)
    {
        for(unsigned int i=0;i<fIntegrationStepNumberAxialX;i++)
            if(FileIn.good())
            {
                FileIn >> vTempD;
                PotentialVector.push_back(vTempD);
            }
    }
    FileIn.close();

    return PotentialVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::PrintPlanarElectricCharacteristicToFile(std::string FileOutName, std::vector<double> vVector, std::string vOptions)
{
    std::ofstream FileOut;
    FileOut.open(FileOutName.c_str());
    if(FileOut.good()) FileOut << fIntegrationStepNumberPlanar << std::endl;
    if(FileOut.good()) FileOut << fDirectPeriodPlanar << std::endl;
    double Minimum = *std::min_element(vVector.begin(),vVector.end());

    for(unsigned int i=0;i <vVector.size();i++)
        if(FileOut.good()){
            if((vOptions == "wrtdp_zero") or (vOptions=="zero")) {FileOut << vVector.at(i) - Minimum << std::endl;}
            else {FileOut << vVector.at(i) << std::endl;}
        }
    FileOut.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::PrintAxialElectricCharacteristicToFile(std::string FileOutName, std::vector<double> vVector, std::string vOptions)
{
    std::ofstream FileOut;
    FileOut.open(FileOutName.c_str());
    if(FileOut.good()) FileOut << fIntegrationStepNumberAxialX << std::endl;
    if(FileOut.good()) FileOut << fIntegrationStepNumberAxialY << std::endl;
    if(FileOut.good()) FileOut << fDirectPeriodAxialX << std::endl;
    if(FileOut.good()) FileOut << fDirectPeriodAxialY << std::endl;
    double Minimum = *std::min_element(vVector.begin(),vVector.end());

    for(unsigned int j=0;j < fIntegrationStepNumberAxialY;j++)
        for(unsigned int i=0;i < fIntegrationStepNumberAxialX;i++)
            if(FileOut.good()){
                if((vOptions == "wrtdp_zero") or (vOptions=="zero")) {FileOut << vVector.at(ComputeAxialVectorIndex(i,j,fIntegrationStepNumberAxialX)) << std::endl;}
                else {FileOut << vVector.at(ComputeAxialVectorIndex(i,j,fIntegrationStepNumberAxialX)) - Minimum << std::endl;}
            }
    
    FileOut.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_crystal::PrintPlanarElectricCharacteristicToTH1(std::string vName, std::vector<double> vVector, std::string vOptions)
{
    double vAxisXmax = fDirectPeriodPlanar/AA;
    std::string vAxisName = vName + ";Horizontal Impact Position [#AA];Electric Characteristic";

    if((vOptions == "wrtdp_zero") or (vOptions=="wrtdp")) //wrtdp == with respect to interplanar distance
    {
        vAxisXmax = 1.;
        vAxisName.clear();
        vAxisName = vName + ";Horizontal Impact Parameter [x/d_{p}];Electric Characteristic";
    }
    double Minimum = *std::min_element(vVector.begin(),vVector.end());
    TH1D *vHisto = new TH1D(vName.c_str(),vAxisName.c_str(),vVector.size(),0.0,vAxisXmax);
    for(unsigned int i=0;i <vVector.size();i++)
    {
        if((vOptions == "wrtdp_zero") or (vOptions=="zero")) vHisto->SetBinContent(i+1,vVector.at(i)-Minimum);
        else vHisto->SetBinContent(i+1,vVector.at(i));
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_crystal::PrintAxialElectricCharacteristicToTH2(std::string vName, std::vector<double> vVector, std::string vOptions)
{
    double vAxisXmax = fDirectPeriodAxialX;
    double vAxisYmax = fDirectPeriodAxialY;
    std::string vAxisName = vName + ";Horizontal Impact Position [#mum];Vertical Impact Position [#mum];Electric Characteristic";

    if(vOptions == "wrtdp") //wrtdp == with respect to interplanar distance
    {
        vAxisXmax = 1.;
        vAxisYmax = 1;
        vAxisName.clear();
        vAxisName = vName + ";Horizontal Impact Parameter [x/d_{px}];Vertical Impact Paramter [y/d_{py}];Electric Characteristic";
    }
    
    TH2D *vHisto = new TH2D(vName.c_str(),vAxisName.c_str(),fIntegrationStepNumberAxialX,0.0,vAxisXmax,fIntegrationStepNumberAxialY,0.0,vAxisYmax);
    for(unsigned int j=0;j<fIntegrationStepNumberAxialY;j++)
        for(unsigned int i=0;i <fIntegrationStepNumberAxialX;i++)
            vHisto->SetBinContent(i+1,j+1,vVector.at(ComputeAxialVectorIndex(i,j,fIntegrationStepNumberAxialX)));
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::AddBase(ECHARM_atom *atom,ECHARM_lattice *lattice, float percentage)
{
    fAtom.push_back(atom);
    fLattice.push_back(lattice);
    fPercentage.push_back(percentage);
    ComputeCrystalAverageParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::SetBase(unsigned int vIndex,ECHARM_atom *atom,ECHARM_lattice *lattice,float percentage)
{
    if(vIndex < fLattice.size())
    {
        fAtom[vIndex] = atom;
        fLattice[vIndex] = lattice;
        fPercentage[vIndex] = percentage;
    }
    else std::cout << "ECHARM_crystal ERROR - Base does not exist" << std::endl;
    ComputeCrystalAverageParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::SetAtom(unsigned int vIndex,ECHARM_atom *atom)
{
    if(vIndex < fAtom.size())
    {
        fAtom[vIndex] = atom;
    }
    else std::cout << "ECHARM_crystal ERROR - Base does not exist" << std::endl;
    ComputeCrystalAverageParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::SetLattice(unsigned int vIndex,ECHARM_lattice *lattice)
{
    if(vIndex < fLattice.size())
    {
        fLattice[vIndex] = lattice;
    }
    else std::cout << "ECHARM_crystal ERROR - Base does not exist" << std::endl;
    ComputeCrystalAverageParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::SetPercentage(unsigned int vIndex,float percentage)
{
    if(vIndex < fPercentage.size())
    {
        fPercentage[vIndex] = percentage;
    }
    ComputeCrystalAverageParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::SetMiller(ECHARM_miller *miller)
{
    fMiller = miller;
    ComputeCrystalAverageParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void ECHARM_crystal::SetCell(ECHARM_cell *cell)
{
    fCell = cell;
    ComputeCrystalAverageParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_crystal& ECHARM_crystal::operator=(const ECHARM_crystal& right)
{
    if (this != &right)
    {        
        fAtom = right.fAtom;
        fLattice = right.fLattice;
        fPercentage = right.fPercentage;
        fCell = right.fCell;
        fMiller = right.fMiller;
     
        ComputeCrystalAverageParameters();

        fDirectPeriodPlanar = right.fDirectPeriodPlanar;
        fDirectPeriodAxialX = right.fDirectPeriodAxialX;
        fDirectPeriodAxialY = right.fDirectPeriodAxialY;
        
        fReciprocalPeriodPlanar = right.fReciprocalPeriodPlanar;
        fReciprocalPeriodAxialX = right.fReciprocalPeriodAxialX;
        fReciprocalPeriodAxialY = right.fReciprocalPeriodAxialY;
        
        fElectricFieldMaximum = right.fElectricFieldMaximum;
        fPotentialMaximum = right.fPotentialMaximum;

        fElectricFieldMaximumAxial = right.fElectricFieldMaximumAxial;
        fPotentialMaximumAxial = right.fPotentialMaximumAxial;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal::operator==(const ECHARM_crystal& right) const
{
    return (this == (ECHARM_crystal*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal::operator!=(const ECHARM_crystal& right) const
{
    return (this != (ECHARM_crystal*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal::GetPotentialDifference(double vFirstPoint,double vSecondPoint)
{
    double vPotentialDifference = GetPlanarElectricCharacteristic( vFirstPoint,0) - GetPlanarElectricCharacteristic( vSecondPoint,0);
    return vPotentialDifference;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal::GetPotentialDifferenceAxial(double vFirstPointX,double vFirstPointY,double vSecondPointX,double vSecondPointY)
{
    double vPotentialDifference = GetAxialElectricCharacteristic( vFirstPointX,vFirstPointY,0) - GetAxialElectricCharacteristic( vSecondPointX,vSecondPointY,0);
    return vPotentialDifference;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal::ComputeCrystalAverageParameters()
{
    double fZ_temp = 0.0;
    double fA_temp = 0.0;
    double fAverageIonizationConstant_temp = 0.0;
    double fThermalVibrationConstant_temp = 0.0;
    double fDebyeTemperature_temp = 0.0;
    double fTemperature_temp = 0.0;
    
    int NumberOfAtomsTotal = 0;
    
    bool bChangeAtomName = false;
    if(GetAtomName()=="") bChangeAtomName = true;
    
    for(unsigned int i=0;i<GetNumberOfBases();i++)
    {
        NumberOfAtomsTotal += GetLattice(i)->GetNumberOfCoordinates() * GetPercentage(i);
        fZ_temp += GetAtom(i)->GetZ() * GetLattice(i)->GetNumberOfCoordinates() * GetPercentage(i);
        fA_temp += GetAtom(i)->GetA() * GetLattice(i)->GetNumberOfCoordinates() * GetPercentage(i);
        fDebyeTemperature_temp += GetAtom(i)->GetDebyeTemperature() * GetLattice(i)->GetNumberOfCoordinates() * GetPercentage(i);
        fTemperature_temp += GetAtom(i)->GetTemperature() * GetLattice(i)->GetNumberOfCoordinates() * GetPercentage(i);
        fAverageIonizationConstant_temp += GetAtom(i)->GetAverageIonizationConstant() * GetLattice(i)->GetNumberOfCoordinates() * GetPercentage(i);
        fThermalVibrationConstant_temp += GetAtom(i)->GetThermalVibrationConstant() * GetLattice(i)->GetNumberOfCoordinates() * GetPercentage(i);
        if(bChangeAtomName) SetAtomName(GetAtomName() + GetAtom(i)->GetAtomName());
    }
    
    fZ_temp /= NumberOfAtomsTotal;
    fA_temp /= NumberOfAtomsTotal;
    fDebyeTemperature_temp /= NumberOfAtomsTotal;
    fTemperature_temp /= NumberOfAtomsTotal;
    fAverageIonizationConstant_temp /= NumberOfAtomsTotal;
    fThermalVibrationConstant_temp /= NumberOfAtomsTotal;
    fNumberOfCoordinatesTotal = NumberOfAtomsTotal;
    
    SetZ(fZ_temp);
    SetA(fA_temp);
    SetDebyeTemperature(fDebyeTemperature_temp);
    SetTemperature(fTemperature_temp);
    SetAverageIonizationConstant(fAverageIonizationConstant_temp);
    SetThermalVibrationConstant(fThermalVibrationConstant_temp);
    
    int Indexes[3];
    for(unsigned int i=0;i<3;i++) Indexes[i] = GetMiller()->GetMillerPlanar(i);
    fDirectPeriodPlanar = GetCell()->FindPeriodDirect(Indexes);
    fReciprocalPeriodPlanar = GetCell()->FindPeriodReciprocal(Indexes);
    for(unsigned int i=0;i<3;i++) Indexes[i] = GetMiller()->GetMillerAxial(1,i);
    fDirectPeriodAxialX =  GetCell()->FindPeriodDirect(Indexes);
    fReciprocalPeriodAxialX =  GetCell()->FindPeriodReciprocal(Indexes);
    for(unsigned int i=0;i<3;i++) Indexes[i] = GetMiller()->GetMillerAxial(2,i);
    fDirectPeriodAxialY =  GetCell()->FindPeriodDirect(Indexes);
    fReciprocalPeriodAxialY =  GetCell()->FindPeriodReciprocal(Indexes);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::FindStructureFactorCoefficient(int vIndex[3])
{
    std::vector<double> SFtemp;
    std::vector<double> SFtemp_lattice;
    
    for(unsigned int i=0;i<GetNumberOfBases();i++)
    {
        SFtemp_lattice = GetLattice(i)->FindStructureFactor(vIndex);
        SFtemp.push_back(SFtemp_lattice.at(0) * GetPercentage(i));
        SFtemp.push_back(SFtemp_lattice.at(1) * GetPercentage(i));
    }
    return SFtemp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::FindStructureFactorCoefficient(int vIndex00,int vIndex01,int vIndex02)
{
    int vIndex[3];
    vIndex[0]=vIndex00;
    vIndex[1]=vIndex01;
    vIndex[2]=vIndex02;
    std::vector<double> SFtemp = FindStructureFactorCoefficient(vIndex);
    return SFtemp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal::GetValueInPeriodicUnit(double vX, double &vPeriod)
{
    if (vX < 0.0) vX += (fabs(int( vX / vPeriod ) ) + 1.0 ) * vPeriod;
    else if ( vX > vPeriod ) vX -= fabs( int( vX / vPeriod ) * vPeriod );
    return vX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal::ComputeAxialVectorIndex(int i,int j, int vTermNumberX, int vTermNumberX0, int vTermNumberY0)
{
    int vIndex = 0;
    vIndex = (i - vTermNumberX0) + vTermNumberX * (j - vTermNumberY0);
    return vIndex;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::NormalizeElectricCharacteristic(std::vector<double> vVector)
{
    std::vector<double> vVectorReturn;
    vVectorReturn.clear();
    double vSum = 0.0;
    double vElCh = 0.0;
    for(unsigned int i=0;i<vVector.size();i++) {vSum += vVector.at(i);}
    for(unsigned int i=0;i<vVector.size();i++)
    {
        vElCh = vVector.at(i) / (vSum * vVector.size());
        vVectorReturn.push_back(vElCh);
    }
    return vVectorReturn;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::FindPlanarElectricCharacteristic(unsigned int vType, std::string vOptions)
{
    std::vector<double> vVector;
    vVector.clear();
    if(!CheckCrystal()) return vVector;
    
    double Step = GetStepPlanar();
    double x[fIntegrationStepNumberPlanar];
    for(unsigned int i=0;i<fIntegrationStepNumberPlanar;i++) x[i] = i * Step;
    
#ifndef OPENMP_
    for(unsigned int i=0;i<fIntegrationStepNumberPlanar;i++) vVector.push_back(GetPlanarElectricCharacteristic(x[i],vType));
#endif
    
#ifdef OPENMP_
    int fIntegrationStepNumberPlanarInt = int(fIntegrationStepNumberPlanar);
    double vArray[fIntegrationStepNumberPlanar];
#pragma omp parallel for
    for(int i=0;i<fIntegrationStepNumberPlanarInt;i++)
    {
        vArray[i] = GetPlanarElectricCharacteristic(x[i],vType);
    }
    for(unsigned int i=0;i<fIntegrationStepNumberPlanar;i++) vVector.push_back(vArray[i]);
#endif
    
    double Minimum = *std::min_element(vVector.begin(),vVector.end());
    double Maximum = *std::max_element(vVector.begin(),vVector.end());
    
    std::cout << "Min val is " << std::setw(10) << Minimum << " ---------- " << " Max val is " << std::setw(10) << Maximum << std::endl;
    if(vType == 0) SetPotentialMaximum(Maximum - Minimum);
    if(vType == 3) SetElectricFieldMaximum(Maximum);
    
#ifdef ROOT_
    std::string vHistoName = GetAtomName() + GetMiller()->GetMillerTextPlanar() + "pl" + GetCharacteristicType(vType);
    PrintPlanarElectricCharacteristicToTH1(vHistoName,vVector,vOptions);
#endif
    
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal::FindAxialElectricCharacteristic(unsigned int vType, std::string vOptions)
{
    std::vector<double> vVector;
    vVector.clear();
    
    if(!CheckCrystal()) return vVector;
    
    double StepX = GetStepAxialX();
    double StepY = GetStepAxialY();
    
    double x = 0.0;
    double y = 0.0;
        
    std::cout << "ECHARM_crystal - Calculate " << vType << " for " << GetAtomName() << " " << GetMiller()->GetMillerTextAxial() << " axis" << std::endl;
    
#ifndef OPENMP_
    for(unsigned int j=0;j<fIntegrationStepNumberAxialY;j++)
    {
        y = j * StepY;
        for(unsigned int i=0;i<fIntegrationStepNumberAxialX;i++)
        {
            x = i * StepX;
            vVector.push_back(GetAxialElectricCharacteristic(x,y,vType));
        }
        //std::cout << std::setw(4) << j+1 << " of " << std::setw(4) << fIntegrationStepNumberAxialY << std::endl;
    }
#endif
    
#ifdef OPENMP_
    double vArray[fIntegrationStepNumberAxialX*fIntegrationStepNumberAxialY];
    int fIntegrationStepNumberAxialXInt = int(fIntegrationStepNumberAxialX);
    for(unsigned int j=0;j<fIntegrationStepNumberAxialY;j++)
    {
        y = j * StepY;
#pragma omp parallel for private(x)
        for(int i=0;i<fIntegrationStepNumberAxialXInt;i++)
        {
            x = i * StepX;
            vArray[i] = GetAxialElectricCharacteristic(x,y,vType);
        }
        
        for(unsigned int i=0;i<fIntegrationStepNumberAxialX;i++) vVector.push_back(vArray[i]);
        //std::cout << std::setw(4) << j+1 << " of " << std::setw(4) << fIntegrationStepNumberAxialY << std::endl;
    }
#endif
    
    std::cout << " Min val is " << std::setw(10) << *std::min_element(vVector.begin(),vVector.end());
    std::cout << " ---------- ";
    std::cout << " Max val is " << std::setw(10) << *std::max_element(vVector.begin(),vVector.end()) << std::endl;
    std::cout << " --------------------------------------------- " << std::endl;
    
#ifdef ROOT_
    std::string vHistoName = GetAtomName() + GetMiller()->GetMillerTextAxial() + "ax" + GetCharacteristicType(vType);
    PrintAxialElectricCharacteristicToTH2(vHistoName,vVector,vOptions);
#endif
    
    
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......