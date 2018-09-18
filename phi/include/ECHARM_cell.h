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
//   It is possibile to evaluate the reciprocal and direct vector module squared, when their Miller vIndexes are inserted, and the direct and reciprocal period.

#ifndef _ECHARM_cell_h
#define _ECHARM_cell_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

#ifndef _ECHARM_constants_h
#include "ECHARM_constants.h"
#endif

#ifndef _ECHARM_threevector_h
#include "ECHARM_threevector.h"
#endif

class ECHARM_cell
{
public:
    
    //
    // Constructors
    //
    ECHARM_cell();
    ECHARM_cell(ECHARM_threevector *Size, ECHARM_threevector *Angle);
    ECHARM_cell(double Size00, double Size01, double Size02, double Angle00, double Angle01, double Angle02);
    ECHARM_cell(ECHARM_threevector *Size);
    ECHARM_cell(double Size00, double Size01, double Size02);
    virtual ~ECHARM_cell();
    
    //
    // Retrieval methods
    //
    ECHARM_threevector* GetSize() {return fSize;};
    ECHARM_threevector* GetAngle() {return fAngle;};
   
    //
    // Set methods
    //
    void Set(double Size00, double Size01, double Size02, double Angle00, double Angle01, double Angle02);
    void Set(ECHARM_threevector *Size, ECHARM_threevector *Angle);
    void Set(std::string File_Cell);
        
    //
    // Printing methods
    //    
    friend std::ostream& operator<<(std::ostream&, ECHARM_cell*);
    friend std::ostream& operator<<(std::ostream&, ECHARM_cell&);
    
    void PrintCellProperties();
    
    //
    // Check methods
    //    
    bool CheckCell();
    bool IsOrthogonal();
    bool IsCubic();

    //
    // Calculation methods
    //
    double FindVolume();
    
    double FindVectorSquaredReciprocal(int vIndex[3]);
    double FindVectorSquaredReciprocal(int vIndex00,int vIndex01, int vIndex02);

    double FindVectorSquaredDirect(int vIndex[3]);
    double FindVectorSquaredDirect(int vIndex00,int vIndex01, int vIndex02);

    double FindPeriodDirect(int vIndex[3]);
    double FindPeriodDirect(int vIndex00,int vIndex01, int vIndex02);
    
    double FindPeriodReciprocal(int vIndex[3]);
    double FindPeriodReciprocal(int vIndex00,int vIndex01, int vIndex02);
   
    
public:
    
    int operator==(const ECHARM_cell&) const;
    int operator!=(const ECHARM_cell&) const;
    
public:
    void InitializePointersCell();

    ECHARM_cell(ECHARM_cell&);
    ECHARM_cell(const ECHARM_cell&);
    const ECHARM_cell & operator=(const ECHARM_cell&);

private:
    ECHARM_threevector* fSize;
    ECHARM_threevector* fAngle;
};

#endif
