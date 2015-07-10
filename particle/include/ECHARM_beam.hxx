//
//  ECHARM_beam.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//  Class ECHARM_beam

public:
inline std::vector<ECHARM_particle*> GetParticles() {return fParticles;}
inline std::vector<double> GetPercentages() {return fPercentages;}

inline ECHARM_distribution* GetDistrMomX() {return fDistrMomentumX;}
inline void SetDistrMomX(ECHARM_distribution* Momentum) {fDistrMomentumX=Momentum;}

inline ECHARM_distribution* GetDistrMomY() {return fDistrMomentumY;}
inline void SetDistrMomY(ECHARM_distribution* Momentum) {fDistrMomentumY=Momentum;}

inline ECHARM_distribution* GetDistrMomZ() {return fDistrMomentumZ;}
inline void SetDistrMomZ(ECHARM_distribution* Momentum) {fDistrMomentumZ=Momentum;}

inline ECHARM_distribution* GetDistrPosX() {return fDistrPositionX;}
inline void SetDistrPosX(ECHARM_distribution* Position) {fDistrPositionX=Position;}

inline ECHARM_distribution* GetDistrPosY() {return fDistrPositionY;}
inline void SetDistrPosY(ECHARM_distribution* Position) {fDistrPositionY=Position;}

inline ECHARM_distribution* GetDistrPosZ() {return fDistrPositionZ;}
inline void SetDistrPosZ(ECHARM_distribution* Position) {fDistrPositionZ=Position;}

inline ECHARM_particle* GetGeneratedParticle() {return fParticle;}

inline ECHARM_distribution* GetDistrBeamSizeX() {return fDistrBeamSizeX;}
inline void GetDistrBeamSizeX(ECHARM_distribution* Position) {fDistrBeamSizeX=Position;}

inline ECHARM_distribution* GetDistrBeamSizeY() {return fDistrBeamSizeY;}
inline void GetDistrBeamSizeY(ECHARM_distribution* Position) {fDistrBeamSizeY=Position;}

inline ECHARM_distribution* GetDistrBeamSizeZ() {return fDistrBeamSizeZ;}
inline void GetDistrBeamSizeZ(ECHARM_distribution* Position) {fDistrBeamSizeZ=Position;}
