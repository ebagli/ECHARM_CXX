//
//  ECHARM_crystal.ihh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
public:
inline double Get(ECHARM_3vec* vec) {return Get(vec->GetX(),vec->GetY(),vec->GetZ());};

inline ECHARM_crystal* GetCrystal() {return fCrystal;};
inline void SetCrystal(ECHARM_crystal *crystal) {fCrystal = crystal;};

inline std::string GetName() {return fName;}; //!< Get name.
inline void SetName(std::string Name) {fName=Name;}; //!< Set name.

inline double GetMax() {return fMax;};
inline void SetMax(double max) {fMax=max;};

inline double GetMin() {return fMin;};
inline void SetMin(double min) {fMin=min;};