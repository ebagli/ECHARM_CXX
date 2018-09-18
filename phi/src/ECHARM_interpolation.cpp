//
//  ECHARM_interpolation.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_interpolation::ECHARM_interpolation()
{
    InitializePointersInterpolation();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_interpolation::ECHARM_interpolation(unsigned int vType)
{
    InitializePointersInterpolation();
    fType = vType;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_interpolation::~ECHARM_interpolation()
{
    if (&fType)         { delete &fType; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_interpolation& ECHARM_interpolation::operator=(const ECHARM_interpolation& right)
{
    if (this != &right)
    {
        InitializePointersInterpolation();
        fType = right.fType;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_interpolation::InitializePointersInterpolation()
{
    fType = 2;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_interpolation::operator==(const ECHARM_interpolation& right) const
{
    return (this == (ECHARM_interpolation*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_interpolation::operator!=(const ECHARM_interpolation& right) const
{
    return (this != (ECHARM_interpolation*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_interpolation::FindCubicInterpolate (double &p0,double &p1, double &p2,double &p3,double &x)
{
    double a0, a1 , a2 , a3 , x2;
    
    x2 = x * x;
    a0 = p3 - p2 - p0 + p1;
    a1 = p0 - p1 - p0;
    a2 = p2 - p0;
    a3 = p1;

    return (a0 * x * x2 + a1 * x2 + a2 * x + a3);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_interpolation::FindCatmullRomInterpolate (double &p0,double &p1, double &p2,double &p3,double &x)
{
    double a0, a1 , a2 , a3 , x2;
    
    x2 = x * x;
    a0 = -0.5 * p0 + 1.5 * p1 - 1.5 * p2 + 0.5 * p3;
    a1 = p0 - 2.5 * p1 + 2.0 * p2 - 0.5 * p3;
    a2 = -0.5 * p0 + 0.5 * p2;
    a3 = p1;

    return (a0 * x * x2 + a1 * x2 + a2 * x + a3);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_interpolation::FindLinearInterpolate (double &p0,double &p1, double &x)
{
    return p0 + x * (p1-p0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_interpolation::FindBilinearInterpolate (double &p00, double &p01, double &p10, double &p11, double &x, double &y)
{
    double p0 = FindLinearInterpolate(p00,p01,x);
    double p1 = FindLinearInterpolate(p10,p11,x);
    return FindLinearInterpolate(p0,p1,y);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_interpolation::FindTrilinearInterpolate (double &p000, double &p001, double &p010, double &p011, double &p100, double &p101, double &p110, double &p111,double &x, double &y, double &z)
{
    double p0 = FindBilinearInterpolate(p000,p001,p010,p011,x,y);
    double p1 = FindBilinearInterpolate(p100,p101,p110,p111,x,y);
    return FindLinearInterpolate(p0,p1,z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_interpolation::FindInterpolate1D (double &p0,double &p1,double &p2,double &p3, double &x)
{
    switch (fType) {
        case 0:
            return FindLinearInterpolate(p1,p2,x);
            break;
        case 1:
            return FindCubicInterpolate(p0,p1,p2,p3,x);
        case 2:
            return FindCatmullRomInterpolate(p0,p1,p2,p3,x);
        default:
            return 0.0;
            break;
    } 
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_interpolation::FindInterpolate2D (double &p00, double &p01, double &p10, double &p11, double &x, double &y)
{
    if(fType==0) return FindBilinearInterpolate(p00,p01,p10,p11,x,y);
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_interpolation::FindInterpolate3D (double &p000, double &p001, double &p010, double &p011, double &p100, double &p101, double &p110, double &p111,double &x, double &y, double &z)
{
    if(fType==0) return FindTrilinearInterpolate(p000,p001,p010,p011,p100,p101,p110,p111,x,y,z);
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



