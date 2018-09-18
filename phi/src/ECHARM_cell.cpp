//
//  ECHARM_cell.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_cell::ECHARM_cell()
{
    InitializePointersCell();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_cell::ECHARM_cell(ECHARM_threevector *Size, ECHARM_threevector *Angle)
{
    InitializePointersCell();
    fSize->Set(Size);
    fAngle->Set(Angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_cell::ECHARM_cell(double Size00, double Size01, double Size02, double Angle00, double Angle01, double Angle02)
{
    InitializePointersCell();
    fSize->Set(Size00,Size01,Size02);
    fAngle->Set(Angle00,Angle01,Angle02);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_cell::ECHARM_cell(ECHARM_threevector *Size)
{
    InitializePointersCell();
    fSize->Set(Size);
    fAngle->Set(M_PI/2,M_PI/2,M_PI/2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_cell::ECHARM_cell(double Size00, double Size01, double Size02)
{
    InitializePointersCell();
    fSize->Set(Size00,Size01,Size02);
    fAngle->Set(M_PI/2,M_PI/2,M_PI/2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_cell::~ECHARM_cell()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_cell::InitializePointersCell()
{
    fSize = new ECHARM_threevector();
    fAngle = new ECHARM_threevector();
    fSize->InitializePointersThreeVector();
    fAngle->InitializePointersThreeVector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_cell::CheckCell()
{
    if(fSize->GetComponent(0)!=0.0)
        if(fSize->GetComponent(1)!=0.0)
            if(fSize->GetComponent(2)!=0.0)
                if(fAngle->GetComponent(0) > 0.0)
                    if(fAngle->GetComponent(1) > 0.0)
                        if(fAngle->GetComponent(2) > 0.0)
                            return 1;
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_cell::IsOrthogonal()
{
    if(fAngle->GetComponent(0) == M_PI/2)
        if(fAngle->GetComponent(1) == M_PI/2)
            if(fAngle->GetComponent(2) == M_PI/2)
                return 1;
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_cell::IsCubic()
{
    if(IsOrthogonal())
        if(fSize->GetComponent(0) == fSize->GetComponent(1))
            if(fSize->GetComponent(1) == fSize->GetComponent(2))
                return 1;
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_cell::Set(std::string File_Cell)
{
    std::ifstream File_Cell_In;
    File_Cell_In.open(File_Cell.c_str());
    fSize->Set(&File_Cell_In);
    fAngle->Set(&File_Cell_In);
    File_Cell_In.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_cell::Set(ECHARM_threevector *Size, ECHARM_threevector *Angle)
{
    fSize->Set(Size);
    fAngle->Set(Angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_cell::Set(double Size00, double Size01, double Size02, double Angle00, double Angle01, double Angle02)
{
    fSize->Set(Size00,Size01,Size02);
    fAngle->Set(Angle00,Angle01,Angle02);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_cell::PrintCellProperties()
{
    std::cout << "ECHARM_cell - Print Cell Properties" << std::endl;
    std::cout << "Size      X_0 [A]   Y_0 [A]   Z_0 [A]  Volume [A^3]"<< std::endl;
    fSize->PrintThreeVector(1.E10);
    std::cout << "Angles   Alfa [°]  Beta [°] Gamma [°]" << std::endl;
    fAngle->PrintThreeVector(180/M_PI);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


const ECHARM_cell& ECHARM_cell::operator=(const ECHARM_cell& right)
{
    if (this != &right)
    {
        InitializePointersCell();
        fSize = right.fSize;
        fAngle = right.fAngle;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_cell::operator==(const ECHARM_cell& right) const
{
    return (this == (ECHARM_cell*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_cell::operator!=(const ECHARM_cell& right) const
{
    return (this != (ECHARM_cell*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::FindVolume()
{
    double double_temp = fSize->GetComponent(0)*fSize->GetComponent(1)*fSize->GetComponent(2);
    if(!IsOrthogonal())
    {
        double_temp = fSize->GetComponent(0)*fSize->GetComponent(1)*fSize->GetComponent(2)*cos(fAngle->GetComponent(0))*sin(fAngle->GetComponent(2));
    }
    return double_temp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::FindVectorSquaredReciprocal(int vIndex[3])
{
    double double_result = 0.0;
    double double_temp[6];
    int i;
    
    if(IsOrthogonal())
    {
        for(i=0;i<3;i++) double_result += pow(vIndex[i] / fSize->GetComponent(i),2);
    }
    else
    {
        double_temp[0] = fSize->GetComponent(1) * fSize->GetComponent(2) * sin(fAngle->GetComponent(1)) / FindVolume(); 
        double_temp[1] = fSize->GetComponent(0) * fSize->GetComponent(2) * sin(fAngle->GetComponent(0)) / FindVolume(); 
        double_temp[2] = fSize->GetComponent(0) * fSize->GetComponent(1) * sin(fAngle->GetComponent(2)) / FindVolume(); 
        double_temp[3] = fSize->GetComponent(0) * fSize->GetComponent(1) * pow(fSize->GetComponent(2),2) * (cos(fAngle->GetComponent(0)) * cos(fAngle->GetComponent(1)) - cos(fAngle->GetComponent(2))) / FindVolume(); 
        double_temp[4] = fSize->GetComponent(0) * pow(fSize->GetComponent(1),2) * fSize->GetComponent(2) * (cos(fAngle->GetComponent(2)) * cos(fAngle->GetComponent(0)) - cos(fAngle->GetComponent(1))) / FindVolume(); 
        double_temp[5] = pow(fSize->GetComponent(0),2) * fSize->GetComponent(1) * fSize->GetComponent(2) * (cos(fAngle->GetComponent(1)) * cos(fAngle->GetComponent(2)) - cos(fAngle->GetComponent(0))) / FindVolume(); 
        
        for(i=0;i<3;i++) double_temp[i] = pow(double_temp[i] * vIndex[i],2);
        double_temp[3] *= (2 * vIndex[0] * vIndex[1]);
        double_temp[4] *= (2 * vIndex[2] * vIndex[0]);
        double_temp[5] *= (2 * vIndex[2] * vIndex[2]);
        
        for(i=0;i<6;i++) double_result += double_temp[i];
    }
    
    double_result *= (4 * pow(M_PI,2));
    
    return double_result;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::FindVectorSquaredReciprocal(int vIndex00,int vIndex01, int vIndex02)
{
    double double_result;
    int vIndex_vector[3] = {vIndex00,vIndex01,vIndex02};
    double_result = FindVectorSquaredReciprocal(vIndex_vector);
    return double_result;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::FindVectorSquaredDirect(int vIndex[3])
{
    double double_result = 0.0;
    double double_temp[6];
    int i;
    
    if(IsOrthogonal())
    {
        for(i=0;i<3;i++) double_result += pow(vIndex[i]*fSize->GetComponent(i),2);
    }
    else
    {        
        for(i=0;i<3;i++) double_temp[i] = pow(fSize->GetComponent(i) * vIndex[i],2);
        double_temp[3] = 2 * vIndex[0] * vIndex[1] * fSize->GetComponent(1) * fSize->GetComponent(2) * cos(fAngle->GetComponent(1)) ; 
        double_temp[4] = 2 * vIndex[2] * vIndex[0] * fSize->GetComponent(0) * fSize->GetComponent(2) * cos(fAngle->GetComponent(0)) ; 
        double_temp[5] = 2 * vIndex[2] * vIndex[2] * fSize->GetComponent(0) * fSize->GetComponent(1) * cos(fAngle->GetComponent(2)) ; 
        
        for(i=0;i<6;i++) double_result += double_temp[i];
    }
    
    return double_result;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::FindVectorSquaredDirect(int vIndex00,int vIndex01, int vIndex02)
{
    double double_result;
    int vIndex_vector[3] = {vIndex00,vIndex01,vIndex02};
    double_result = FindVectorSquaredDirect(vIndex_vector);
    return double_result;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::FindPeriodDirect(int vIndex[3])
{
    double double_temp = 0.0;
    int i;
    for(i=0;i<3;i++) double_temp += pow(vIndex[i]/fSize->GetComponent(i),2);
    double_temp = pow(1/double_temp,0.5);
    return double_temp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::FindPeriodReciprocal(int vIndex[3])
{
    double double_temp = 0.0;
    int i;
    for(i=0;i<3;i++) double_temp += pow(vIndex[i]/fSize->GetComponent(i),2);
    double_temp = pow(double_temp,0.5)*2*M_PI;
    return double_temp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::FindPeriodDirect(int vIndex00,int vIndex01, int vIndex02)
{
    int vIndex[3];
    double double_temp = 0.0;
    vIndex[0]=vIndex00;
    vIndex[1]=vIndex01;
    vIndex[2]=vIndex02;
    double_temp = FindPeriodDirect(vIndex);
    return double_temp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_cell::FindPeriodReciprocal(int vIndex00,int vIndex01, int vIndex02)
{
    int vIndex[3];
    double double_temp = 0.0;
    vIndex[0]=vIndex00;
    vIndex[1]=vIndex01;
    vIndex[2]=vIndex02;
    double_temp = FindPeriodReciprocal(vIndex);
    return double_temp;
}




