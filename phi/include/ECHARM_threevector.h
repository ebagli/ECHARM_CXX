//
//  ECHARM_threevector.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_threevector has to be filled with size and angle of the cell.
//   All the function inside this class are been written for any kind of cell.
//   It is possibile to evaluate the reciprocal and direct vector module squared, when their Miller vIndexes are inserted, and the direct and reciprocal period.

#ifndef _ECHARM_threevector_h
#define _ECHARM_threevector_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

class ECHARM_threevector
{
public:
    
    //
    // Constructors
    //
    ECHARM_threevector();
    ECHARM_threevector(double Size[3]);
    ECHARM_threevector(double X, double Y, double Z);

    virtual ~ECHARM_threevector();
    
    //
    // Retrieval methods
    //
    double GetComponent(unsigned int vIndex) {if(vIndex<3) return fSize[vIndex]; return 0.0;};
    double GetComponentNormalized(unsigned int vIndex) {if(vIndex<3) return fSize[vIndex]/GetModule(); return 0.0;};
    inline double GetModule() {return sqrt(GetModuleSquared());};
    inline double GetModuleSquared() {return ScalarProduct(this);};
    inline double GetX() const {return fSize[0];};
    inline double GetY() const {return fSize[1];};
    inline double GetZ() const {return fSize[2];};
    double GetXNormalized() {return fSize[0]/GetModule();};
    double GetYNormalized() {return fSize[1]/GetModule();};
    double GetZNormalized() {return fSize[2]/GetModule();};

    void CopyOn(double vVector[3]) {for(int i=0;i<3;i++) vVector[i] = fSize[i];};
    void CopyOn(ECHARM_threevector *vVector) {for(int i=0;i<3;i++) vVector->Set(i,GetComponent(i));};
    void CopyOn(std::vector<double> vVector) {vVector.clear(); AppendOn(vVector);};
    void AppendOn(std::vector<double> vVector) {for(int i=0;i<3;i++) vVector.push_back(fSize[i]);};

    //
    // Set methods
    //
    void Set(double X, double Y, double Z);
    void Set(double Size[3]);
    void Set(ECHARM_threevector *vector) {for(int i=0;i<3;i++) fSize[i]=vector->GetComponent(i);};
    void Set(std::ifstream* File_In);
    void Set(int vIndex,double Size) {if(vIndex<3) fSize[vIndex]= Size;};
    inline void SetX(double X) {fSize[0] = X;};
    inline void SetY(double Y) {fSize[1] = Y;};
    inline void SetZ(double Z) {fSize[2] = Z;};
    void CopyFrom(ECHARM_threevector *vector) {for(int i=0;i<3;i++) fSize[i]=vector->GetComponent(i);};
    void ScaleModuleTo(double vModule);
    
    //
    // Add methods
    //
    inline void AddX(double X) {fSize[0] += X;};
    inline void AddY(double Y) {fSize[1] += Y;};
    inline void AddZ(double Z) {fSize[2] += Z;};

    //
    // Subtract methods
    //
    inline void SubtractX(double X) {fSize[0] -= X;};
    inline void SubtractY(double Y) {fSize[1] -= Y;};
    inline void SubtractZ(double Z) {fSize[2] -= Z;};

    //
    // Calculation methods
    //
    
    double ScalarProduct(ECHARM_threevector *vVector);
    ECHARM_threevector* VectorProduct(ECHARM_threevector *vVector);
    ECHARM_threevector* ConstantMoltiplication(double MoltiplicationFactor);
    ECHARM_threevector* NormalizeVector();
    
    //
    // Printing methods
    //    
    friend std::ostream& operator<<(std::ostream&, ECHARM_threevector*);
    friend std::ostream& operator<<(std::ostream&, ECHARM_threevector&);
    
    void PrintThreeVector();
    void PrintThreeVector(double MoltiplicationFactor);
    
    
public:
    
    int operator==(const ECHARM_threevector&) const;
    int operator!=(const ECHARM_threevector&) const;

public:
    
    ECHARM_threevector(ECHARM_threevector&);
    ECHARM_threevector(const ECHARM_threevector&);
    const ECHARM_threevector & operator=(const ECHARM_threevector&);
    void InitializePointersThreeVector();
    
private:
    double fSize[3];
};

#endif
