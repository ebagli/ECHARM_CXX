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

public:
double GetModule2() {return ScalarProduct(this);};
double GetModule() {return fSquareRoot(GetModule2());};

inline double Get(unsigned int vIndex) {return fSize[vIndex];};
inline double GetX() const {return fSize[0];};
inline double GetY() const {return fSize[1];};
inline double GetZ() const {return fSize[2];};

double GetNormalized(unsigned int vIndex) {return fSize[vIndex]/GetModule();};
double GetXNormalized() {return fSize[0]/GetModule();};
double GetYNormalized() {return fSize[1]/GetModule();};
double GetZNormalized() {return fSize[2]/GetModule();};

inline void Set(ECHARM_3vec* vec) {fSize[0] = vec->GetX();fSize[1] = vec->GetY();fSize[2] = vec->GetZ();};
inline void Set(int size[3]) {fSize[0] = size[0];fSize[1] = size[1];fSize[2] = size[2];};
inline void Set(double size[3]) {fSize[0] = size[0];fSize[1] = size[1];fSize[2] = size[2];};
inline void Set(int vIndex, double vSize) {fSize[vIndex] = vSize;};
inline void Set(double X,double Y,double Z) {fSize[0] = X;fSize[1] = Y;fSize[2] = Z;}
inline void SetX(double X) {fSize[0] = X;};
inline void SetY(double Y) {fSize[1] = Y;};
inline void SetZ(double Z) {fSize[2] = Z;};

inline void Add(int vIndex, double X) {fSize[vIndex] += X;};
inline void AddX(double X) {fSize[0] += X;};
inline void AddY(double Y) {fSize[1] += Y;};
inline void AddZ(double Z) {fSize[2] += Z;};

inline void Subtract(int vIndex, double X) {fSize[vIndex] -= X;};
inline void SubtractX(double X) {fSize[0] -= X;};
inline void SubtractY(double Y) {fSize[1] -= Y;};
inline void SubtractZ(double Z) {fSize[2] -= Z;};
