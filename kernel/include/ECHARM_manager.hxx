//
//  ECHARM_manager.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

public:
inline void AddKernel(ECHARM_kernel* kernel) {fKernel.push_back(kernel);};

inline bool GetSaveTrajStatus() {return bSaveTrajStatus;};
inline void SetSaveTrajStatus(bool aBool) {bSaveTrajStatus = aBool;};
