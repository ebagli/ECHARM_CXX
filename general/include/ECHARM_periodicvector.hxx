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

inline void SetNumStepsX(double vStep) {fNumSteps[0] = vStep;};
inline void SetNumStepsY(double vStep) {fNumSteps[1] = vStep;};
inline void SetNumStepsZ(double vStep) {fNumSteps[2] = vStep;};

inline double GetStepX() {return (fPeriod[0] / double(fNumSteps[0] - 1));};
inline double GetStepY() {return (fPeriod[1] / double(fNumSteps[1] - 1));};
inline double GetStepZ() {return (fPeriod[2] / double(fNumSteps[2] - 1));};
inline double GetStep(int vIndex) {return (fPeriod[vIndex] / double(fNumSteps[vIndex] - 1));};

inline double GetPeriodX() {return fPeriod[0];};
inline double GetPeriodY() {return fPeriod[1];};
inline double GetPeriodZ() {return fPeriod[2];};
inline double GetPeriod(int vIndex) {return fPeriod[vIndex];};

inline std::string GetName() {return fName;};
inline void SetName(std::string vName) {fName = vName;};

inline std::vector<double> Get() {return fVec;};
inline double GetVal(int i,int j,int k) {return fVec.at(this->ComputeIndex(i,j,k));};
inline double GetVal(ECHARM_3vec* vec) {return GetVal(vec->GetX(),vec->GetY(),vec->GetZ());};

double GetMax(){
    if(fMax==DBL_MAX){
        return *std::max_element(fVec.begin(),fVec.end());
    }
    else{
        return fMax;
    }
};

double GetMin(){
    if(fMin==DBL_MAX){
        return *std::min_element(fVec.begin(),fVec.end());
    }
    else{
        return fMin;
    }
};