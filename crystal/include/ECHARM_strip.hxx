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

public:
inline ECHARM_3vec* GetDim() {return fDim;};
inline ECHARM_3vec* GetPos() {return fPos;};
inline ECHARM_3vec* GetBR() {return fBR;};
inline ECHARM_3vec* GetBRconst() {return fBRconst;};
inline void ResetBR() {fBR->Set(fBRconst);}
inline ECHARM_3vec* GetAnglesLattice() {return fAL;};

inline bool IsBentX() {return IsBent(0);};
inline bool IsBentY() {return IsBent(1);};
inline bool IsBentZ() {return IsBent(2);};

inline void SetPot(ECHARM_EC* ec) {fPot = ec;};
inline void SetAtD(ECHARM_EC* ec) {fAtD = ec;};
inline void SetElD(ECHARM_EC* ec) {fElD = ec;};
inline void SetEFX(ECHARM_EC* ec) {fEFX = ec;};
inline void SetEFY(ECHARM_EC* ec) {fEFY = ec;};
inline void SetEFZ(ECHARM_EC* ec) {fEFZ = ec;};

inline std::string GetName() {return fName;};
inline void SetName(std::string name) {fName = name;};

virtual inline ECHARM_crystal* GetCrystal() {return fCrystal;};
inline void SetCrystal(ECHARM_crystal *crystal) {fCrystal = crystal;};

virtual inline ECHARM_EC* GetPot() {return fPot;};
virtual inline ECHARM_EC* GetElD() {return fAtD;};
virtual inline ECHARM_EC* GetAtD() {return fElD;};
virtual inline ECHARM_EC* GetEFX() {return fEFX;};
virtual inline ECHARM_EC* GetEFY() {return fEFY;};
virtual inline ECHARM_EC* GetEFZ() {return fEFZ;};
