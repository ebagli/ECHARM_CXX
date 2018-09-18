//
//  ECHARM_atom.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_atom::ECHARM_atom()
{
    InitializePointersAtom();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom::ECHARM_atom(std::string  AtomName,
                         double Z,
                         double A,
                         double DebyeTemperature,
                         double Temperature,
                         double AverageIonizationConstant,
                         unsigned int FormFactorType,
                         std::vector<double> ExperimentalFormFactorParameters
                         )
{
    if(Z < 0.) 
    {
        std::cout << "ECHARM_atom ERROR - Z < 1 is not allowed" << std::endl;
    }
    InitializePointersAtom();
    fAtomName = AtomName;
    fZ = Z;
    fA = A;
    fDebyeTemperature = DebyeTemperature;
    fTemperature = Temperature;
    fAverageIonizationConstant = AverageIonizationConstant;
    fFormFactorType = FormFactorType;
    fExperimentalFormFactorParameters = ExperimentalFormFactorParameters;
    ComputeThermalVibration();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom::ECHARM_atom(std::string File_Atom)
{
    InitializePointersAtom();
    
    std::ifstream File_Atom_In;
    
    File_Atom_In.open(File_Atom.c_str());
    if(File_Atom_In)
    {
        if(File_Atom_In.good()) File_Atom_In >> fAtomName;
        if(File_Atom_In.good()) File_Atom_In >> fZ;
        if(File_Atom_In.good()) File_Atom_In >> fA;
        fA *= amu;
        if(File_Atom_In.good()) File_Atom_In >> fDebyeTemperature;
        if(File_Atom_In.good()) File_Atom_In >> fTemperature;
        if(File_Atom_In.good()) File_Atom_In >> fAverageIonizationConstant;
        if(File_Atom_In.good()) File_Atom_In >> fFormFactorType;
                
        if(fFormFactorType==2)
        {
            fExperimentalFormFactorParameters.reserve(12);
            for(int i=0;i<12;i++)
                if(File_Atom_In.good()) File_Atom_In >> fExperimentalFormFactorParameters.at(i);
        }
        else
        {
            fExperimentalFormFactorParameters.clear();
            fExperimentalFormFactorParameters.reserve(0);                
        }
    }
    else std::cout << "ECHARM_atom ERROR - file does not exist" << std::endl;
    File_Atom_In.close();
        
    ComputeThermalVibration();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom::~ECHARM_atom()
{
    if (&fThermalVibrationConstant)         { delete &fThermalVibrationConstant; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


const ECHARM_atom& ECHARM_atom::operator=(const ECHARM_atom& right)
{
    if (this != &right)
    {
        InitializePointersAtom();
        fAtomName = right.fAtomName;
        fZ = right.fZ;
        fA = right.fA;
        fDebyeTemperature = right.fDebyeTemperature;
        fTemperature = right.fTemperature;
        fAverageIonizationConstant = right.fAverageIonizationConstant;
        fFormFactorType = right.fFormFactorType;
        fExperimentalFormFactorParameters = right.fExperimentalFormFactorParameters;
        ComputeThermalVibration();
        if(fThermalVibrationConstant!=right.fThermalVibrationConstant) fThermalVibrationConstant = right.fThermalVibrationConstant;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_atom::PrintAtomProperties()
{
    std::cout << "ECHARM_atom - Print " << fAtomName << " Properties" << std::endl;
    std::cout << "AtomName                       " << std::setw(10) << fAtomName << std::endl; 
    std::cout << "A                              " << std::setw(10) << fA << std::endl;  
    std::cout << "Z                              " << std::setw(10) << fZ << std::endl;  
    std::cout << "Debye Temperature           [K]" << std::setw(10) << fDebyeTemperature << std::endl;  
    std::cout << "Ionization Constant        [eV]" << std::setw(10) << fAverageIonizationConstant << std::endl;  
    std::cout << "Form Factor Type               " << std::setw(10) << fFormFactorType << std::endl;  
    std::cout << "Thermal Vibration Amplitude [A]" << std::setw(10) << std::setprecision(3) << fThermalVibrationConstant*1.E10 << std::endl;
    if(fFormFactorType == 2)
        for(unsigned int i=0;i<12;i++)
        {
            std::cout << "Coefficient                    " << std::setw(10) << std::setprecision(3) << fExperimentalFormFactorParameters.at(i) << std::endl;
        }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_atom::InitializePointersAtom()
{
    fZ = 0.0;
    fA = 0.0;
    fDebyeTemperature = 0.0;
    fAverageIonizationConstant = 0.0;
    fFormFactorType = 1;
    fExperimentalFormFactorParameters.clear();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_atom::operator==(const ECHARM_atom& right) const
{
    return (this == (ECHARM_atom*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_atom::operator!=(const ECHARM_atom& right) const
{
    return (this != (ECHARM_atom*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_atom::ComputeThermalVibration()
{
    double Constant = ( (3 * pow(cPlanckConstant,2)) / (4 * cBoltzmanConstant * GetA() * GetDebyeTemperature()));
    double Integral = 0.0;
    
    int i;
    int IntegrationStepNumber = 8192;
    double y_var_0 = GetDebyeTemperature() / GetTemperature() / IntegrationStepNumber;
    double y_var = 0.0;
    double y_value = 0.0;
    for(i=1;i<IntegrationStepNumber;i++)
    {
        y_var = i * y_var_0;
        y_value = ( y_var / (exp(y_var) - 1)); 
        Integral += (y_value * y_var_0 );
    }
    
    fThermalVibrationConstant = pow( Constant * ( 1 + 4 * Integral * pow(GetTemperature()/GetDebyeTemperature(),2)) , 0.5);
    if(fDebyeTemperature==0.0) fThermalVibrationConstant = 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindThomasFermiRadius()
{
    double BohrRadius = 0.529177E-10;
    double ThomasFermiRadius = BohrRadius * 0.8853 / pow (GetZ() , 0.333333333);
    return ThomasFermiRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorReciprocalSimple(double VectorSquaredReciprocal)
{
    double vResult = 0.0;

    vResult = 1 / (1+ VectorSquaredReciprocal * pow(FindThomasFermiRadius(),2));
    
    vResult = 1.0 - vResult;

    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorReciprocalMoliere(double VectorSquaredReciprocal)
{
    double vResult = 0.0;

    double MoliereCoefficientsAlfa[3] = {0.1,0.55,0.35};
    double MoliereCoefficientsBeta[3] = {6.0,1.2,0.3};

    for(unsigned int i=0;i<3;i++)
        vResult += (MoliereCoefficientsAlfa[i] / (1. + VectorSquaredReciprocal / pow(MoliereCoefficientsBeta[i] / FindThomasFermiRadius(),2.)));
    
    vResult = 1.0 - vResult;

    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorReciprocalExperimental(double VectorSquaredReciprocal)
{
    double vResult = 0.0;
    
    for(unsigned int i=0;i<6;i++)
    {
        vResult += (fExperimentalFormFactorParameters.at(i) * exp(- VectorSquaredReciprocal * fExperimentalFormFactorParameters.at(i+6) / 16. / pow(M_PI,2.)) );
    }
    
    vResult = 1.0 - vResult;
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorReciprocalLindhard(double VectorSquaredReciprocal)
{
    double vResult = 0.0;
    
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorReciprocal(double VectorSquaredReciprocal)
{    
    if(fFormFactorType == 0) return FindFormFactorReciprocalSimple(VectorSquaredReciprocal);
    else if(fFormFactorType == 1) return FindFormFactorReciprocalMoliere(VectorSquaredReciprocal);
    else if(fFormFactorType == 2) return FindFormFactorReciprocalExperimental(VectorSquaredReciprocal);
    else if(fFormFactorType == 3) return FindFormFactorReciprocalLindhard(VectorSquaredReciprocal);
    else return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorDirectMoliere(double DirectVector)
{
    
    double vResult = 0.0;
    double MoliereCoefficientsAlfa[3] = {0.1,0.55,0.35};
    double MoliereCoefficientsBeta[3] = {6.0,1.2,0.3};
    
    for(unsigned int i=0;i<3;i++)
        vResult += (MoliereCoefficientsAlfa[i] / MoliereCoefficientsBeta[i] * exp( - MoliereCoefficientsBeta[i] * fabs(DirectVector)/FindThomasFermiRadius() ) );
    
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorDirectMoliereDerivate(double DirectVector)
{
    
    double vResult = 0.0;
    double MoliereCoefficientsAlfa[3] = {0.1,0.55,0.35};
    double MoliereCoefficientsBeta[3] = {6.0,1.2,0.3};
    
    for(unsigned int i=0;i<3;i++)
        vResult -= (MoliereCoefficientsAlfa[i] * exp( - MoliereCoefficientsBeta[i] * fabs(DirectVector) / FindThomasFermiRadius() ) / FindThomasFermiRadius());
    
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorDirectMoliereAveragedOverTemperature(double vX)
{
    double vTF = FindThomasFermiRadius();
    double vResult = 0.0;
    double vTemp = 0.0;
    double vAlfa[3] = {0.1,0.55,0.35};
    double vBeta[3] = {6.0,1.2,0.3};
    double vGamma[3];
    double vTau[3];
    
    for(unsigned int i=0;i<3;i++) vGamma[i] = vAlfa[i]/vBeta[i];
    for(unsigned int i=0;i<3;i++) vTau[i] = (pow(fThermalVibrationConstant / vTF * vBeta[i],2) / 2.0);

    for(unsigned int i=0;i<3;i++)
    {
        vTemp = 0.0;
        vTemp += ( exp(-vX / vTF * vBeta[i] ) * erfc((fThermalVibrationConstant / vTF * vBeta[i] - vX / fThermalVibrationConstant) / pow(2.,0.5)) );
        vTemp += ( exp( vX / vTF * vBeta[i] ) * erfc((fThermalVibrationConstant / vTF * vBeta[i] + vX / fThermalVibrationConstant) / pow(2.,0.5)) );
        vResult += ( vTemp * vGamma[i] * exp( vTau[i] ) /2.0);
    }
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorDirectSimple(double DirectVector)
{
    double vResult = 0.0;
    vResult = exp( - DirectVector / FindThomasFermiRadius() );
    return vResult ;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorDirectSimpleDerivate(double DirectVector)
{
    double vResult = 0.0;
    vResult = - exp( - DirectVector / FindThomasFermiRadius() ) / FindThomasFermiRadius();
    return vResult ;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorDirectLindhard(double DirectVector)
{
    double vResult = 0.0;
    double vConstant = pow(3,0.5) * FindThomasFermiRadius() ;
    vResult = pow(pow(DirectVector,2) +  pow(vConstant,2.),0.5);
    vResult -= DirectVector;
    vResult /= vConstant;
    return vResult ;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorDirectLindhardDerivate(double DirectVector)
{
    double vResult = 0.0;
    double vConstant = pow(3,0.5) * FindThomasFermiRadius() ;
    vResult = ( - 1.0 + DirectVector / pow(pow(DirectVector,2.) +  pow(vConstant,2.),0.5) );
    vResult /= vConstant;
    return vResult ;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorDirectExperimental(double DirectVector)
{
    double vResult = 0.0;

    for(unsigned int i=0;i<4;i++)
    {
        vResult += (GetExperimentalFormFactorParameter(i));
        vResult /= (1. + DirectVector / GetExperimentalFormFactorParameter(i+4) / FindThomasFermiRadius());
    }
    vResult +=  GetExperimentalFormFactorParameter(8);
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom::FindFormFactorDirect(double VectorSquaredDirect)
{
    double DirectVector = pow(VectorSquaredDirect,0.5);
    if(fFormFactorType == 0) return FindFormFactorDirectSimple(DirectVector);
    else if(fFormFactorType == 1) return FindFormFactorDirectMoliere(DirectVector);
    else if(fFormFactorType == 2) return FindFormFactorDirectExperimental(DirectVector);
    else if(fFormFactorType == 3) return FindFormFactorDirectLindhard(DirectVector);
    else return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
