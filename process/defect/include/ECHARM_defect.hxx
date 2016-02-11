//
//  ECHARM_defect.h
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

inline void SetPoissonRatio(double num) {fPoissonRatio = num;};
inline double GetPoissonRatio() {return fPoissonRatio;};

inline void SetBurger(ECHARM_3vec* vec) {fBurger = vec;};
inline ECHARM_3vec* GetBurger() {return fBurger;};

inline void SetLine(ECHARM_3vec* vec) {fLine = vec;};
inline ECHARM_3vec* GetLine() {return fLine;};
