//
//  ECHARM_defect.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
    void ResetStored() {bVecStored = false;};

    void SetPoissonRatio(double num) {fPoissonRatio = num;};
    int GetPoissonRatio() {return fPoissonRatio;};

    void SetBurger(ECHARM_3vec* vec) {fBurger = vec;};
    ECHARM_3vec* GetBurger() {return fBurger;};