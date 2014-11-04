//
//  ECHARM_defect.h
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
inline void SetTorsionX(double vec) {fTorsionX = vec;};
inline double GetTorsionX() {return fTorsionX;};

inline void SetTorsionY(double vec) {fTorsionY = vec;};
inline double GetTorsionY() {return fTorsionY;};

inline void SetSigmaBeamX(double vec) {fDistrX->SetPar(1,vec);};
inline double GetSigmaBeamX() {return fDistrX->GetPar(1);};

inline void SetSigmaBeamY(double vec) {fDistrY->SetPar(1,vec);};
inline double GetSigmaBeamY() {return fDistrY->GetPar(1);};