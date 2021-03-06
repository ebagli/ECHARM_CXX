//
//  ECHARM_kernel.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

public:
inline ECHARM_info_save* GetInfo() {return fInfo;};
inline void SetInfo(ECHARM_info_save* info) {fInfo = info;};

inline ECHARM_strip* GetStrip() {return fStrip;};
inline void SetStrip(ECHARM_strip* strip) {fStrip = strip;};

inline ECHARM_particle* GetParticle() {return fPart;};
inline void SetParticle(ECHARM_particle* particle) {fPart = particle;};

inline double GetTimeStepMin() {return fTimeStepMin;};
inline void SetTimeStepMin(double step) {fTimeStepMin = step;};

inline double GetTransverseVariationMax() {return fTransverseVariationMax;};
inline void SetTransverseVariationMax(double step) {fTransverseVariationMax = step;};

inline double GetOverrideMaxPotential() {return fOverrideMaxPotential;};
inline void SetOverrideMaxPotential(double step) {fOverrideMaxPotential = step;};

inline void EnableOverrideMaxPotential(bool abool) {bOverrideMaxPotential = abool;};

inline double GetTimeStepTotal() {return fTimeStepTotal;};

inline double GetStep() {return fTimeStep;};
inline void SetStep(double step) {fTimeStep = step;};

inline bool GetSaveTrajStatus() {return bSaveTrajStatus;};
inline void SetSaveTrajStatus(bool aBool) {bSaveTrajStatus = aBool;};

inline double GetSaveTrajStep() {return bSaveTrajStep;};

inline bool GetExitOnDechanneling() {return bExitOnDechanneling;};
inline void SetExitOnDechanneling(bool aBool) {bExitOnDechanneling = aBool;};

inline bool GetStoreDensity() {return bStoreDensity;};
inline void SetStoreDensity(bool aBool) {bStoreDensity = aBool;};

inline void AddProcess(ECHARM_process* process) {fProcesses.push_back(process);};
inline std::vector<ECHARM_process*> GetProcesses() {return fProcesses;};

inline void SavePartIn(bool aBool) {bSavePartIn = aBool;};
inline void SavePartOut(bool aBool) {bSavePartOut = aBool;};

inline void SetParticle();
inline void SetStrip();
