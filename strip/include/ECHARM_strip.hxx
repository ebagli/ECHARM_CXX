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
inline ECHARM_crystal* GetCrystal() {return fCrystal;};
inline void SetCrystal(ECHARM_crystal *crystal) {fCrystal = crystal;};

inline ECHARM_3vec* GetDim() {return fDim;};
inline ECHARM_3vec* GetPos() {return fPos;};
inline ECHARM_3vec* GetBR() {return fBR;};
inline ECHARM_3vec* GetBRconst() {return fBRconst;};
inline void ResetBR() {fBR->Set(fBRconst);}
inline ECHARM_3vec* GetAnglesLattice() {return fAL;};

inline bool IsBentX() {return IsBent(0);};
inline bool IsBentY() {return IsBent(1);};
inline bool IsBentZ() {return IsBent(2);};

inline ECHARM_EC* GetPot() {return fPot;};
inline ECHARM_EC* GetElD() {return fAtD;};
inline ECHARM_EC* GetAtD() {return fElD;};
inline ECHARM_EC* GetEFX() {return fEFX;};
inline ECHARM_EC* GetEFY() {return fEFY;};
inline ECHARM_EC* GetEFZ() {return fEFZ;};

inline void SetPot(ECHARM_EC* ec) {fPot = ec;};
inline void SetAtD(ECHARM_EC* ec) {fAtD = ec;};
inline void SetElD(ECHARM_EC* ec) {fElD = ec;};
inline void SetEFX(ECHARM_EC* ec) {fEFX = ec;};
inline void SetEFY(ECHARM_EC* ec) {fEFY = ec;};
inline void SetEFZ(ECHARM_EC* ec) {fEFZ = ec;};
