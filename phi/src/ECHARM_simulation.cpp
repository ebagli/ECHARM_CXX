//
//  ECHARM_simulation.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


ECHARM_simulation::ECHARM_simulation()
{
    InitializePointersChanneling();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_simulation::~ECHARM_simulation()
{
    if(&fStrip) delete (&fStrip);
    if(&fParticle) delete (&fParticle);
    if(&fMaximumPotential) delete (&fMaximumPotential);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation::InitializePointersChanneling()
{
    fStrip = new ECHARM_strip();
    fParticle = new ECHARM_particle();
    fMaximumPotential = DBL_MAX;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_simulation::operator==(const ECHARM_simulation& right) const
{
    return (this == (ECHARM_simulation*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_simulation::operator!=(const ECHARM_simulation& right) const
{
    return (this != (ECHARM_simulation*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_simulation& ECHARM_simulation::operator=(const ECHARM_simulation& right)
{
    if (this != &right)
    {
        InitializePointersChanneling();
        fStrip=right.fStrip;
        fParticle=right.fParticle;
        fMaximumPotential = right.fMaximumPotential;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation::PrintChannelingProperties(std::vector<double> vVector)
{
    std::cout << "ECHARM_simulation - Print Channneling Properties" << std::endl;
    std::cout << "Critical Potential         [eV]" << std::setw(10) << EvaluateCriticalPotential(vVector) << std::endl;
    std::cout << "Critical Radius             [m]" << std::setw(10) << EvaluateCriticalRadius(vVector) << std::endl;
    std::cout << "Critical Angle           [µrad]" << std::setw(10) << EvaluateCriticalAngle(vVector) * 1.E6 << std::endl;
    std::cout << "Lindhard Angle           [µrad]" << std::setw(10) << EvaluateLindhardAngle(vVector) * 1.E6 << std::endl;
    std::cout << "Oscillation Period         [µm]" << std::setw(10) << EvaluateOscillationPeriod(vVector) * 1.E6 << std::endl;
    std::cout << "Geometric Efficiency        [%]" << std::setw(10) << EvaluateGeometricEfficiency(vVector) * 1.E2 << std::endl;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::GetTransverseEnergyPlanar()
{
    double vEnergy = fabs(fParticle->GetMomentumVelocity() * 0.5 );
    vEnergy *= ( pow(fParticle->GetMomentumVector()->GetX() / fParticle->GetMomentumVector()->GetZ(),2.0) );
    vEnergy += fStrip->GetCrystal()->GetPlanarElectricCharacteristic(fParticle->GetPositionVector()->GetX(),0);
    return vEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::GetTransverseEnergyToDechannel()
{
    double vTempEnergy;
    
    vTempEnergy = GetStrip()->GetCrystal()->GetPlanarElectricCharacteristic( GetParticle()->GetPositionVector()->GetX() , 0);
    if( StripIsBentX() ) vTempEnergy += ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta()  * GetParticle()->GetPositionVector()->GetX() / GetStrip()->GetCurvatureRadius()->GetX() );
    vTempEnergy += ( 0.5 * pow(GetParticle()->GetMomentumVector()->GetX(),2.) / ( GetParticle()->GetBeta() * GetParticle()->GetMomentumVector()->GetZ() ) );
    vTempEnergy -= GetStrip()->GetCrystal()->GetPlanarElectricCharacteristic(0.0,0);
    
    if(vTempEnergy > 0.0) vTempEnergy = -0.;
    vTempEnergy *= (-1.);
    return vTempEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateEffectiveInterplanarDistance(std::vector<double> vVector)
{
    double vInterplanar = EvaluatePotentialWellCentre(vVector) * 2.0;
    return vInterplanar;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateMaximumPotential(std::vector<double> vVector)
{
    if(fMaximumPotential==DBL_MAX){
        fMaximumPotential = fStrip->GetCrystal()->GetPotentialDifference(0.0,EvaluatePotentialWellCentre());
    }
    return fMaximumPotential;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateCriticalRadius(std::vector<double> vVector)
{
    double vCriticalRadius = fabs(fParticle->GetMomentumVector()->GetZ() / fStrip->GetCrystal()->GetElectricFieldCritical());
    return vCriticalRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateCriticalPotential(std::vector<double> vVector)
{
    double vPotentialCritical = fStrip->GetCrystal()->GetPotentialDifference(2.5 * fStrip->GetCrystal()->GetThermalVibrationConstant(),EvaluatePotentialWellCentre(vVector));
    if( vVector != std::vector<double>() )
    {
        int vIndex = int(float((fStrip->GetCrystal()->GetDirectPeriodPlanar() - fStrip->GetCrystal()->GetThermalVibrationConstant() * 2.5)/fStrip->GetCrystal()->GetDirectPeriodPlanar() * vVector.size()));
        vPotentialCritical = vVector.at(vIndex);
    }
    return vPotentialCritical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateCriticalAngle(std::vector<double> vVector)
{
    double vCriticalAngle = pow( 2.0 * fabs( EvaluateCriticalPotential(vVector) / fParticle->GetMomentumVelocity()  ) , 0.5);
    return vCriticalAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateCriticalMomentum(std::vector<double> vVector)
{
    double vCriticalMomentum = EvaluateCriticalAngle(vVector) * fParticle->GetMomentumVector()->GetZ();;
    return vCriticalMomentum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateLindhardAngle(std::vector<double> vVector)
{
    double vLindhardAngle = pow( 2.0 * fabs( EvaluateMaximumPotential(vVector) / fParticle->GetMomentumVelocity() ) , 0.5);
    return vLindhardAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateCriticalRadiusAxial(std::vector<double> vVector)
{
    double vCriticalRadius = fabs(fParticle->GetMomentumVector()->GetZ() / fStrip->GetCrystal()->GetElectricFieldMaximumAxial());
    return vCriticalRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateCriticalPotentialAxial(std::vector<double> vVector)
{
    double vPotentialCritical = fStrip->GetCrystal()->GetPotentialDifferenceAxial(0.0,0.0,2.5 * fStrip->GetCrystal()->GetThermalVibrationConstant(),2.5 * fStrip->GetCrystal()->GetThermalVibrationConstant());
    return vPotentialCritical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateCriticalAngleAxial(std::vector<double> vVector)
{
    double vCriticalAngle = pow( 2.0 * fabs( EvaluateCriticalPotentialAxial(vVector) / fParticle->GetMomentumVelocity()  ) , 0.5);
    return vCriticalAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateCriticalMomentumAxial(std::vector<double> vVector)
{
    double vCriticalMomentum = EvaluateCriticalAngleAxial(vVector) * fParticle->GetMomentumVector()->GetZ();;
    return vCriticalMomentum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateLindhardAngleAxial(std::vector<double> vVector)
{
    double vLindhardAngle = pow( 2.0 * fabs( fStrip->GetCrystal()->GetPotentialMaximumAxial() / fParticle->GetMomentumVelocity() ) , 0.5);
    return vLindhardAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateOscillationPeriod(std::vector<double> vVector)
{
    double vOscillationPeriod = M_PI * fStrip->GetCrystal()->GetDirectPeriodPlanar() / EvaluateLindhardAngle(vVector);
    return vOscillationPeriod;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateGeometricEfficiency(std::vector<double> vVector)
{
    double vGeometricEfficiency = 1.0 - 2.0 * fabs(fStrip->GetCrystal()->GetThermalVibrationConstant() * 2.5 / EvaluateEffectiveInterplanarDistance(vVector) );
//    if(StripIsBentX())
//    {
//        if(fStrip->GetCurvatureRadius()->GetX() > EvaluateCriticalRadius())
//            vGeometricEfficiency *= ( 1.0 - EvaluateCriticalRadius() / fStrip->GetCurvatureRadius()->GetX());
//        else vGeometricEfficiency = 0.0;
//    }
    return fabs(vGeometricEfficiency);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluatePotentialWellCentre(std::vector<double> vVector)
{
    if(StripIsBentX() && (fStrip->GetCurvatureRadius()->GetX()<EvaluateCriticalRadius()) ) return 0.;

    double vCentre = ( fStrip->GetCrystal()->GetDirectPeriodPlanar() * 0.5 );
    vCentre *= ( fParticle->GetMomentumVelocity() * 0.5 );
    if(StripIsBentX()) vCentre /= ( fStrip->GetCurvatureRadius()->GetX() );
    vCentre /= ( fStrip->GetCrystal()->GetPotentialCritical() );
    
    double vResult = fStrip->GetCrystal()->GetDirectPeriodPlanar() * 0.5 * ( 1. - vCentre );
    
    if( vVector != std::vector<double>() )
    {
        int vIndexCritical = int(float((fStrip->GetCrystal()->GetDirectPeriodPlanar() - fStrip->GetCrystal()->GetThermalVibrationConstant() * 2.5) / fStrip->GetCrystal()->GetDirectPeriodPlanar() * vVector.size()));
        double vCriticalPotential = vVector.at(vIndexCritical);
        int vIndex = vIndexCritical;
        do { vIndex--;
        } while(vVector.at(vIndex) < vCriticalPotential);
        vResult = ( float(vIndexCritical) - float(vIndex) ) / float(vVector.size());
        std::cout << vIndexCritical << " " << vIndex << " " << vCriticalPotential << " " << vResult << std::endl;
    }
    
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateMaximumChannelingAngle(std::vector<double> vVector) // Evaluate the maximum angle which a particle can have to be channeled
{
    double vPotentialDifference = fStrip->GetCrystal()->GetPotentialDifference(0.0 , fParticle->GetPositionVector()->GetX());
    double vMaximumAngle = pow(vPotentialDifference * 2.0 / fParticle->GetMomentumVelocity(),0.5);
    return vMaximumAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::EvaluateMaximumChannelingMomentum(std::vector<double> vVector) // Evaluate the maximum angle which a particle can have to be channeled
{
    double vPotentialDifference = fStrip->GetCrystal()->GetPotentialDifference(0.0 , fParticle->GetPositionVector()->GetX());
    double vEnergy = pow(vPotentialDifference * 2.0 / fParticle->GetMomentumVelocity(),0.5);
    return vEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation::GetPlanarElectricCharacteristicParticleReferenceFrame(double x, unsigned int vType)
{
    double vPotential = fStrip->GetCrystal()->GetPlanarElectricCharacteristic(x,vType);
    if(StripIsBentX()) if(vType==0) vPotential -= (fParticle->GetMomentumVelocity() / fStrip->GetCurvatureRadius()->GetX() * x);
    if(StripIsBentX()) if(vType==3) vPotential -= (fParticle->GetMomentumVelocity() / fStrip->GetCurvatureRadius()->GetX());
    return vPotential;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


double ECHARM_simulation::GetAxialElectricCharacteristicParticleReferenceFrame(double x, double y, unsigned int vType)
{
    double vPotential = fStrip->GetCrystal()->GetAxialElectricCharacteristic(x,y,vType);
    if(vType==0)
    {
        if(StripIsBentX())vPotential -= (fParticle->GetMomentumVelocity() / fStrip->GetCurvatureRadius()->GetX() * x);
        if(StripIsBentY())vPotential -= (fParticle->GetMomentumVelocity() / fStrip->GetCurvatureRadius()->GetY() * y);
    }
    if(vType==3)
    {
        if(StripIsBentX())vPotential -= (fParticle->GetMomentumVelocity() / fStrip->GetCurvatureRadius()->GetX());
        if(StripIsBentY())vPotential -= (fParticle->GetMomentumVelocity() / fStrip->GetCurvatureRadius()->GetY());
    }
    return vPotential;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_simulation::FindPlanarElectricCharacteristicParticleReferenceFrame(unsigned int vType,std::string vOptions)
{
    std::vector<double> vVector;
    vVector.clear();
    if(!fStrip->GetCrystal()->CheckCrystal()) return vVector;
    
    double Step = fStrip->GetCrystal()->GetStepPlanar();
    double x[fStrip->GetCrystal()->GetIntegrationStepNumberPlanar()];
    for(unsigned int i=0;i<fStrip->GetCrystal()->GetIntegrationStepNumberPlanar();i++) x[i] = i * Step;
    
#ifndef OPENMP_
    for(unsigned int i=0;i<fStrip->GetCrystal()->GetIntegrationStepNumberPlanar();i++)
        vVector.push_back(GetPlanarElectricCharacteristicParticleReferenceFrame(x[i],vType));
#endif
    
#ifdef OPENMP_
    int fIntegrationStepNumberPlanarInt = int(fStrip->GetCrystal()->GetIntegrationStepNumberPlanar());
    double vArray[fStrip->GetCrystal()->GetIntegrationStepNumberPlanar()];
#pragma omp parallel for
    for(int i=0;i<fIntegrationStepNumberPlanarInt;i++)
    {
        vArray[i] = GetPlanarElectricCharacteristicParticleReferenceFrame(x[i],vType);
    }
    for(unsigned int i=0;i<fStrip->GetCrystal()->GetIntegrationStepNumberPlanar();i++) vVector.push_back(vArray[i]);
#endif
    
    double Minimum = *std::min_element(vVector.begin(),vVector.end());
    double Maximum = *std::max_element(vVector.begin(),vVector.end());
    
    std::cout << "Min val is " << std::setw(10) << Minimum << " ---------- " << " Max val is " << std::setw(10) << Maximum << std::endl;
    
#ifdef ROOT_
    std::string vHistoName = fStrip->GetCrystal()->GetAtomName() + fStrip->GetCrystal()->GetMiller()->GetMillerTextPlanar() + "pl" + fStrip->GetCrystal()->GetCharacteristicType(vType) + "prf" + GetStrip()->GetRadiusValueAsStringText();
    fStrip->GetCrystal()->PrintPlanarElectricCharacteristicToTH1(vHistoName,vVector,vOptions);
#endif
    
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_simulation::FindAxialElectricCharacteristicParticleReferenceFrame(unsigned int vType,std::string vOptions)
{
    std::vector<double> vVector;
    vVector.clear();
    
    if(!fStrip->GetCrystal()->CheckCrystal()) return vVector;
    
    double StepX = fStrip->GetCrystal()->GetStepAxialX();
    double StepY = fStrip->GetCrystal()->GetStepAxialY();
    
    double x = 0.0;
    double y = 0.0;

#ifndef OPENMP_
    for(unsigned int j=0;j<fStrip->GetCrystal()->GetIntegrationStepNumberAxialY();j++)
    {
        y = j * StepY;
        for(unsigned int i=0;i<fStrip->GetCrystal()->GetIntegrationStepNumberAxialX();i++)
        {
            x = i * StepX;
            vVector.push_back(GetAxialElectricCharacteristicParticleReferenceFrame(x,y,vType));
        }
        std::cout << std::setw(4) << j+1 << " of " << std::setw(4) << fStrip->GetCrystal()->GetIntegrationStepNumberAxialY() << std::endl;
    }
#endif
    
#ifdef OPENMP_
    int fIntegrationStepNumberAxialXInt = int(fStrip->GetCrystal()->GetIntegrationStepNumberAxialX());
    double vArray[fStrip->GetCrystal()->GetIntegrationStepNumberAxialX()*fStrip->GetCrystal()->GetIntegrationStepNumberAxialY()];
    for(unsigned int j=0;j<fStrip->GetCrystal()->GetIntegrationStepNumberAxialY();j++)
    {
        y = j * StepY;
#pragma omp parallel for private(x)
        for(int i=0;i<fIntegrationStepNumberAxialXInt;i++)
        {
            x = i * StepX;
            vArray[i] = GetAxialElectricCharacteristicParticleReferenceFrame(x,y,vType);
        }
        
        for(unsigned int i=0;i<fStrip->GetCrystal()->GetIntegrationStepNumberAxialX();i++) vVector.push_back(vArray[i]);
        std::cout << std::setw(4) << j+1 << " of " << std::setw(4) << fStrip->GetCrystal()->GetIntegrationStepNumberAxialY() << std::endl;
    }
#endif
    
    std::cout << " Min val is " << std::setw(10) << *std::min_element(vVector.begin(),vVector.end());
    std::cout << " ---------- ";
    std::cout << " Max val is " << std::setw(10) << *std::max_element(vVector.begin(),vVector.end()) << std::endl;
    std::cout << " --------------------------------------------- " << std::endl;
    
#ifdef ROOT_
    std::string vHistoName = fStrip->GetCrystal()->GetAtomName() + fStrip->GetCrystal()->GetMiller()->GetMillerTextAxial() + "ax" + fStrip->GetCrystal()->GetCharacteristicType(vType) + "prf" + GetStrip()->GetRadiusValueAsStringText();
    
    fStrip->GetCrystal()->PrintAxialElectricCharacteristicToTH2(vHistoName,vVector,vOptions);
#endif
    
    
    return vVector;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


