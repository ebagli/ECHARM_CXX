//
//  ECHARM_radiation.h
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

inline void SetAngColl(double num) {fAngColl = num;};
inline double GetAngColl() {return fAngColl;};

inline void SetStepMaxLength(double num) {fStepMaxLength = num;};
inline double GetStepMaxLength() {return fStepMaxLength;};

inline void SetAngXbins(double num) {fAngXbins = num;};
inline double GetAngXbins() {return fAngXbins;};

inline void SetAngYbins(double num) {fAngYbins = num;};
inline double GetAngYbins() {return fAngYbins;};

inline void SetSliceTraj(bool num) {bSliceTraj = num;};
inline bool GetSliceTraj() {return bSliceTraj;};

inline void SetInitialAngleX(double num) {fInitialAngleX = num;};
inline double GetInitialAngleX() {return fInitialAngleX;};

inline void SetInitialAngleY(double num) {fInitialAngleY = num;};
inline double GetInitialAngleY() {return fInitialAngleY;};