//
//  ECHARM_crystal_reciprocal.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//


ECHARM_crystal_reciprocal::ECHARM_crystal_reciprocal()
{
    InitializePointersCrystalReciprocal();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_reciprocal::ECHARM_crystal_reciprocal(ECHARM_cell *cell, ECHARM_miller *miller, ECHARM_atom *atom, ECHARM_lattice *lattice)
{
    InitializePointersCrystalReciprocal();
    SetCell(cell);
    SetMiller(miller);
    AddBase(atom,lattice);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_reciprocal::ECHARM_crystal_reciprocal(ECHARM_crystal *crystal)
{
    InitializePointersCrystalReciprocal();
    SetCell(crystal->GetCell());
    SetMiller(crystal->GetMiller());
    for(unsigned int i=0;i<crystal->GetNumberOfBases();i++)
        AddBase(crystal->GetAtom(i),crystal->GetLattice(i));
    
    ComputeCrystalAverageParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_reciprocal::~ECHARM_crystal_reciprocal()
{
    if (&fAtom)         { delete &fAtom; }
    if (&fLattice)         { delete &fLattice; }
    if (&fMiller)         { delete &fMiller; }
    if (&fCell)         { delete &fCell; }
    if (&fAtom)         { delete &fAtom; }
    if (&fIntegrationStepNumberPlanar) { delete &fIntegrationStepNumberPlanar; }
    if (&fIntegrationStepNumberAxialX) { delete &fIntegrationStepNumberAxialX; }
    if (&fIntegrationStepNumberAxialY) { delete &fIntegrationStepNumberAxialY; }
    if (&fDirectPeriodPlanar) { delete &fDirectPeriodPlanar; }
    if (&fDirectPeriodAxialX) { delete &fDirectPeriodAxialX; }
    if (&fDirectPeriodAxialY) { delete &fDirectPeriodAxialY; }
    if (&fReciprocalPeriodPlanar) { delete &fReciprocalPeriodPlanar; }
    if (&fReciprocalPeriodAxialX) { delete &fReciprocalPeriodAxialX; }
    if (&fReciprocalPeriodAxialY) { delete &fReciprocalPeriodAxialY; }
    if (&fElectricFieldMaximum) { delete &fElectricFieldMaximum; }
    if (&fPotentialMaximum) { delete &fPotentialMaximum; }
    
    if(&fFourierTermNumberPlanar) { delete &fFourierTermNumberPlanar; }
    if(&fFourierTermNumberAxialX) { delete &fFourierTermNumberAxialX; }
    if(&fFourierTermNumberAxialY) { delete &fFourierTermNumberAxialY; }
    
    if (&fFourierCoefficientPlanarPotential) { delete &fFourierCoefficientPlanarPotential; }
    if (&fFourierCoefficientPlanarAtomicDensity) { delete &fFourierCoefficientPlanarAtomicDensity; }
    if (&fFourierCoefficientPlanarElectronDensity) { delete &fFourierCoefficientPlanarElectronDensity; }
    if (&fFourierCoefficientPlanarElectricFieldX) { delete &fFourierCoefficientPlanarElectricFieldX; }
    if (&fFourierCoefficientAxialPotential) { delete &fFourierCoefficientAxialPotential; }
    if (&fFourierCoefficientAxialAtomicDensity) { delete &fFourierCoefficientAxialAtomicDensity; }
    if (&fFourierCoefficientAxialElectronDensity) { delete &fFourierCoefficientAxialElectronDensity; }
    if (&fFourierCoefficientAxialElectricFieldX) { delete &fFourierCoefficientAxialElectricFieldX; }
    if (&fFourierCoefficientAxialElectricFieldY) { delete &fFourierCoefficientAxialElectricFieldY; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal_reciprocal::InitializePointersCrystalReciprocal()
{
    InitializePointersCrystal();
    
    fFourierTermNumberPlanar = 128;
    fFourierTermNumberAxialX = fFourierTermNumberAxialY = 16;
    
    fFourierCoefficientPlanarPotential.clear();
    fFourierCoefficientPlanarAtomicDensity.clear();
    fFourierCoefficientPlanarElectronDensity.clear();
    fFourierCoefficientPlanarElectricFieldX.clear();
    
    fFourierCoefficientAxialPotential.clear();
    fFourierCoefficientAxialAtomicDensity.clear();
    fFourierCoefficientAxialElectronDensity.clear();
    fFourierCoefficientAxialElectricFieldX.clear();
    fFourierCoefficientAxialElectricFieldY.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_crystal_reciprocal& ECHARM_crystal_reciprocal::operator=(const ECHARM_crystal_reciprocal& right)
{
    if (this != &right)
    {
        fAtom = right.fAtom;
        fLattice = right.fLattice;
        fCell = right.fCell;
        fMiller = right.fMiller;
        
        fIntegrationStepNumberPlanar = right.fIntegrationStepNumberPlanar;
        fIntegrationStepNumberAxialX = right.fIntegrationStepNumberAxialX;
        fIntegrationStepNumberAxialY = right.fIntegrationStepNumberAxialY;
        
        fDirectPeriodPlanar = right.fDirectPeriodPlanar;
        fDirectPeriodAxialX = right.fDirectPeriodAxialX;
        fDirectPeriodAxialY = right.fDirectPeriodAxialY;
        
        fReciprocalPeriodPlanar = right.fReciprocalPeriodPlanar;
        fReciprocalPeriodAxialX = right.fReciprocalPeriodAxialX;
        fReciprocalPeriodAxialY = right.fReciprocalPeriodAxialY;
        
        fElectricFieldMaximum = right.fElectricFieldMaximum;
        fPotentialMaximum = right.fPotentialMaximum;
        
        fFourierCoefficientPlanarPotential =  right.fFourierCoefficientPlanarPotential;
        fFourierCoefficientPlanarAtomicDensity = right.fFourierCoefficientPlanarAtomicDensity;
        fFourierCoefficientPlanarElectronDensity = right.fFourierCoefficientPlanarElectronDensity;
        fFourierCoefficientPlanarElectricFieldX = right.fFourierCoefficientPlanarElectricFieldX;
        
        fFourierCoefficientAxialPotential = right.fFourierCoefficientAxialPotential;
        fFourierCoefficientAxialAtomicDensity = right.fFourierCoefficientAxialAtomicDensity;
        fFourierCoefficientAxialElectronDensity = right.fFourierCoefficientAxialElectronDensity;
        fFourierCoefficientAxialElectricFieldX = right.fFourierCoefficientAxialElectricFieldX;
        fFourierCoefficientAxialElectricFieldY = right.fFourierCoefficientAxialElectricFieldY;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal_reciprocal::operator==(const ECHARM_crystal_reciprocal& right) const
{
    return (this == (ECHARM_crystal_reciprocal*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal_reciprocal::operator!=(const ECHARM_crystal_reciprocal& right) const
{
    return (this != (ECHARM_crystal_reciprocal*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal_reciprocal::FindFourierCoefficient(int vIndex[3], unsigned int vType)
{
    std::vector<double> FCRtemp;
    std::vector<double> SFtemp = FindStructureFactorCoefficient(vIndex);
    
    double FormFactor = 0.0;
    double ThermalVibration = 0.0;
    double ReciprocalVectorSquared = GetCell()->FindVectorSquaredReciprocal(vIndex);
    
    for(unsigned int i=0;i<GetNumberOfBases();i++)
    {
        FCRtemp.push_back(0.0);
        FCRtemp.push_back(0.0);
        
        FormFactor = GetAtom(i)->FindFormFactorReciprocal(ReciprocalVectorSquared);
        ThermalVibration = exp( - pow(GetAtom(i)->GetThermalVibrationConstant(),2) * ReciprocalVectorSquared / 2);
        
        if((vType==0) ||
           (vType==3) ||
           (vType==4))
        {
            FCRtemp[2*i] = FormFactor * SFtemp[2*i] * GetAtom(i)->GetZ() * ThermalVibration / ReciprocalVectorSquared;
            FCRtemp[2*i+1] = FormFactor * SFtemp[2*i+1] * GetAtom(i)->GetZ() * ThermalVibration / ReciprocalVectorSquared;
        }
        else if(vType==1)
        {
            FCRtemp[2*i] = SFtemp[2*i] * ThermalVibration;
            FCRtemp[2*i+1] = SFtemp[2*i+1] * ThermalVibration;
        }
        else if(vType==2)
        {
            FCRtemp[2*i] = (1 - FormFactor) * SFtemp[2*i] * GetAtom(i)->GetZ() * ThermalVibration ;
            FCRtemp[2*i+1] = (1 - FormFactor) * SFtemp[2*i+1] * GetAtom(i)->GetZ() * ThermalVibration ;
        }
        // std::cout << "FF " << FormFactor << " - SFre " << SFtemp[2*i] << " - SFim " << SFtemp[2*i+1] << " - TV " << ThermalVibration << " - G2 " << ReciprocalVectorSquared << std::endl;
    }
    return FCRtemp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal_reciprocal::FindFourierCoefficient(int vIndex00,int vIndex01,int vIndex02, unsigned int vType)
{
    int vIndex[3];
    vIndex[0]=vIndex00;
    vIndex[1]=vIndex01;
    vIndex[2]=vIndex02;
    std::vector<double> FCRtemp = FindFourierCoefficient(vIndex,vType);
    return FCRtemp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal_reciprocal::FindPlanarFourierCoefficient()
{
    fFourierCoefficientPlanarPotential = FindPlanarFourierCoefficient(0);
    fFourierCoefficientPlanarAtomicDensity = FindPlanarFourierCoefficient(1);
    fFourierCoefficientPlanarElectronDensity = FindPlanarFourierCoefficient(2);
    fFourierCoefficientPlanarElectricFieldX = FindPlanarFourierCoefficient(3);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal_reciprocal::FindAxialFourierCoefficient()
{
    fFourierCoefficientAxialPotential = FindAxialFourierCoefficient(0);
    fFourierCoefficientAxialAtomicDensity = FindAxialFourierCoefficient(1);
    fFourierCoefficientAxialElectronDensity = FindAxialFourierCoefficient(2);
    fFourierCoefficientAxialElectricFieldX = FindAxialFourierCoefficient(3);
    fFourierCoefficientAxialElectricFieldY = FindAxialFourierCoefficient(4);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector< std::vector<double> >  ECHARM_crystal_reciprocal::GetPlanarFourierCoefficient(unsigned int vType)
{
    //if(fFourierCoefficientPlanarElectricFieldX.size() == 0) FindPlanarFourierCoefficient();
    if(vType == 0) return fFourierCoefficientPlanarPotential;
    else if(vType == 1) return fFourierCoefficientPlanarAtomicDensity;
    else if(vType == 2) return fFourierCoefficientPlanarElectronDensity;
    else if(vType == 3) return fFourierCoefficientPlanarElectricFieldX;
    std::vector< std::vector<double> > vVector;
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector< std::vector< std::vector<double> > > ECHARM_crystal_reciprocal::GetAxialFourierCoefficient(unsigned int vType)
{
    //if(fFourierCoefficientAxialElectricFieldX.size() == 0) FindAxialFourierCoefficient();
    if(vType == 0) return fFourierCoefficientAxialPotential;
    else if(vType == 1) return fFourierCoefficientAxialAtomicDensity;
    else if(vType == 2) return fFourierCoefficientAxialElectronDensity;
    else if(vType == 3) return fFourierCoefficientAxialElectricFieldX;
    else if(vType == 4) return fFourierCoefficientAxialElectricFieldY;
    std::vector< std::vector< std::vector<double> > > vVector;
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
// std::vector<double> x -> describe  x[0]=re[0] x[1]=im[0] x[2]=re[1] x[3]=im[1] x[4]=re[2] x[5]=im[2] ...
// x[even] = re ; x[odd] = im
//
std::vector< std::vector<double> > ECHARM_crystal_reciprocal::FindPlanarFourierCoefficient(unsigned int vType)
{
    std::vector< std::vector<double> > cReImPl;
    cReImPl.clear();
    if(!CheckCrystal()) return cReImPl;
    
    int PlanarIndexes[3];
    
    std::vector<double> cRePl;
    std::vector<double> cImPl;
    cRePl.clear();
    cImPl.clear();
    
    std::vector<double> sfReIm;
    sfReIm.clear();
    
    double cRePlTemp = 0.0;
    double cImPlTemp = 0.0;
    
    for(int i=-fFourierTermNumberPlanar;i<=fFourierTermNumberPlanar;i++)
    {
        cRePlTemp = 0.0;
        cImPlTemp = 0.0;
        
        if(i!=0)
        {
            for(unsigned int k=0;k<3;k++) PlanarIndexes[k] = GetMiller()->GetMillerPlanar(k) * i;
            sfReIm = FindFourierCoefficient(PlanarIndexes,vType);
            for(unsigned int j=0;j<GetNumberOfBases();j++)
            {
                cRePlTemp += sfReIm[2*j];
                cImPlTemp += sfReIm[2*j+1];
            }
        }
        cRePl.push_back(cRePlTemp);
        cImPl.push_back(cImPlTemp);
    }
    
    cReImPl.push_back(cRePl);
    cReImPl.push_back(cImPl);
    
#ifdef ROOT_
    std::string vBaseName = GetAtomName() + GetMiller()->GetMillerTextPlanar() + "pl" + GetCharacteristicType(vType);
    
    std::string vHistoName = vBaseName + "Re";
    TH1F *vHistoCRe = new TH1F(vHistoName.c_str(),vHistoName.c_str(),cReImPl.at(0).size(),-float(cReImPl.at(0).size())/2.,+float(cReImPl.at(0).size())/2.);
    for(unsigned int i=0;i<cReImPl.at(0).size();i++)
        vHistoCRe->SetBinContent(i+1,cReImPl.at(0).at(i));
    
    vHistoName = vBaseName + "Im";
    TH1F *vHistoCIm = new TH1F(vHistoName.c_str(),vHistoName.c_str(),cReImPl.at(1).size(),-float(cReImPl.at(1).size())/2.,+float(cReImPl.at(1).size())/2.);
    for(unsigned int i=0;i<cReImPl.at(1).size();i++)
        vHistoCIm->SetBinContent(i+1,cReImPl.at(1).at(i));
#endif
    
    return cReImPl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_reciprocal::GetPlanarElectricCharacteristic(double x, unsigned int vType)
{
    if(!CheckCrystal()) return 0.0;
    
    double vElCh = 0;
    double vTempAngleDouble = 0.;
    std::vector < std::vector<double> > vFourierCoefficientPlanar;
    
    if(fFourierCoefficientPlanarPotential.size()!=0){ vFourierCoefficientPlanar = GetPlanarFourierCoefficient(vType); }
    else{
        FindPlanarFourierCoefficient();
        vFourierCoefficientPlanar = GetPlanarFourierCoefficient(vType);
    }
    
    for(int i = -fFourierTermNumberPlanar; i <= fFourierTermNumberPlanar;i++)
    {
        vTempAngleDouble = fReciprocalPeriodPlanar * x * i;
        if(vType==3)
        {
            vElCh += (fReciprocalPeriodPlanar * i * (vFourierCoefficientPlanar.at(0).at(+i+fFourierTermNumberPlanar)) * sin(vTempAngleDouble));
            vElCh += (fReciprocalPeriodPlanar * i * (vFourierCoefficientPlanar.at(1).at(+i+fFourierTermNumberPlanar)) * cos(vTempAngleDouble));
        }
        else if((vType==0)
                || (vType==1)
                || (vType==2))
        {
            vElCh += ((vFourierCoefficientPlanar.at(0).at(+i+fFourierTermNumberPlanar)) * cos(vTempAngleDouble));
            vElCh -= ((vFourierCoefficientPlanar.at(1).at(+i+fFourierTermNumberPlanar)) * sin(vTempAngleDouble));
        }
    }
    
    if((vType==0) || (vType==3))
    {
        vElCh *= cElectronLengthOnCharge; //eV*m on charge evaluated in unit of electron charge
        vElCh /= GetCell()->FindVolume();
    }
    
    if(vType==1)
    {
        vElCh += ( fNumberOfCoordinatesTotal );
        vElCh /= ( fNumberOfCoordinatesTotal );
        //        vElCh /= ( fDirectPeriodPlanar );
    }
    
    if(vType==2)
    {
        vElCh += ( fNumberOfCoordinatesTotal * GetZ() );
        vElCh /= ( fNumberOfCoordinatesTotal * GetZ() );
        //        vElCh /= ( fDirectPeriodPlanar );
    }
    
    return vElCh;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
// std::vector< std::vector<double> > y x -> describe  y[0]x[0]=re[0][0] ; y[0] x[1]=im[0][0] ; y[1] x[0] = re[0][1] ; y[1] x[0]=im[0][1] ...
// x[even] = re ; x[odd] = im
//
std::vector< std::vector < std::vector<double> > >  ECHARM_crystal_reciprocal::FindAxialFourierCoefficient(unsigned int vType)
{
    std::cout << "ECHARM_crystal_reciprocal - Calculate Fourier Coefficient of " << vType << " for " << GetAtomName() << " " << GetMiller()->GetMillerTextAxial() << " axis" << std::endl;
    std::vector< std::vector < std::vector<double> > >  cReImAx;
    cReImAx.clear();
    if(!CheckCrystal()) return cReImAx;
    
    int vIndexAxial[3];
    
    std::vector<double> cReAx;
    std::vector<double> cImAx;
    
    std::vector<std::vector<double> > cReAxY;
    std::vector<std::vector<double> > cImAxY;
    cReAxY.clear();
    cImAxY.clear();
    
    std::vector<double> sfReIm;
    sfReIm.clear();
    
    double cReAxTemp = 0.0;
    double cImAxTemp = 0.0;
    
    
    for(int j=-fFourierTermNumberAxialY; j<=fFourierTermNumberAxialY; j++)
    {
        cReAx.clear();
        cImAx.clear();
        for(int i=-fFourierTermNumberAxialX; i<=fFourierTermNumberAxialX;i++)
        {
            cReAxTemp = 0.0;
            cImAxTemp = 0.0;
            
            {
                if(GetCell()->IsCubic())
                {
                    vIndexAxial[0]=i;
                    vIndexAxial[1]=j;
                    vIndexAxial[2]=0;
                    
                    if(GetMiller()->CheckCubicIndexesOrthogonalToMainAxis(vIndexAxial))
                    {
                        GetMiller()->ReverseMillerOrderForCubicAxialCalculationsGeneral(vIndexAxial);
                        sfReIm = FindFourierCoefficient(vIndexAxial,vType);
                        for(unsigned int k=0;k<GetNumberOfBases();k++)
                        {
                            cReAxTemp += sfReIm[2*k];
                            cImAxTemp += sfReIm[2*k+1];
                        }
                    }
                }
                else
                {
                    vIndexAxial[0]=i*GetMiller()->GetMillerAxial(1,0)+j*GetMiller()->GetMillerAxial(2,0);
                    vIndexAxial[1]=i*GetMiller()->GetMillerAxial(1,1)+j*GetMiller()->GetMillerAxial(2,1);
                    vIndexAxial[2]=i*GetMiller()->GetMillerAxial(1,2)+j*GetMiller()->GetMillerAxial(2,2);
                    sfReIm = FindFourierCoefficient(vIndexAxial,vType);
                    for(unsigned int k=0;k<GetNumberOfBases();k++)
                    {
                        cReAxTemp += sfReIm[2*k];
                        cImAxTemp += sfReIm[2*k+1];
                    }
                }
            }
            cReAx.push_back(cReAxTemp);
            cImAx.push_back(cImAxTemp);
        }
        cReAxY.push_back(cReAx);
        cImAxY.push_back(cImAx);
    }
    
    cReImAx.push_back(cReAxY);
    cReImAx.push_back(cImAxY);
    
#ifdef ROOT_
    std::string vBaseName = GetAtomName() + GetMiller()->GetMillerTextAxial() + "ax" + GetCharacteristicType(vType);
    std::string vHistoName = vBaseName + "Re";
    TH2F *vHistoCRe = new TH2F(vHistoName.c_str(),vHistoName.c_str(),cReImAx.at(0).at(0).size(),-float(cReImAx.at(0).at(0).size())/2.,+float(cReImAx.at(0).at(0).size())/2.,cReImAx.at(0).size(),-float(cReImAx.at(0).size())/2.,+float(cReImAx.at(0).size())/2.);
    for(unsigned int j=0;j<cReImAx.at(0).size();j++)
        for(unsigned int i=0;i<cReImAx.at(0).at(j).size();i++) vHistoCRe->SetBinContent(i,j,cReImAx.at(0).at(j).at(i));
    
    vHistoName = vBaseName + "Im";
    TH2F *vHistoCIm = new TH2F(vHistoName.c_str(),vHistoName.c_str(),cReImAx.at(1).at(0).size(),-float(cReImAx.at(1).at(0).size())/2.,+float(cReImAx.at(1).at(0).size())/2.,cReImAx.at(1).size(),-float(cReImAx.at(1).size())/2.,+float(cReImAx.at(1).size())/2.);
    for(unsigned int j=0;j<cReImAx.at(1).size();j++)
        for(unsigned int i=0;i<cReImAx.at(1).at(j).size();i++) vHistoCIm->SetBinContent(i,j,cReImAx.at(1).at(j).at(i));
#endif
    std::cout << "ECHARM_crystal_reciprocal -  End of Calculation of Fourier Coefficient of " << vType << " for " << GetAtomName() << " " << GetMiller()->GetMillerTextAxial() << " axis" << std::endl;
    
    return cReImAx;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_reciprocal::GetAxialElectricCharacteristic(double x, double y, unsigned int vType)
{
    if(!CheckCrystal()) return 0.0;
    
    double vElCh = 0;
    int vIndexAxial[3];
    
    double vTempAngleDouble = 0.;
    double vTempGx = 0.;
    double vTempGy = 0.;
    
    double vMillerAxialXModule = pow(GetMiller()->GetMillerAxialModuleX(),2.0);
    double vMillerAxialYModule = pow(GetMiller()->GetMillerAxialModuleY(),2.0);
    
    std::vector< std::vector < std::vector<double> > > vFourierCoefficientAxial;
    
    if(fFourierCoefficientAxialPotential.size()!=0){ vFourierCoefficientAxial = GetAxialFourierCoefficient(vType); }
    else{
        FindAxialFourierCoefficient();
        vFourierCoefficientAxial = GetAxialFourierCoefficient(vType);
    }
        
    
    if(GetCell()->IsCubic() && !GetMiller()->IsMainAxis())
        for(int j = -fFourierTermNumberAxialY; j<=fFourierTermNumberAxialY; j++)
            for(int i = -fFourierTermNumberAxialX; i<=fFourierTermNumberAxialX; i++)
            {
                {
                    vIndexAxial[0]=i;
                    vIndexAxial[1]=j;
                    vIndexAxial[2]=0;

                    vTempAngleDouble = 0.0;
                    vTempGx = 0.0;
                    vTempGy = 0.0;
                    
                    if(GetMiller()->CheckCubicIndexesOrthogonalToMainAxis(vIndexAxial))
                    {
                        GetMiller()->ReverseMillerOrderForCubicAxialCalculationsGeneral(vIndexAxial);

                        for(int k=0;k<3;k++)
                        {
                            vTempGx += (vIndexAxial[k] * GetMiller()->GetMillerAxial(1,k) * fReciprocalPeriodAxialX / vMillerAxialXModule);
                            vTempGy += (vIndexAxial[k] * GetMiller()->GetMillerAxial(2,k) * fReciprocalPeriodAxialY / vMillerAxialYModule);
                        }
                        vTempAngleDouble = vTempGx * x + vTempGy * y;
                        
                        if(vType==3)
                        {
                            vElCh += ( vTempGx * (vFourierCoefficientAxial.at(0).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * sin(vTempAngleDouble));
                            vElCh += ( vTempGx * (vFourierCoefficientAxial.at(1).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * cos(vTempAngleDouble));
                        }
                        if(vType==4)
                        {
                            vElCh += ( vTempGy * ( vFourierCoefficientAxial.at(0).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * sin(vTempAngleDouble));
                            vElCh += ( vTempGy * ( vFourierCoefficientAxial.at(1).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * cos(vTempAngleDouble));
                        }
                        else if((vType==0)
                                || (vType==1)
                                || (vType==2))
                        {
                            vElCh += (( vFourierCoefficientAxial.at(0).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * cos(vTempAngleDouble));
                            vElCh -= (( vFourierCoefficientAxial.at(1).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * sin(vTempAngleDouble));
                        }
                        
                    }
                }
            }
    else
        for(int j = -fFourierTermNumberAxialY; j<=fFourierTermNumberAxialY; j++)
            for(int i = -fFourierTermNumberAxialX; i<=fFourierTermNumberAxialX; i++)
                if(i!=0 || j!=0)
            {
                vTempAngleDouble = fReciprocalPeriodAxialX * x * i + fReciprocalPeriodAxialY * y * j;
                if(vType==3)
                {
                    vElCh += (fReciprocalPeriodAxialX * i * ( vFourierCoefficientAxial.at(0).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * sin(vTempAngleDouble) );
                    vElCh += (fReciprocalPeriodAxialX * i * ( vFourierCoefficientAxial.at(1).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * cos(vTempAngleDouble) );
                }
                if(vType==4)
                {
                    vElCh += (fReciprocalPeriodAxialY * j * ( vFourierCoefficientAxial.at(0).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * sin(vTempAngleDouble) );
                    vElCh += (fReciprocalPeriodAxialY * j * ( vFourierCoefficientAxial.at(1).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX) ) * cos(vTempAngleDouble) );
                }
                else if((vType==0)
                        || (vType==1)
                        || (vType==2))
                {
                    vElCh += ( vFourierCoefficientAxial.at(0).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX)  * cos(vTempAngleDouble) );
                    vElCh -= ( vFourierCoefficientAxial.at(1).at(j + fFourierTermNumberAxialY).at(i + fFourierTermNumberAxialX)  * sin(vTempAngleDouble) );
                }
            }
    
    
    if((vType==0) || (vType==3) || (vType==4))
    {
        vElCh *= cElectronLengthOnCharge; //eV*m on charge evaluated in unit of electron charge
        vElCh /= GetCell()->FindVolume();
    }
    
    if(vType==1)
    {
        vElCh += ( fNumberOfCoordinatesTotal );
        vElCh /= ( fNumberOfCoordinatesTotal );
        //        vElCh /= ( fDirectPeriodAxialX );
        //        vElCh /= ( fDirectPeriodAxialY );
    }
    
    if(vType==2)
    {
        vElCh += ( fNumberOfCoordinatesTotal * GetZ() );
        vElCh /= ( fNumberOfCoordinatesTotal * GetZ() );
        //        vElCh /= ( fDirectPeriodAxialX );
        //        vElCh /= ( fDirectPeriodAxialY );
    }
    
    return vElCh;
}

