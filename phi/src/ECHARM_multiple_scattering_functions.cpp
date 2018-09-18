//
//  ECHARM_multiple_scattering_functions.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_multiple_scattering_functions::ECHARM_multiple_scattering_functions()
{
    InitializePointersMultipleScatteringFunctions();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_multiple_scattering_functions::ECHARM_multiple_scattering_functions(ECHARM_crystal *Crystal,ECHARM_particle *Particle)
{
    InitializePointersMultipleScatteringFunctions();
    SetParticle(Particle);
    SetCrystal(Crystal);
    SetRadiationLength("tsai");
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_multiple_scattering_functions::~ECHARM_multiple_scattering_functions()
{
    if (&fParticle)         { delete &fParticle; }
    if (&fCrystal)         { delete &fCrystal; }
    
    if (&fCrossedMaterialLength) delete (&fCrossedMaterialLength);
    if (&fRadiationLength)         { delete &fRadiationLength; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


const ECHARM_multiple_scattering_functions& ECHARM_multiple_scattering_functions::operator=(const ECHARM_multiple_scattering_functions& right)
{
    if (this != &right)
    {
        InitializePointersMultipleScatteringFunctions();
        fCrystal = right.fCrystal;
        fParticle = right.fParticle;
        
        fCrossedMaterialLength = right.fCrossedMaterialLength;
        fRadiationLength = right.fRadiationLength;
}
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_multiple_scattering_functions::PrintMultipleScatteringProperties()
{
    std::cout << "ECHARM_multiple_scattering_functions - Print Properties" << std::endl;
    std::cout << "Radiation Length           [m]" << std::setw(12) << std::setprecision(6) << fRadiationLength << std::endl;
    std::cout << "Crossed Material Length    [m]" << std::setw(12) << std::setprecision(6) << fCrossedMaterialLength << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_multiple_scattering_functions::InitializePointersMultipleScatteringFunctions()
{
    fRadiationLength = 0.0;
    fCrystal = new ECHARM_crystal();
    fParticle = new ECHARM_particle();

    fCrossedMaterialLength = 0.001;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_multiple_scattering_functions::operator==(const ECHARM_multiple_scattering_functions& right) const
{
    return (this == (ECHARM_multiple_scattering_functions*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_multiple_scattering_functions::operator!=(const ECHARM_multiple_scattering_functions& right) const
{
    return (this != (ECHARM_multiple_scattering_functions*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_multiple_scattering_functions::SetRadiationLength(std::string Type) //!< J.D. Jackson, Classical Electrodynamics, Wiley, New York, 1975.
{
    if(Type=="jackson") fRadiationLength = EvaluateRadiationLengthJackson();
    if(Type=="tsai") fRadiationLength = EvaluateRadiationLengthTsai();    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateInverseRadiationLengthJackson() //!< J.D. Jackson, Classical Electrodynamics, Wiley, New York, 1975.
{
    double InverseRadiationLength = (4 * cFineStructureConstant);
    InverseRadiationLength *= fCrystal->GetZ() * (fCrystal->GetZ() + 1) * pow(cElectronRadius,2);
    InverseRadiationLength *= log(183 * pow(fCrystal->GetZ(),-0.3333333333333));
    InverseRadiationLength /= fCrystal->GetA();
    InverseRadiationLength *= fCrystal->GetMassDensity();
    return InverseRadiationLength;
    
    //electron mass in eV 0.510998928E6
    //electron mass in  g 9.10938291E-28

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateRadiationLengthJackson() //!< J.D. Jackson, Classical Electrodynamics, Wiley, New York, 1975.
{
    double RadiationLength = 1/EvaluateInverseRadiationLengthJackson();
    return RadiationLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateInverseRadiationLengthTsai() //!< 
{
    double InverseRadiationLength = (4 * cFineStructureConstant * pow(cElectronRadius,2));
    double L_rad = log(184.15 * pow(fCrystal->GetZ(),-0.3333333333333));
    double L_rad_i = log(1194 * pow(fCrystal->GetZ(),-0.6666666666666));
    
    if(fCrystal->GetZ()==1) {L_rad=5.31; L_rad_i=6.144;}
    else if(fCrystal->GetZ()==2) {L_rad=4.79; L_rad_i=5.621;}
    else if(fCrystal->GetZ()==3) {L_rad=4.74; L_rad_i=5.805;}
    else if(fCrystal->GetZ()==4) {L_rad=4.71; L_rad_i=5.924;}

    double Z_alfa = cFineStructureConstant*fCrystal->GetZ();
    double ScreeningFunction = pow(Z_alfa,2)*(1/(1+pow(Z_alfa,2)) + 0.20206-0.0369*pow(Z_alfa,2)+0.0083*pow(Z_alfa,4)-0.002*pow(Z_alfa,6));
    
    InverseRadiationLength *= (pow(fCrystal->GetZ(),2) * (L_rad - ScreeningFunction) +  fCrystal->GetZ() * L_rad_i);
    InverseRadiationLength /= fCrystal->GetA();
    InverseRadiationLength *= fCrystal->GetMassDensity();
    return InverseRadiationLength;
    
    //electron mass in eV 0.510998928E6
    //electron mass in  g 9.10938291E-28
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateRadiationLengthTsai() //!< 
{
    double RadiationLength = 1.0 / EvaluateInverseRadiationLengthTsai();
    return RadiationLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateMeanEnergyTransfer() //!< 
{
    double MeanEnergyTransfer = (2 * M_PI * pow(cElectronRadius,4) * pow(fabs(fParticle->GetZ()),2) * fCrystal->GetZ() * fCrystal->GetMassDensity());
    MeanEnergyTransfer /= (cElectronMass * pow(fParticle->GetBeta(),2) * fCrystal->GetA());
    MeanEnergyTransfer *= fCrossedMaterialLength;
    return MeanEnergyTransfer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateElectronMaximumKineticTransfer() //!< 
{
    double KineticTransfer = 2 * pow(cElectronMass * fParticle->GetBeta() * fParticle->GetGamma(),2);
    KineticTransfer /= (1 + 2 * fParticle->GetGamma() * cElectronMass / fParticle->GetMass() + pow(cElectronMass/fParticle->GetMass(),2));
    return KineticTransfer;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateBetheBlochLogarithmicTerm() //!< 
{
    double LogarithmicTerm = 2 * cElectronMass * pow(fParticle->GetBeta() * fParticle->GetGamma(),2);
    LogarithmicTerm *= EvaluateElectronMaximumKineticTransfer();
    LogarithmicTerm /= (pow(fCrystal->GetAverageIonizationConstant(),2));
    return (0.5 * log(LogarithmicTerm));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateBetheBlochDensityEffectTerm() //!< 
{
    double DensityTerm = 0.0;
    return DensityTerm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateBetheBlochMeanEnergyLoss() //!< 
{
    double EnergyLoss = (4 * M_PI * pow(cElectronRadius,2) * cElectronMass);
    EnergyLoss *= (pow(fabs(fParticle->GetZ()),2)*fCrystal->GetZ());
    EnergyLoss *= (EvaluateBetheBlochLogarithmicTerm() + EvaluateBetheBlochDensityEffectTerm() - pow(fParticle->GetBeta(),2));
    EnergyLoss /= (pow(fParticle->GetBeta(),2) * fCrystal->GetA());
    EnergyLoss *= fCrystal->GetMassDensity();
    EnergyLoss *= fCrossedMaterialLength;
    return EnergyLoss;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateBetheBlochScatteringAngle() //!<
{
    double ScatteringAngle = EvaluateBetheBlochMeanEnergyLoss() * fCrossedMaterialLength;
    ScatteringAngle *= cElectronMass;
    ScatteringAngle /= pow(fParticle->GetMomentum(),2);
    
    return pow(ScatteringAngle,0.5);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateMultipleScatteringAngleTaratin() //!<
{
    if(fRadiationLength==0.0) SetRadiationLength("tsai");

    double MultipleScatteringAngle = double(21.) * MeV * fabs(fParticle->GetZ()) / fParticle->GetMomentumVelocity();
    MultipleScatteringAngle *= pow(fCrossedMaterialLength/fRadiationLength,0.5);

    return MultipleScatteringAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateMultipleScatteringAngleHighland() //!< 
{
    if(fRadiationLength==0.0) SetRadiationLength("tsai");
    double LengthOverRadiationLength = fCrossedMaterialLength/fRadiationLength;
    double fY = log(LengthOverRadiationLength);

    double MultipleScatteringAngle = double(13.6) * MeV * fabs(fParticle->GetZ()) / fParticle->GetMomentumVelocity();
    MultipleScatteringAngle *= pow(LengthOverRadiationLength,0.5) * ( 1.0 + 0.038 * fY );

    return MultipleScatteringAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


double ECHARM_multiple_scattering_functions::EvaluateMultipleScatteringAngleUrban() //!< 6.28 Geant4 Physic Reference Manual
{
    if(fRadiationLength==0.0) SetRadiationLength("tsai");
    double LengthOverRadiationLength = fCrossedMaterialLength/fRadiationLength;
    
    double MultipleScatteringAngle = double(13.6) * MeV * fabs(fParticle->GetZ()) / (fParticle->GetMomentumVelocity());
    double fY = log(LengthOverRadiationLength);
    double fZ = 0.0;
    double fC1 = 0.0;
    double fC2 = 0.0;
    if(fParticle->GetMass() > ( cElectronMass * 2.0 ) )
    {
        fZ = double(1.0) - double(0.24) / (fCrystal->GetZ() * (fCrystal->GetZ() + double(1.0)));
        MultipleScatteringAngle *=  (pow(LengthOverRadiationLength,0.5) * pow(double(1.0) + double(0.105) * fY + double(0.035) * pow(fY,2.),0.5) * fZ );
    }
    else
    {
        MultipleScatteringAngle *= pow(fabs(fY),0.5);
        fC1 = double(0.885) + log(fCrystal->GetZ()) * (double(0.104) - double(0.01770) * log(fCrystal->GetZ()));
        fC2 = double(0.028) + log(fCrystal->GetZ()) * (double(0.112) - double(0.00125) * log(fCrystal->GetZ()));
        if(fY > -double(6.5)) MultipleScatteringAngle *= (fC1 + fC2 * fY);
        else MultipleScatteringAngle *= (fC1 + fC2 * fY - double(0.011) * (double(6.5) + fY));
    }
    MultipleScatteringAngle /= pow(2.0,0.5);
    return MultipleScatteringAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateMultipleScatteringAngleLynch(double fF) //!< NIMB58 6-10
{

    double fChi_c2 = double(0.157) * fCrystal->GetZ() * (fCrystal->GetZ() + double(1.0)) * pow(fabs(fParticle->GetZ()),2.);
    fChi_c2 *= (fCrossedMaterialLength * fCrystal->GetMassDensity() );
    fChi_c2 /= (pow(fParticle->GetBeta() * fParticle->GetMomentum() / MeV,2.));
    fChi_c2 /= fCrystal->GetA() / amu;
    fChi_c2 /= (gram /centimeter2);
    double fChi_alfa2 = double(2.007E-5) * pow(fCrystal->GetZ(),double(2./3.));
    fChi_alfa2 *= (double(1.0) + double(3.34) * pow(fCrystal->GetZ() * fabs(fParticle->GetZ()) * cFineStructureConstant / fParticle->GetBeta(),2.0) );
    fChi_alfa2 /= (pow(fParticle->GetMomentum() / MeV,2));
    double fOmega = fChi_c2 / fChi_alfa2;
    double fNu = double(0.5) * fOmega / (1.0 - fF);
    //std::cout << "Omega " << fOmega << std::endl;

    double MultipleScatteringAngle = fChi_c2 * ( ( (1.0 + fNu) / fNu) * log(1.0 + fNu) - 1.0);
    MultipleScatteringAngle /= (1 + pow(fF,2.));
    
    return pow(MultipleScatteringAngle,0.5); //!<  It seems to work with the square root, but it is not in the paper... to be investigated
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateSingleScatteringProbabilityBiryukov() //!< Biryukov book INTEGRATED OVER T [I,T_max]!!
{
    double EnergyLoss = EvaluateSingleScatteringEnergyVariationConstantBiryukov();
    EnergyLoss *= ( 1.0 / fCrystal->GetAverageIonizationConstant() - 1.0 / EvaluateElectronMaximumKineticTransfer());
    return EnergyLoss;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateSingleScatteringEnergyVariationConstantBiryukov() //!< Biryukov book INTEGRATED OVER T [I,T_max]!!
{
    double EnergyLoss = (4.0 * M_PI * pow(cElectronRadius,2.0) * cElectronMass);
    EnergyLoss *= (pow(fabs(fParticle->GetZ()),2.0)*fCrystal->GetZ());
    EnergyLoss /= ( 2.0 * pow(GetParticle()->GetBeta(),2.0) );
    EnergyLoss *= fCrossedMaterialLength;
    EnergyLoss *= fCrystal->GetNucleiDensity();
    return EnergyLoss;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateSingleScatteringEnergyVariationMeanBiryukov() //!< Biryukov book INTEGRATED OVER T [I,T_max]!!
{
    double EnergyLoss = EvaluateSingleScatteringEnergyVariationConstantBiryukov();
    EnergyLoss *= log(EvaluateElectronMaximumKineticTransfer()/fCrystal->GetAverageIonizationConstant());
    return EnergyLoss;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateSingleScatteringEnergyVariationVarianceBiryukov() //!< Biryukov book INTEGRATED OVER T [I,T_max]!!
{
    double EnergyLoss = EvaluateSingleScatteringEnergyVariationConstantBiryukov();
    EnergyLoss *= (EvaluateElectronMaximumKineticTransfer() - fCrystal->GetAverageIonizationConstant());
    return EnergyLoss;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateSingleScatteringEnergyVariationBiryukov() //!< Biryukov book INTEGRATED OVER T [I,T_max]!!
{
    double EnergyLoss = 0.0;
    return EnergyLoss;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateScatteringAngle(unsigned int vType, double *vParameters) //
{
    double vPar = double(0.96);
    if(vParameters == NULL) vParameters = &vPar;

    if(vType==0) return EvaluateMultipleScatteringAngleTaratin();
    else if(vType==1) return EvaluateMultipleScatteringAngleLynch(vParameters[0]);
    else if(vType==2) return EvaluateMultipleScatteringAngleUrban();
    else if(vType==3) return EvaluateMultipleScatteringAngleHighland();
    else if(vType==4) return EvaluateBetheBlochScatteringAngle();
    else if(vType==5) return EvaluateSingleScatteringEnergyVariationBiryukov();
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_multiple_scattering_functions::EvaluateScatteringTransverseEnergyVariation(unsigned int vType, double *vParameters) //
{
    double vPar = double(0.96);
    if(vParameters == NULL) vParameters = &vPar;

    if(vType==0) return EvaluateMultipleScatteringTransverseEnergyVariationTaratin();
    else if(vType==1) return EvaluateMultipleScatteringTransverseEnergyVariationLynch(*vParameters);
    else if(vType==2) return EvaluateMultipleScatteringTransverseEnergyVariationUrban();
    else if(vType==3) return EvaluateMultipleScatteringTransverseEnergyVariationHighland();
    else if(vType==4) return EvaluateBetheBlochMeanEnergyLoss();
    else if(vType==5) return EvaluateSingleScatteringEnergyVariationBiryukov();
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_multiple_scattering_functions::PrintMultipleScatteringFunctionTH1(unsigned int vType)
{
    std::string vBaseName = GetCrystal()->GetAtomName();

    TH1D *vHisto = new TH1D(vBaseName.c_str(),"Multiple Scattering Curve;Penetration Depth [mm];Deflection Angle  [#murad]",1024,0.,10.24 * centimeter);
    for(int i=1;i<vHisto->GetXaxis()->GetNbins();i++)
    {
        fCrossedMaterialLength = i * vHisto->GetXaxis()->GetXmax() / vHisto->GetXaxis()->GetNbins();
        vHisto->SetBinContent(i+1,EvaluateScatteringAngle(vType));
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef ROOT_
void ECHARM_multiple_scattering_functions::PrintMultipleScatteringDistributionTH1(ECHARM_distribution* vDistribution)
{
    std::string vBaseName = GetCrystal()->GetAtomName() + "_ms";
    
    TH1D *vHisto = new TH1D(vBaseName.c_str(),"Multiple Scattering Curve;Penetration Depth [mm];Deflection Angle  [#murad]",1024, -6. * vDistribution->GetDistributionParameters().at(1), 6. * vDistribution->GetDistributionParameters().at(1));
    for(int i=0;i<100000;i++)
    {
        vHisto->Fill(vDistribution->GenerateNumber());
    }
}
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
