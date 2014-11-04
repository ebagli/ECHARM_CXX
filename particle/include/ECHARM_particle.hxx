//
//  ECHARM_particle.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_particle

public:
    
inline double GetZ() {return fZ;}
inline void SetZ(double Z) {fZ=Z;}

inline double GetMass() {return fMass;}
inline void SetMass(double Mass) {fMass=Mass;}

inline ECHARM_3vec* GetMom() {return fMom;}
inline ECHARM_3vec* GetPos() {return fPos;}

inline ECHARM_3vec* GetMomPre() {return fMomPre;}
inline ECHARM_3vec* GetPosPre() {return fPosPre;}

inline void SaveMom() {fMomPre->Set(fMom);}
inline void SavePos() {fPosPre->Set(fPos);}

inline double GetAngX() {return fMom->GetX()/fMom->GetZ();}
inline double GetAngY() {return fMom->GetY()/fMom->GetZ();}

inline double GetAngXPre() {return fMomPre->GetX()/fMomPre->GetZ();}
inline double GetAngYPre() {return fMomPre->GetY()/fMomPre->GetZ();}

inline double GetStepLengthSinceLastProcess() {return fStepLengthSinceLastProgress;};
inline void ResetStepLengthSinceLastProcess() {fStepLengthSinceLastProgress = 0.;};
inline void UpdateStepLengthSinceLastProcess() {fStepLengthSinceLastProgress += GetStepLength();};

inline double GetAtDSinceLastProcess() {return fAtDSinceLastProgress/fStepLengthSinceLastProgress;};
inline void ResetAtDSinceLastProcess() {fAtDSinceLastProgress = 0.;};
inline void UpdateAtDSinceLastProcess(double num) {fAtDSinceLastProgress += num;};

inline double GetElDSinceLastProcess() {return fElDSinceLastProgress/fStepLengthSinceLastProgress;};
inline void ResetElDSinceLastProcess() {fElDSinceLastProgress = 0.;};
inline void UpdateElDSinceLastProcess(double num) {fElDSinceLastProgress += num;};