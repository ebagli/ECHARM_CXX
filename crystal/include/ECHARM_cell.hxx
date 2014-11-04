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

public:
    inline ECHARM_3vec* GetSizes() {return fSize;};
    inline ECHARM_3vec* GetAngles() {return fAngle;};
    inline double GetVolume() {return fVolume;};

    virtual void SetSizes(double Size00, double Size01, double Size02) {fSize->Set(Size00,Size01,Size02);};
    virtual void SetAngles(double Angle00, double Angle01, double Angle02) {fAngle->Set(Angle00,Angle01,Angle02);};
