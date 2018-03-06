//
//  ECHARM_EC.hh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_h
#define _ECHARM_EC_h

#include "ECHARM_crystal.hh"

class ECHARM_EC
{
public:
    ECHARM_EC(std::string,ECHARM_crystal*);
    ~ECHARM_EC();

#ifdef ROOT_
    virtual void PrintToTH(std::string = "");
    void PrintToTH1(std::string = "");
    void PrintToTH2(std::string = "");
#endif

    virtual void PrintToFile(std::string,std::string,std::string);
    
public:
    virtual double Get(double,double,double);

    virtual double ComputeMax() {return 0.;std::cout << "No Max Computation!!!!" << std::endl;};
    virtual double ComputeMin() {return 0.;std::cout << "No Min Computation!!!!" << std::endl;};
    
protected:
    ECHARM_crystal *fCrystal;
    std::string fName;
    
    double fMax;
    double fMin;
    
#include "ECHARM_EC.hxx"
};

#endif
