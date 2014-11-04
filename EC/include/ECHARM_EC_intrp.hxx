//
//  ECHARM_crystal.ihh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

public:

inline unsigned int GetNumStepsX() {return fNumSteps[0];};
inline unsigned int GetNumStepsY() {return fNumSteps[1];};
inline unsigned int GetNumStepsZ() {return fNumSteps[2];};
inline unsigned int GetNumSteps(int vIndex) {return fNumSteps[vIndex];};

inline double GetStepX() {return fStep[0];};
inline double GetStepY() {return fStep[1];};
inline double GetStepZ() {return fStep[2];};
inline double GetStep(int vIndex) {return fStep[vIndex];};

inline double ComputeStep(int vIndex) {return (fCrystal->GetPeriod(vIndex) / double(fNumSteps[vIndex] - 1));};

inline double ComputeMax() {return fVec->GetMax();};
inline double ComputeMin() {return fVec->GetMin();};

inline void PrintVecToFile(std::string filename,std::string opt = "") {fVec->PrintToFile(filename,opt);};
inline void ReadVecFromFile(std::string filename) {fVec->ReadFromFile(filename);};
