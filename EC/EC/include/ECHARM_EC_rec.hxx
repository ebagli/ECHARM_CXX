//
//  ECHARM_crystal_rec.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
public:
    inline int GetFourierTermNumberX() {return fFTN[0];};
    inline void SetFourierTermNumberX(int term) {fFTN[0] = term;};
    inline int GetFourierTermNumberY() {return fFTN[1];};
    inline void SetFourierTermNumberY(int term) {fFTN[1] = term;};
    inline int GetFourierTermNumberZ() {return fFTN[2];};
    inline void SetFourierTermNumberZ(int term) {fFTN[2] = term;};

void SetRecFFCoeff(std::vector<double> vec) {fFFC = vec;};
