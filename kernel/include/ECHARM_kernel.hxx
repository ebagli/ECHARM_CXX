//
//  ECHARM_kernel.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

public:
inline ECHARM_strip* GetStrip() {return fStrip;};
inline void SetStrip(ECHARM_strip* strip) {fStrip = strip;};

inline ECHARM_particle* GetParticle() {return fPart;};
inline void SetParticle(ECHARM_particle* particle) {fPart = particle;};

inline double GetTimeStepMin() {return fTimeTimeStepMin;};
inline void SetTimeStepMin(double step) {fTimeTimeStepMin = step;};

inline double GetStep() {return fTimeStep;};
inline void SetStep(double step) {fTimeStep = step;};

inline void AddProcess(ECHARM_process* process) {fProcesses.push_back(process);};
#ifdef ROOT_
inline bool GetSaveTrajStatus() {return bSaveTrajStatus;};
inline void SetSaveTrajStatus(bool aBool) {bSaveTrajStatus = aBool;};
#endif
