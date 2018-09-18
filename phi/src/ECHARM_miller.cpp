//
//  ECHARM_miller.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//


ECHARM_miller::ECHARM_miller()
{
    InitializePointersMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller::ECHARM_miller(int MillerPlanar[3],int MillerAxial[3])
{
    InitializePointersMiller();
    SetMillerPlanar(MillerPlanar);
    SetMillerAxial(MillerAxial);
    ComputeCubicAxialMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller::ECHARM_miller(int MillerPl00, int MillerPl01, int MillerPl02,int MillerAx00, int MillerAx01, int MillerAx02)
{
    InitializePointersMiller();
    SetMillerPlanar(MillerPl00, MillerPl01, MillerPl02);
    SetMillerAxial(MillerAx00, MillerAx01, MillerAx02);
    ComputeCubicAxialMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ECHARM_miller::~ECHARM_miller()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::SetMillerPlanar(int MillerPlanar[3])
{
    int i;
    for(i=0;i<3;i++) fMillerPlanar[i] = MillerPlanar[i];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::SetMillerAxial(int MillerAxial[3])
{
    int i;
    for(i=0;i<3;i++) fMillerAxial[0][i] = MillerAxial[i];
    ComputeCubicAxialMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::SetMillerAxialX(int MillerAxial[3])
{
    int i;
    for(i=0;i<3;i++) fMillerAxial[1][i] = MillerAxial[i];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::SetMillerAxialY(int MillerAxial[3])
{
    int i;
    for(i=0;i<3;i++) fMillerAxial[2][i] = MillerAxial[i];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::SetMillerPlanar(int MillerPl00, int MillerPl01, int MillerPl02)
{
    fMillerPlanar[0] = MillerPl00;
    fMillerPlanar[1] = MillerPl01;
    fMillerPlanar[2] = MillerPl02;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::SetMillerAxial(int MillerAx00, int MillerAx01, int MillerAx02)
{
    fMillerAxial[0][0] = MillerAx00;
    fMillerAxial[0][1] = MillerAx01;
    fMillerAxial[0][2] = MillerAx02;
    ComputeCubicAxialMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::SetMillerAxialX(int MillerAx10, int MillerAx11, int MillerAx12)
{
    fMillerAxial[1][0] = MillerAx10;
    fMillerAxial[1][1] = MillerAx11;
    fMillerAxial[1][2] = MillerAx12;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::SetMillerAxialY(int MillerAx20, int MillerAx21, int MillerAx22)
{
    fMillerAxial[2][0] = MillerAx20;
    fMillerAxial[2][1] = MillerAx21;
    fMillerAxial[2][2] = MillerAx22;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_miller::GetMillerPlanar(int vIndex)
{
    if(vIndex<3)
        return fMillerPlanar[vIndex];
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_miller::GetMillerAxial(int vIndex) 
{
    if(vIndex<3)
        return fMillerAxial[0][vIndex];
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_miller::GetMillerAxial(int vIndex,int vIndex_yz)
{
    if((vIndex < 3) && (vIndex_yz < 3))
        return fMillerAxial[vIndex][vIndex_yz];
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_miller::GetMillerAxialModule(int vIndex)
{
    double vModule = pow( pow(double(fMillerAxial[vIndex][0]),2.0) + pow(double(fMillerAxial[vIndex][1]),2.0) + pow(double(fMillerAxial[vIndex][2]),2) , 0.5);
    return vModule;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ECHARM_miller::PrintMiller()
{
    std::cout << "ECHARM_miller - Print Planar & Axial Indexes" << std::endl;
    std::cout << "( " << std::setw(3) << fMillerPlanar[0] << " " << std::setw(3) << fMillerPlanar[1] << " " << std::setw(3) << fMillerPlanar[2] << "  )" << std::endl; 
    std::cout << "< " << std::setw(3) << fMillerAxial[0][0] << " " << std::setw(3) << fMillerAxial[0][1] << " " << std::setw(3) << fMillerAxial[0][2] << "  >" << std::endl; 
    std::cout << "ECHARM_miller - Print Miller Indexes of Axes Orthogonal to Main Axis" << std::endl;
    std::cout << "< " << std::setw(3) << fMillerAxial[1][0] << " " << std::setw(3) << fMillerAxial[1][1] << " " << std::setw(3) << fMillerAxial[1][2] << "  >" << std::endl; 
    std::cout << "< " << std::setw(3) << fMillerAxial[2][0] << " " << std::setw(3) << fMillerAxial[2][1] << " " << std::setw(3) << fMillerAxial[2][2] << "  >" << std::endl; 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::string ECHARM_miller::GetMillerText(int vMiller[3])
{
    std::stringstream vSS;
    vSS << vMiller[0] << vMiller[1] << vMiller[2];
    std::string vBaseName = vSS.str();
    return vBaseName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::InitializePointersMiller()
{
    int i,j;
    for(i=0;i<3;i++) fMillerPlanar[i] = 0;
    for(i=0;i<3;i++) 
        for(j=0;j<3;j++) 
            fMillerAxial[i][j] = 0;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::PrintMillerOn(ECHARM_Miller_Save &vMillerSave)
{
    vMillerSave.MillerPlane0 = fMillerPlanar[0];
    vMillerSave.MillerPlane1 = fMillerPlanar[1];
    vMillerSave.MillerPlane2 = fMillerPlanar[2];
    vMillerSave.MillerAxis0 = fMillerAxial[0][0];
    vMillerSave.MillerAxis1 = fMillerAxial[0][1];
    vMillerSave.MillerAxis2 = fMillerAxial[0][2];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_miller::operator==(const ECHARM_miller& right) const
{
    return (this == (ECHARM_miller*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_miller::operator!=(const ECHARM_miller& right) const
{
    return (this != (ECHARM_miller*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_miller& ECHARM_miller::operator=(const ECHARM_miller& right)
{
    if (this != &right)
    {
        InitializePointersMiller();
        for(int i=0;i<3;i++)
        {
            fMillerPlanar[i] = right.fMillerPlanar[i];
            fMillerAxial[0][i] = right.fMillerAxial[0][i];
        }
        ComputeCubicAxialMiller();
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::ComputeCubicAxialMiller()
{    
    int i,j,k,l;
    
    for(i=1;i<3;i++)
        for(j=0;j<3;j++) fMillerAxial[i][j] = 0;
    
    
    if((fMillerAxial[0][0]!=0) && (fMillerAxial[0][1]==0) && (fMillerAxial[0][2]==0))
    {
        fMillerAxial[1][0] = 0; fMillerAxial[1][1] = 1; fMillerAxial[1][2] = 0;
		fMillerAxial[2][0] = 0; fMillerAxial[2][1] = 0; fMillerAxial[2][2] = 1;
    }
    else if((fMillerAxial[0][0]==0) && (fMillerAxial[0][1]!=0) && (fMillerAxial[0][2]==0))
    {
		fMillerAxial[1][0] = 0; fMillerAxial[1][1] = 0; fMillerAxial[1][2] = 1;
		fMillerAxial[2][0] = 1; fMillerAxial[2][1] = 0; fMillerAxial[2][2] = 0;
    }
    else if((fMillerAxial[0][0]==0) && (fMillerAxial[0][1]==0) && (fMillerAxial[0][2]!=0))
    {
		fMillerAxial[1][0] = 1; fMillerAxial[1][1] = 0; fMillerAxial[1][2] = 0;
		fMillerAxial[2][0] = 0; fMillerAxial[2][1] = 1; fMillerAxial[2][2] = 0;
    }
    else
    {
        if((fMillerAxial[0][0]!=0) && (fMillerAxial[0][1]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMillerAxial[0][0]*i==-fMillerAxial[0][1]*j)
                                {fMillerAxial[1][0] = i;fMillerAxial[1][1] = j;fMillerAxial[1][2] = 0;}
                k++;
            }
            while((fMillerAxial[1][0] == 0) && (fMillerAxial[1][1] == 0) && (fMillerAxial[1][2] == 0));
        }
        
        if((fMillerAxial[0][1]!=0) && (fMillerAxial[0][2]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMillerAxial[0][2]*i==-fMillerAxial[0][1]*j)
                                {fMillerAxial[1][2] = i;fMillerAxial[1][1] = j;fMillerAxial[1][0] = 0;}
                k++;
            }
            while((fMillerAxial[1][0] == 0) && (fMillerAxial[1][1] == 0) && (fMillerAxial[1][2] == 0));
        }
        
        if((fMillerAxial[0][0]!=0) && (fMillerAxial[0][1]==0) && (fMillerAxial[0][2]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMillerAxial[0][2]*i==-fMillerAxial[0][0]*j)
                                {fMillerAxial[2][0] = j;fMillerAxial[2][1] = 0;fMillerAxial[2][2] = i;}
                k++;
            }
            while((fMillerAxial[2][0] == 0) && (fMillerAxial[2][1] == 0) && (fMillerAxial[2][2] == 0));
        }
        
        if((fMillerAxial[0][0]!=0) && (fMillerAxial[0][1]!=0) && (fMillerAxial[0][2]==0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMillerAxial[0][1]*i==-fMillerAxial[0][0]*j)
                                {fMillerAxial[2][0] = j;fMillerAxial[2][1] = i;fMillerAxial[2][2] = 0;}
                k++;
            }
            while((fMillerAxial[2][0] == 0) && (fMillerAxial[2][1] == 0) && (fMillerAxial[2][2] == 0));
        }
        
        if((fMillerAxial[0][0]==0) && (fMillerAxial[0][1]!=0) && (fMillerAxial[0][2]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMillerAxial[0][2]*i==-fMillerAxial[0][1]*j)
                                {fMillerAxial[2][0] = 0;fMillerAxial[2][1] = j;fMillerAxial[2][2] = i;}
                k++;
            }
            while((fMillerAxial[2][0] == 0) && (fMillerAxial[2][1] == 0) && (fMillerAxial[2][2] == 0));
        }
        
        if((fMillerAxial[0][0]!=0) && (fMillerAxial[0][1]!=0) && (fMillerAxial[0][2]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                for(l=k;l>=-k;l--)
                                    if(l!=0)
                                        if(((fMillerAxial[0][0]*i + fMillerAxial[0][1]*j + fMillerAxial[0][2]*l)==0) && ((fMillerAxial[1][0]*i + fMillerAxial[1][1]*j + fMillerAxial[1][2]*l)==0))
                                        {fMillerAxial[2][0] = i;fMillerAxial[2][1] = j;fMillerAxial[2][2] = l;}
                k++;
            }
            while((fMillerAxial[2][0] == 0) && (fMillerAxial[2][1] == 0) && (fMillerAxial[2][2] == 0));
        }
        
        if((fMillerAxial[0][0]==0) && (fMillerAxial[0][1]!=0) && (fMillerAxial[0][2]!=0)) {fMillerAxial[1][0] = 1; fMillerAxial[1][1] = 0; fMillerAxial[1][2] = 0;}
        else if((fMillerAxial[0][0]!=0) && (fMillerAxial[0][1]==0) && (fMillerAxial[0][2]!=0)) {fMillerAxial[1][0] = 0; fMillerAxial[1][1] = 1; fMillerAxial[1][2] = 0;}
        else if((fMillerAxial[0][0]!=0) && (fMillerAxial[0][1]!=0) && (fMillerAxial[0][2]==0)) {fMillerAxial[1][0] = 0; fMillerAxial[1][1] = 0; fMillerAxial[1][2] = 1;}
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::ReverseMillerOrderForCubicAxialCalculations(int MillerReversed[3])
{
    if(fMillerAxial[0][2]!=0)
    {
        MillerReversed[0]=fMillerAxial[0][0];
        MillerReversed[1]=fMillerAxial[0][1];
        MillerReversed[2]=fMillerAxial[0][2];
    }
    else if(fMillerAxial[0][1]!=0)
    {
        MillerReversed[0]=fMillerAxial[0][2];
        MillerReversed[1]=fMillerAxial[0][0];
        MillerReversed[2]=fMillerAxial[0][1];
    }
    else if(fMillerAxial[0][0]!=0) 
    {
        MillerReversed[0]=fMillerAxial[0][1];
        MillerReversed[1]=fMillerAxial[0][2];
        MillerReversed[2]=fMillerAxial[0][0];
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::ReverseMillerOrderForCubicAxialCalculationsGeneral(int MillerReversed[3])
{
    int MillerTemp[3];
    for(unsigned int i = 0;i<3;i++) MillerTemp[i]=MillerReversed[i];
    
    if(fMillerAxial[0][2]!=0)
    {
        MillerReversed[0]=MillerTemp[0];
        MillerReversed[1]=MillerTemp[1];
        MillerReversed[2]=MillerTemp[2];
    }
    else if(fMillerAxial[0][1]!=0)
    {
        MillerReversed[0]=MillerTemp[1];
        MillerReversed[1]=MillerTemp[2];
        MillerReversed[2]=MillerTemp[0];
    }
    else if(fMillerAxial[0][0]!=0) 
    {
        MillerReversed[0]=MillerTemp[2];
        MillerReversed[1]=MillerTemp[0];
        MillerReversed[2]=MillerTemp[1];
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if MillerOrthogonal[0] & MillerOrthogonal[1] vIndexes can be used and, if they can  be used, the MillerOrthogonal[2] is the third vIndex of the orthogonal vector
//
bool ECHARM_miller::CheckCubicIndexesOrthogonalToMainAxis(int MillerOrthogonal[3])
{
    double tempF[2];
    int MillerTemp[3] = {0,0,0};
    ReverseMillerOrderForCubicAxialCalculations(MillerTemp);
    
    tempF[0] = -(MillerOrthogonal[0] * MillerTemp[0] + MillerOrthogonal[1] * MillerTemp[1]) / MillerTemp[2];
    tempF[1] = (MillerOrthogonal[0] * MillerTemp[0] + MillerOrthogonal[1] * MillerTemp[1] + tempF[0] * MillerTemp[2]);
    MillerOrthogonal[2] = int(tempF[0]);
    
    if((fabs(tempF[1]) < 1.E-7) && (fabs(double(MillerOrthogonal[2])-tempF[0]) < 1.E-7))
        if((pow(MillerOrthogonal[0],2) + pow(MillerOrthogonal[1],2) + pow(MillerOrthogonal[2],2)) != 0) return true;
    
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if Miller axial vectors are orthogonal each other
//

bool ECHARM_miller::CheckMillerIndexesOrthogonal()
{
    int vIndexesSum = 0;
    for(unsigned int i=0;i<3;i++)
        for(unsigned int j=i+1;j<3;j++)
            for(unsigned int k=0;k<3;k++)
                    vIndexesSum += (fMillerAxial[i][k]*fMillerAxial[j][k]);
                
    if(vIndexesSum==0) return true;
    
    std::cout << "ECHARM_miller - Axial Indexes are not orthogonal" << std::endl;
    
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if Miller axial vectors are orthogonal each other
//

bool ECHARM_miller::IsMainAxis()
{
    if( (fMillerAxial[0][0] == 1) && (fMillerAxial[0][1] == 0) && (fMillerAxial[0][2] == 0) ) return true;
    if( (fMillerAxial[0][0] == 0) && (fMillerAxial[0][1] == 1) && (fMillerAxial[0][2] == 0) ) return true;
    if( (fMillerAxial[0][0] == 0) && (fMillerAxial[0][1] == 0) && (fMillerAxial[0][2] == 1) ) return true;
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
