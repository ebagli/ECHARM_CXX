//
//  ECHARM_distribution.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_distribution::ECHARM_distribution()
{
    InitializePointersRandom();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_distribution::ECHARM_distribution(unsigned int vType)
{
    InitializePointersRandom();
    fType = vType;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_distribution::~ECHARM_distribution()
{
    if (&fGaussFirstOk)         { delete &fGaussFirstOk; }
    if (&fGaussSecondValue)         { delete &fGaussSecondValue; }
    if (&fPar)         { delete &fPar; }
    if (&fParNames)         { delete &fParNames; }
    if (&fType)         { delete &fType; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_distribution& ECHARM_distribution::operator=(const ECHARM_distribution& right)
{
    if (this != &right)
    {
        InitializePointersRandom();
        fGaussFirstOk = right.fGaussFirstOk;
        fGaussSecondValue= right.fGaussSecondValue;
        fPar = right.fPar;
        fParNames = right.fParNames;
        fType = right.fType;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_distribution::InitializePointersRandom()
{
    fGaussFirstOk = 0;
    fGaussSecondValue = 0.;
    fPar.clear();
    fParNames.clear();
    SetDistributionType(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_distribution::operator==(const ECHARM_distribution& right) const
{
    return (this == (ECHARM_distribution*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_distribution::operator!=(const ECHARM_distribution& right) const
{
    return (this != (ECHARM_distribution*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution::GenerateNumberBox(double Mean, double HalfWidth)
{
    double RandomNumber = 0.0;
    RandomNumber = ( drand48() * 2.0 - 1.0 ) * HalfWidth + Mean;
    return RandomNumber;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution::GenerateNumberNegPol2(double Mean, double RMS, double xMin, double xMax)
{
    double RandomNumber = 0.0;
    double vVariableX = 0.0;
    double vVariableY = 0.0;
    double vMax = 1.0 / (pow( xMin / RMS - Mean, 2.0));
    do
    {
        vVariableX = xMin + (drand48() - 0.5) * 2.0 * (xMax - xMin);
        RandomNumber = 1.0 / (pow(vVariableX / RMS - Mean, 2.0));
        vVariableY = drand48() * vMax;
    } while (vVariableY > RandomNumber);

    return vVariableX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution::GetValueBox(double vX,double Mean, double HalfWidth)
{
    if(fabs(vX-Mean)<HalfWidth) return 1./(2.*HalfWidth);
    else return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution::GetValueGauss(double vX, double Mean, double Sigma)
{
    double vValue = exp(-0.5*pow((vX-Mean)/(Sigma),2.))/(pow(2.*M_PI,0.5)*Sigma);
    return vValue;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution::GenerateNumberGauss(double Mean, double Sigma)
{
    double GaussValue = 0.0;
    double GaussTemp = 0.0;
    double GaussTempX1 = 0.0;
    double GaussTempX2 = 0.0;

    
    if (fGaussFirstOk)		       
    {
        GaussValue = fGaussSecondValue;
        fGaussFirstOk = 0;
    }
    else
    {
        do {
            GaussTempX1 = 2.0 * drand48() - 1.0;
            GaussTempX2 = 2.0 * drand48() - 1.0;
            GaussTemp = GaussTempX1 * GaussTempX1 + GaussTempX2 * GaussTempX2;
        } while ( GaussTemp >= 1.0 );
        
        GaussTemp = sqrt( (-2.0*log(GaussTemp))/GaussTemp);
        GaussValue = GaussTempX1 * GaussTemp;
        fGaussSecondValue = GaussTempX2 * GaussTemp;
        fGaussFirstOk = 1;
    }
    return (Mean + GaussValue * Sigma);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_distribution::PrintDistributionProperties()
{
    std::cout << "ECHARM_distribution - Print Properties" << std::endl;
    for(unsigned int i = 0;i<fPar.size();i++)
    std::cout << "Parameter " << std::setw(2) << i<< "                   " << std::setw(10) << fPar.at(i) << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_distribution::SetDistributionType(unsigned int vType)
{
    fPar.clear();
    if(vType==0)
    {
        fPar.push_back(0.0);
        fParNames.push_back("Mean");
        fPar.push_back(1.0);
        fParNames.push_back("HalfWidth");
        fType = vType;
    }
    else if(vType==1)
    {
        fPar.push_back(0.0);
        fParNames.push_back("Mean");
        fPar.push_back(1.0);
        fParNames.push_back("Sigma");
        fType = vType;
    }
    else if(vType==2)
    {
        fPar.push_back(0.0);
        fParNames.push_back("Mean");
        fPar.push_back(1.0);
        fParNames.push_back("RMS");
        fPar.push_back(1.0);
        fParNames.push_back("LimitLeft");
        fPar.push_back(2.0);
        fParNames.push_back("LimitRight");
        fType = vType;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution::GenerateNumber()
{
    if(fType==0) return GenerateNumberBox(fPar.at(0),fPar.at(1));
    else if(fType==1) return GenerateNumberGauss(fPar.at(0),fPar.at(1));
    else if(fType==2) return GenerateNumberNegPol2(fPar.at(0),fPar.at(1),fPar.at(2),fPar.at(3));
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution::GetValue(double vX)
{
    if(fType==0) return GetValueBox(vX,fPar.at(0),fPar.at(1));
    else if(fType==1) return GetValueGauss(vX,fPar.at(0),fPar.at(1));
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


