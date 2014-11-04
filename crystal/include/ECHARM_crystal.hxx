//
//  ECHARM_crystal.ihh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
public:
inline ECHARM_atom* GetAtom(unsigned int vIndex) {return fAtom.at(vIndex);};
inline ECHARM_lattice* GetLattice(unsigned int vIndex) {return fLattice.at(vIndex);};
inline float GetPercentage(unsigned int vIndex) {return fPercentage.at(vIndex);};
inline ECHARM_miller* GetMiller() {return fMiller;};
inline ECHARM_cell* GetCell() {return fCell;};

inline double GetRadLength() {return fRadLength;};
inline void SetRadLength(double rad_length) {fRadLength = rad_length;};

inline unsigned int GetNumBases() {return fAtom.size();};

inline unsigned int GetNumCoord() {return fNumCoord;};

inline double GetPeriodX() {return fPeriod[0];};
inline double GetPeriodY() {return fPeriod[1];};
inline double GetPeriodZ() {return fPeriod[2];};
inline double GetPeriod(int vIndex) {return fPeriod[vIndex];};

inline double GetRecPeriodX() {return fRecPeriod[0];};
inline double GetRecPeriodY() {return fRecPeriod[1];};
inline double GetRecPeriodZ() {return fRecPeriod[2];};
inline double GetRecPeriod(int vIndex) {return fRecPeriod[vIndex];};

inline double GetNucleiDensity() {return (fNumCoord/fCell->ComputeVolume());};
inline double GetNuclearDensity() {return (this->GetZ() * fNumCoord/fCell->ComputeVolume());};
inline double GetMassDensity() {return (this->GetA() * fNumCoord/fCell->ComputeVolume());};