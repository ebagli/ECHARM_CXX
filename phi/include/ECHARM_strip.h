//
//  ECHARM_strip.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_strip
//

#ifndef _ECHARM_strip_h
#define _ECHARM_strip_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifndef _ECHARM_crystal_h
#include "ECHARM_crystal.h"
#endif

#ifndef _ECHARM_threevector_h
#include "ECHARM_threevector.h"
#endif

#ifndef _ECHARM_save_structure_h
#include "ECHARM_save_structure.h"
#endif

class ECHARM_strip
{
public:
    
    //
    // Constructor to Build directly
    //
    ECHARM_strip();
    ECHARM_strip(ECHARM_crystal* vCrystal,ECHARM_threevector* vDimension,ECHARM_threevector* vCurvature);

    virtual ~ECHARM_strip();
    
    //
    // Retrieval methods
    //
    ECHARM_crystal* GetCrystal() {return fCrystal;};
    
    ECHARM_threevector* GetDimension() {return fDimension;};
    ECHARM_threevector* GetCurvatureRadius() {return fCurvature;};

    ECHARM_threevector* GetPosition() {return fPosition;};
    ECHARM_threevector* GetDirection() {return fDirection;};

    ECHARM_threevector* GetAxisDirectionX() {return fAxisDirectionX;};
    ECHARM_threevector* GetAxisDirectionY() {return fAxisDirectionY;};

    //
    // Set methods
    //
    void SetCrystal(ECHARM_crystal *crystal) {fCrystal = crystal;};
    void SetDimension(ECHARM_threevector* Dimension) {fDimension = Dimension;};
    void SetCurvatureRadius(ECHARM_threevector* Curvature) {fCurvature = Curvature;};
 
    
    void SetAxisDirectionX(ECHARM_threevector* Direction) {fAxisDirectionX = Direction;};
    void SetAxisDirectionY(ECHARM_threevector* Direction) {fAxisDirectionY = Direction;};

    void SetPosition(ECHARM_threevector* Position) {fPosition = Position;};
    void SetDirection(ECHARM_threevector* Direction) {fDirection = Direction;};


    //
    // Printing methods
    //    
    friend std::ostream& operator<<(std::ostream&, ECHARM_strip*);
    friend std::ostream& operator<<(std::ostream&, ECHARM_strip&);
    
    std::string GetRadiusValueAsStringText();
    std::string GetLengthValueAsStringText();
    void PrintStripProperties();
    void PrintStripGeometricalProperties();
    void PrintStripOn(ECHARM_Strip_Save &vStrip);
    

    //
    // Check methods
    //
    bool CheckStrip();
    bool PointIsIn(double x,double y,double z);
    bool PointIsIn(ECHARM_threevector* vPoint);

    bool IsBentX() {return 1;};
    bool IsBentY() {return 0;};

    //
    // Calculation coefficients
    //

    
public:
    
    int operator==(const ECHARM_strip&) const;
    int operator!=(const ECHARM_strip&) const;
    
 public:
    
    ECHARM_strip(ECHARM_strip&);
    ECHARM_strip(const ECHARM_strip&);
    const ECHARM_strip & operator=(const ECHARM_strip&);
    void InitializePointersStrip();

private:
    ECHARM_threevector* fDimension;
    ECHARM_threevector* fCurvature;

    ECHARM_threevector* fAxisDirectionX; // Direction of the strip axis in the three dimensional space in which the strip exist
    ECHARM_threevector* fAxisDirectionY; // Direction of the strip axis in the three dimensional space in which the strip exist

    ECHARM_threevector* fPosition;
    ECHARM_threevector* fDirection; // Direction of the strip is the direction of the strip axis in the three dimensional space in which the strip exist
    
    ECHARM_crystal *fCrystal;
; // Direction of the strip is the direction of the strip axis in the three dimensional space in which the strip exist
};
#endif
