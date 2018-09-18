//
//  ECHARM_EC_rec.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_EC_rec_h
#define _ECHARM_EC_rec_h
//#define USE_FFWT3

#include "ECHARM_EC.hh"
#include <iostream>
#include <complex>

#ifdef USE_FFWT3
#include <fftw3.h>
#endif

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
    void StoreValues();

#ifdef ROOT_
    void PrintSFtoTH(std::vector<double>,std::string);
    void PrintSFtoTH1(std::vector<double>,std::string);
    void PrintSFtoTH2(std::vector<double>,std::string);
#endif

    virtual std::vector<double> ComputeRecFF(int[3],double[3]) = 0;

    int GetIndex(int,int,int);
    int GetIndexRe(int,int,int);
    int GetIndexIm(int,int,int);

    virtual bool GetIndexesSF(int*,int,int,int) = 0;
    virtual bool GetIndexesEC(double*,int*,int,int,int) = 0;

    virtual double GetFactorRe(double*) = 0;
    virtual double GetFactorIm(double*) = 0;

    inline void PrintVecToFile(std::string filename,std::string opt = "") {fVec->PrintToFile(filename,opt);};
    inline void PrintCoeffToFile(std::string filename,bool invertReIm,std::string);

protected:
    int fFTN[3]; //Fourier Term Number

    double fPhaseCos;
    double fPhaseSin;
    
    std::vector<double> fFFC;
    ECHARM_periodicvector* fVec;
    
#include "ECHARM_EC_rec.hxx"
};

#endif
