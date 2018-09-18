//
//  ECHARM_interpolation.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///

#ifndef _ECHARM_interpolation_h
#define _ECHARM_interpolation_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

class ECHARM_interpolation
{
public:
    
    //
    // Constructor to Build an element directly; no reference to isotopes
    //
    ECHARM_interpolation();
    ECHARM_interpolation(unsigned int);

    virtual ~ECHARM_interpolation();
    
    //
    // Retrieval methods
    //
    
    //
    // Set methods
    //
    void SetInterpolationType(unsigned int vType) {fType = vType;};

    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_interpolation*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_interpolation&);    
    void PrintDistributionProperties();
    
    //
    // Calculate methods
    //
    inline double FindCatmullRomInterpolate (double &p0, double &p1, double &p2, double &p3, double &x);
    inline double FindCubicInterpolate (double &p0, double &p1, double &p2, double &p3, double &x);
    inline double FindBicubicInterpolate (double &p00, double &p01, double &p02, double &p10, double &p11,double &p12, double &p20, double &p21, double &p22, double &x, double &y);
    
    inline double FindLinearInterpolate (double &p0,double &p1, double &x);
    inline double FindBilinearInterpolate (double &p00, double &p01, double &p10, double &p11, double &x, double &y);
    inline double FindTrilinearInterpolate (double &p000, double &p001, double &p010, double &p011, double &p100, double &p101, double &p110, double &p111,double &x, double &y, double &z);


    inline double FindInterpolate1D(double &p0,double &p1,double &p2,double &p3, double &x);
    double FindInterpolate2D(double &p00, double &p01, double &p10, double &p11, double &x, double &y);
    double FindInterpolate3D(double &p000, double &p001, double &p010, double &p011, double &p100, double &p101, double &p110, double &p111,double &x, double &y, double &z) ;

public:
    
    int operator==(const ECHARM_interpolation&) const;
    int operator!=(const ECHARM_interpolation&) const;
    
public:
    
    ECHARM_interpolation(ECHARM_interpolation&);
    ECHARM_interpolation(const ECHARM_interpolation&);
    const ECHARM_interpolation & operator=(const ECHARM_interpolation&);
    void InitializePointersInterpolation();//!< Initialize pointers of the atom.

private:

    unsigned int fType;
};

#endif
