//
//  ECHARM_process.h
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

public:

inline std::string GetName() {return fName;};
inline void SetName(std::string name) {fName = name;};

inline double GetStepLengthSinceLastProcess() {return fStepLengthSinceLastProgress;};
inline void SetStepLengthSinceLastProcess(double aDouble) {fStepLengthSinceLastProgress = aDouble;};

inline void ResetStepLengthSinceLastProcess() {fStepLengthSinceLastProgress = 0.;};
inline void UpdateStepLengthSinceLastProcess(double num) {fStepLengthSinceLastProgress += num;};

inline void SetAtDSinceLastProcess(double aDouble) {fAtDSinceLastProgress = aDouble;};
inline double GetAtDSinceLastProcess() {return fAtDSinceLastProgress/fStepLengthSinceLastProgress;};
inline void ResetAtDSinceLastProcess() {fAtDSinceLastProgress = 0.;};

inline void SetElDSinceLastProcess(double aDouble) {fElDSinceLastProgress = aDouble;};
inline double GetElDSinceLastProcess() {return fElDSinceLastProgress/fStepLengthSinceLastProgress;};
inline void ResetElDSinceLastProcess() {fElDSinceLastProgress = 0.;};

inline void ResetSinceLastProcess(){
    ResetStepLengthSinceLastProcess();
    ResetAtDSinceLastProcess();
    ResetElDSinceLastProcess();
}
