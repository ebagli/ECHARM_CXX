//
//  ECHARM_cell.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_cell has to be filled with size and angle of the cell.
//   All the function inside this class are been written for any kind of cell.
//   It is possibile to evaluate the reciprocal and direct vector module 2, when their Miller vIndexes are inserted, and the direct and reciprocal period.

#ifndef _ECHARM_cell_h
#define _ECHARM_cell_h

#include "ECHARM_constants.hh"
#include "ECHARM_3vec.hh"

class ECHARM_cell
{
public:
    ECHARM_cell(double Size00, double Size01, double Size02, double Angle00, double Angle01, double Angle02);
    ECHARM_cell(double Size00, double Size01, double Size02);
    virtual ~ECHARM_cell();
    
    void Print();
    
    bool CheckCell();
    bool IsOrthogonal();

    double ComputeVolume();
    
    double ComputeRecVec2(int vIndex[3]);
    double ComputeRecVec2(int vIndex00,int vIndex01, int vIndex02);

    double ComputeVec2(int vIndex[3]);
    double ComputeVec2(int vIndex00,int vIndex01, int vIndex02);

    double ComputePeriod(int vIndex[3]);
    double ComputePeriod(int vIndex00,int vIndex01, int vIndex02);
    
    double ComputeRecPeriod(int vIndex[3]);
    double ComputeRecPeriod(int vIndex00,int vIndex01, int vIndex02);
   
private:
    double fVolume;
    ECHARM_3vec* fSize;
    ECHARM_3vec* fAngle;
    
#include "ECHARM_cell.hxx"
};

#endif
