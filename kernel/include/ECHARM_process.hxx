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
inline void ResetStepLengthSinceLastProcess() {fStepLengthSinceLastProgress = 0.;};
inline void UpdateStepLengthSinceLastProcess(double num) {fStepLengthSinceLastProgress += num;};

inline double GetAtDSinceLastProcess() {return fAtDSinceLastProgress/fStepLengthSinceLastProgress;};
inline void ResetAtDSinceLastProcess() {fAtDSinceLastProgress = 0.;};

inline double GetElDSinceLastProcess() {return fElDSinceLastProgress/fStepLengthSinceLastProgress;};
inline void ResetElDSinceLastProcess() {fElDSinceLastProgress = 0.;};

inline void UpdateAtDSinceLastProcess(double num) {fAtDSinceLastProgress += num;};
inline void UpdateElDSinceLastProcess(double num) {fElDSinceLastProgress += num;};

inline void ResetSinceLastProcess(){
    ResetStepLengthSinceLastProcess();
    ResetAtDSinceLastProcess();
    ResetElDSinceLastProcess();
}