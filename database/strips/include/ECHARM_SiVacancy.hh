//
//  ECHARM_SiVacancy.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_SiVacancy
//

#ifndef _ECHARM_SiVacancy_h
#define _ECHARM_SiVacancy_h
#include "ECHARM_strip.hh"

class ECHARM_SiVacancy : public ECHARM_strip {
public:
    ECHARM_SiVacancy(double,double,double);
    virtual ~ECHARM_SiVacancy();
};
#endif
