//
//  ECHARM_QM_CERN_H4_1mm.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_QM_CERN_H4_1mm
//

#ifndef _ECHARM_QM_CERN_H4_1mm_h
#define _ECHARM_QM_CERN_H4_1mm_h
#include "ECHARM_strip.hh"

class ECHARM_QM_CERN_H4_1mm : public ECHARM_strip {
public:
    ECHARM_QM_CERN_H4_1mm(double,double,std::string);
    virtual ~ECHARM_QM_CERN_H4_1mm();
};
#endif
