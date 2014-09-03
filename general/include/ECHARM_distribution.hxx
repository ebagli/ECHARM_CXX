//
//  ECHARM_distribution.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

public:
    inline std::vector<double> GetPars() {return fPar;};
    inline std::vector<std::string> GetParNames() {return fParNames;};
    
    inline void SetPars(std::vector<double> vPar) {fPar = vPar;};
    inline void SetPar(unsigned int vIndex,double vParSingle) {fPar.at(vIndex) = vParSingle;};
