//
//  ECHARM_defect.h
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
inline void ResetStored() {bVecStored = false;};

inline void SetPoissonRatio(double num) {fPoissonRatio = num;};
inline double GetPoissonRatio() {return fPoissonRatio;};

inline void SetProb(double num) {fProb = num;};
inline double GetProb() {return fProb;};

inline void SetBurger(ECHARM_3vec* vec) {fBurger = vec;};
inline ECHARM_3vec* GetBurger() {return fBurger;};

inline ECHARM_periodicvector* GetDisplX() {return fVecDisplX;};
inline ECHARM_periodicvector* GetDisplY() {return fVecDisplY;};
inline ECHARM_periodicvector* GetDisplZ() {return fVecDisplZ;};

inline ECHARM_periodicvector* GetBRX() {return fVecBRX;};
inline ECHARM_periodicvector* GetBRY() {return fVecBRY;};
inline ECHARM_periodicvector* GetRBZ() {return fVecBRZ;};