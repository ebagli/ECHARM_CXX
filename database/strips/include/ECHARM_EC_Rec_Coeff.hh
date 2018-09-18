//
//  ECHARM_EC_Rec_Coeff.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_EC_Rec_Coeff
//

#ifndef _ECHARM_EC_Rec_Coeff_h
#define _ECHARM_EC_Rec_Coeff_h
#include "ECHARM_strip.hh"

class ECHARM_EC_Rec_Coeff : public ECHARM_strip {
public:
    ECHARM_EC_Rec_Coeff(ECHARM_crystal*,bool,int,int,int,int,std::string = "");
    virtual ~ECHARM_EC_Rec_Coeff();
    
private:
    std::string fType;
};
#endif
