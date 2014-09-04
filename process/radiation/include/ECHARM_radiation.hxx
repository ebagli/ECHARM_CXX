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


inline int GetEnBins() {return fEnBins;};
inline double GetEnMin() {return fEnMin;};
inline double GetEnMax() {return fEnMax;};
inline double GetEnStep() {return fEnStep;};
std::vector<double> GetRadProb() {return fRadEmProb;};

