//
//  ECHARM_strip.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//


ECHARM_strip::ECHARM_strip()
{
    InitializePointersStrip();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_strip::ECHARM_strip(ECHARM_crystal* vCrystal,ECHARM_threevector* vDimension,ECHARM_threevector* vCurvature)
{
    InitializePointersStrip();
    SetCrystal(vCrystal);
    SetDimension(vDimension);
    SetCurvatureRadius(vCurvature);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_strip::~ECHARM_strip()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_strip::InitializePointersStrip()
{
    fCrystal = new ECHARM_crystal();
    
    fDimension = new ECHARM_threevector();
    fCurvature = new ECHARM_threevector();

    fPosition = new ECHARM_threevector();
    fDirection = new ECHARM_threevector(0.0,0.0,1.0);
    fAxisDirectionX = new ECHARM_threevector(1.0,0.0,0.0);
    fAxisDirectionY = new ECHARM_threevector(0.0,1.0,0.0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_strip::CheckStrip()
{
    if(fDimension->GetComponent(0)!=0.0)
        if(fDimension->GetComponent(1)!=0.0)
            if(fDimension->GetComponent(2)!=0.0)
                if(fCrystal->CheckCrystal())
                    return 1;
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_strip::PointIsIn(ECHARM_threevector* vPoint)
{
    if(fabs(vPoint->GetComponent(0) - fPosition->GetComponent(0)) <= ( fDimension->GetComponent(0) * 0.5) )
        if(fabs(vPoint->GetComponent(1) - fPosition->GetComponent(1)) <= ( fDimension->GetComponent(1) * 0.5) )
            if(fabs(vPoint->GetComponent(2) - fPosition->GetComponent(2)) <= ( fDimension->GetComponent(2) * 0.5) )
                return 1;
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_strip::PointIsIn(double x,double y,double z)
{
    ECHARM_threevector* vPoint = new ECHARM_threevector(x,y,z);
    return PointIsIn(vPoint);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_strip::PrintStripProperties()
{
    std::cout << "ECHARM_strip - Strip Properties" << std::endl;
    PrintStripGeometricalProperties();
    fCrystal->PrintPropertiesCrystal();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_strip::PrintStripGeometricalProperties()
{
    std::cout << "ECHARM_strip - Geometrical Properties" << std::endl;
    std::cout << "Size      X  [mm]   Y  [mm]   Z  [mm] "<< std::endl;
    fDimension->PrintThreeVector(1.0/millimeter);
    std::cout << "Curv. Rad.R_X [m]   R_Y [m]   R_Z  [m]" << std::endl;
    fCurvature->PrintThreeVector();
    std::cout << "Position  P_X [m]   P_Y [m]   P_Z  [m]" << std::endl;
    fPosition->PrintThreeVector();
    std::cout << "Direction X         Y         Z       " << std::endl;
    fDirection->PrintThreeVector();
    std::cout << "X-Ax. Dir.X         Y         Z       " << std::endl;
    fAxisDirectionX->PrintThreeVector();
    std::cout << "Y-Ax. Dir.X         Y         Z       " << std::endl;
    fAxisDirectionY->PrintThreeVector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_strip::PrintStripOn(ECHARM_Strip_Save &vStrip)
{
    vStrip.Rx = GetCurvatureRadius()->GetX();
    vStrip.Ry = GetCurvatureRadius()->GetY();
    vStrip.Rz = GetCurvatureRadius()->GetZ();
    vStrip.Lx = GetDimension()->GetX();
    vStrip.Ly = GetDimension()->GetY();
    vStrip.Lz = GetDimension()->GetZ();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::string ECHARM_strip::GetRadiusValueAsStringText()
{
    std::stringstream vSS;
    vSS << round(GetCurvatureRadius()->GetX()/centimeter) << "_" << round(GetCurvatureRadius()->GetY()/centimeter);
    return vSS.str();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::string ECHARM_strip::GetLengthValueAsStringText()
{
    std::stringstream vSS;
    vSS << round(GetDimension()->GetZ()/micrometer);
    return vSS.str();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_strip::operator==(const ECHARM_strip& right) const
{
    return (this == (ECHARM_strip*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_strip::operator!=(const ECHARM_strip& right) const
{
    return (this != (ECHARM_strip*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_strip& ECHARM_strip::operator=(const ECHARM_strip& right)
{
    if (this != &right)
    {
        InitializePointersStrip();
        fDimension = right.fDimension;
        fCurvature = right.fCurvature;
 
        fPosition = right.fPosition;
        fDirection = right.fDirection;
        fAxisDirectionY = right.fAxisDirectionY;
        fAxisDirectionX = right.fAxisDirectionX;
        
        fCrystal = right.fCrystal;
    
    }
    return *this;
}

