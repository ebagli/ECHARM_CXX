//
//  ECHARM_defect.h
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
inline void ResetStored() {bVecStored = false;};

inline void UseTabulatedVal(bool use) {bTabVal = use;};

inline void SetRandomAngle(bool on) {bRandomAngle = on;};
inline void SetRandomPosition(bool on) {bRandomPosition = on;};
inline void SetHalfLimits(ECHARM_3vec *limit) {fLimitsHalf = limit;};

inline void SetProb(double num) {fProb = num;};
inline double GetProb() {return fProb;};

inline ECHARM_periodicvector* GetDisplX() {return fVecDisplX;};
inline ECHARM_periodicvector* GetDisplY() {return fVecDisplY;};
inline ECHARM_periodicvector* GetDisplZ() {return fVecDisplZ;};

inline ECHARM_periodicvector* GetBRX() {return fVecBRX;};
inline ECHARM_periodicvector* GetBRY() {return fVecBRY;};
inline ECHARM_periodicvector* GetRBZ() {return fVecBRZ;};

std::vector<double> GetAngPhi() {return fAngPhi;};
std::vector<double> GetAngTheta() {return fAngTheta;};
std::vector<double> GetAngPsi() {return fAngPsi;};

void SetBoxYzero(bool val) {bBoxYzero = val;};
bool GetBoxYzero() {return bBoxYzero;};