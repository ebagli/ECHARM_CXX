//
//  ECHARM_miller.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_miller has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_crystal class will average electric characteristic.
//   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.

#ifndef _ECHARM_miller_h
#define _ECHARM_miller_h
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#ifndef _ECHARM_threevector_h
#include "ECHARM_threevector.h"
#endif

#ifndef _ECHARM_save_structure_h
#include "ECHARM_save_structure.h"
#endif

class ECHARM_miller
{
public:
    
    //
    // Constructors;
    //
    ECHARM_miller();
    ECHARM_miller(int MillerPlanar[3],int MillerAxial[3]);
    ECHARM_miller(int MillerPl00, int MillerPl01, int MillerPl02,int MillerAx00, int MillerAx01, int MillerAx02);
    virtual ~ECHARM_miller();
    
    //
    // Retrieval methods
    //
    int GetMillerPlanar(int vIndex);
    int GetMillerAxial(int vIndex);
    int GetMillerAxial(int vIndex,int vIndex_yz);
    double GetMillerAxialModule(int vIndex);
    double GetMillerAxialModuleX() {return GetMillerAxialModule(1);};
    double GetMillerAxialModuleY() {return GetMillerAxialModule(2);};
    
    std::string GetMillerText(int vMiller[3]);
    std::string GetMillerTextPlanar() { return GetMillerText(fMillerPlanar);};
    std::string GetMillerTextAxial() { return GetMillerText(fMillerAxial[0]);};
    std::string GetMillerTextAxialX() { return GetMillerText(fMillerAxial[1]);};
    std::string GetMillerTextAxialY() { return GetMillerText(fMillerAxial[2]);};

    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_miller*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_miller&);    
    void PrintMiller();
    void PrintMillerOn(ECHARM_Miller_Save &vMillerSave);

    //
    // Set methods
    //
    void SetMillerPlanar(int MillerPlanar[3]);
    void SetMillerAxial(int MillerAxial[3]);
    void SetMillerAxialX(int MillerAxial[3]);
    void SetMillerAxialY(int MillerAxial[3]);
    void SetMillerPlanar(int MillerPl00, int MillerPl01, int MillerPl02);
    void SetMillerAxial(int MillerAx00, int MillerAx01, int MillerAx02);
    void SetMillerAxialX(int MillerAx10, int MillerAx11, int MillerAx12);
    void SetMillerAxialY(int MillerAx20, int MillerAx21, int MillerAx22);

    //
    // Calculation methods
    //
    void ReverseMillerOrderForCubicAxialCalculations(int MillerReversed[3]);
    void ReverseMillerOrderForCubicAxialCalculationsGeneral(int MillerReversed[3]);
    bool CheckCubicIndexesOrthogonalToMainAxis(int MillerOrthogonal[3]);
    bool CheckMillerIndexesOrthogonal();
    bool IsMainAxis();

public:
    
    int operator==(const ECHARM_miller&) const;
    int operator!=(const ECHARM_miller&) const;
    
    
public:
    
    ECHARM_miller(ECHARM_miller&);
    ECHARM_miller(const ECHARM_miller&);
    const ECHARM_miller & operator=(const ECHARM_miller&);
    void InitializePointersMiller();

private:
    void ComputeCubicAxialMiller();
    
    int fMillerPlanar[3];
    int fMillerAxial[3][3];
};

#endif
