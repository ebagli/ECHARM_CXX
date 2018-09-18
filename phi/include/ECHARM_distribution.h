//
//  ECHARM_distribution.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///

#ifndef _ECHARM_distribution_h
#define _ECHARM_distribution_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

class ECHARM_distribution
{
public:
    
    //
    // Constructor to Build an element directly; no reference to isotopes
    //
    ECHARM_distribution();
    ECHARM_distribution(unsigned int vType);

    virtual ~ECHARM_distribution();
    
    //
    // Retrieval methods
    //
    std::vector<double> GetDistributionParameters() {return fPar;};
    std::vector<std::string> GetDistributionParameterNames() {return fParNames;};
    unsigned int GetDistributionType() {return fType;};
    
    double GetValue(double vX);
    double GetValueGauss(double vX, double Mean, double HalfWidth);
    double GetValueBox(double vX, double Mean, double HalfWidth);
    
    //
    // Set methods
    //
    void SetDistributionParameters(std::vector<double> vPar) {fPar = vPar;};
    void SetDistributionParameter(unsigned int vIndex,double vParSingle) {if(vIndex<fPar.size()) fPar.at(vIndex) = vParSingle;};
    void SetDistributionType(unsigned int vType);
    void SetRandomSeed(short unsigned int vSeed) {seed48(&vSeed);};

    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_distribution*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_distribution&);    
    void PrintDistributionProperties();
    
    //
    // Calculate methods
    //
    
    double GenerateNumber();
    
    double GenerateNumberBox(double Mean, double HalfWidth);
    double GenerateNumberNegPol2(double Mean, double RMS, double xMin = 0.1, double xMax = 2.0);
    double GenerateNumberGauss(double Mean, double Sigma);//!< Box - Muller algorithm for Gaussian distrubution
    
public:
    
    int operator==(const ECHARM_distribution&) const;
    int operator!=(const ECHARM_distribution&) const;
    
public:
    
    ECHARM_distribution(ECHARM_distribution&);
    ECHARM_distribution(const ECHARM_distribution&);
    const ECHARM_distribution & operator=(const ECHARM_distribution&);
    void InitializePointersRandom();//!< Initialize pointers of the atom.
    
private:

    bool fGaussFirstOk;
    double fGaussSecondValue;
    std::vector<double> fPar;
    std::vector<std::string> fParNames;
    unsigned int fType;
};

#endif
