//
//  ECHARM_EC_rec.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_h
#define _ECHARM_EC_rec_h

#include "ECHARM_EC.hh"

class ECHARM_EC_rec: public ECHARM_EC
{
public:
    ECHARM_EC_rec(std::string,ECHARM_crystal*,int,int,int);
    ~ECHARM_EC_rec();
       
    virtual double Get(double, double, double) = 0; //!< Calculation method described in PRE 81, 026708 (2010)

    double GetFT(double,double,double,std::vector<double>&); //!< Calculation method described in PRE 81, 026708 (2010)
#ifdef CUDA_
    double GetFT1D_CUDA(double,,std::vector<double>&); //!< Calculation method described in PRE 81, 026708 (2010)
#endif
    
    void StoreRecFF();

#ifdef ROOT_
    void PrintSFtoTH(std::vector<double>,std::string);
    void PrintSFtoTH1(std::vector<double>,std::string);
    void PrintSFtoTH2(std::vector<double>,std::string);
#endif

    virtual std::vector<double> ComputeRecFF(int[3]) = 0;

    int GetIndexRe(int,int,int);
    int GetIndexIm(int,int,int);

    virtual bool GetIndexesSF(int*,int,int,int) = 0;
    virtual bool GetIndexesEC(double*,int*,int,int,int) = 0;

    virtual double GetFactorRe(double*) = 0;
    virtual double GetFactorIm(double*) = 0;

protected:
    int fFTN[3]; //Fourier Term Number

    double fPhaseCos;
    double fPhaseSin;
    
    std::vector<double> fFFC;
    
#include "ECHARM_EC_rec.hxx"
};

#endif
