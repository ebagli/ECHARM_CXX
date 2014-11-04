//
//  ECHARM_3vec.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_3vec has to be filled with size and angle of the cell.
//   All the function inside this class are been written for any kind of cell.
//   It is possibile to evaluate the reciprocal and direct vector module 2, when their Miller vIndexes are inserted, and the direct and reciprocal period.

#ifndef _ECHARM_3vec_h
#define _ECHARM_3vec_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

class ECHARM_3vec
{
public:
    ECHARM_3vec();
    ECHARM_3vec(double Size[3]);
    ECHARM_3vec(double X, double Y, double Z);

    virtual ~ECHARM_3vec();
    
    bool IsInCube(ECHARM_3vec*);
    
    double ScalarProduct(ECHARM_3vec*);
    double ScalarProduct(double[3]);
    double GetPhi();
    double GetTheta();

    double GetAngle(ECHARM_3vec*);
    bool IsParallel(ECHARM_3vec*);
    
    ECHARM_3vec* ScaleModuleTo(double);
    ECHARM_3vec* VectorProductTo(ECHARM_3vec*);
    ECHARM_3vec* ConstantMoltiplicationTo(double);
    ECHARM_3vec* NormalizeVectorTo();
    ECHARM_3vec* AddTo(ECHARM_3vec*,double);

    void ScaleModule(double);
    void VectorProduct(ECHARM_3vec*);
    void ConstantMoltiplication(double);
    void NormalizeVector();
    void Add(ECHARM_3vec*,double);
    void AddInverse(ECHARM_3vec*,double);

    void Rotate(double,double,double);
    void Rotate(double,double);
    void Rotate(double);

    void Zero();
    virtual void Update() {;};
    
    void Print();
    void Print(double MoltiplicationFactor);
    std::string PrintAsString(double);
    
private:
    double fSize[3];
    
#include "ECHARM_3vec.hxx"
};

#endif
