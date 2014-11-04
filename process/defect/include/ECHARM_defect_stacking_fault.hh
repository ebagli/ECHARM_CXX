//
//  ECHARM_defect_stacking_fault.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_defect_stacking_fault_h
#define _ECHARM_defect_stacking_fault_h

#include "ECHARM_defect.hh"

class ECHARM_defect_stacking_fault: public ECHARM_defect
{
public:
    ECHARM_defect_stacking_fault(double,double);
    virtual ~ECHARM_defect_stacking_fault();

    void ComputeDispl(ECHARM_3vec*,ECHARM_3vec*);
    void ComputeBR(ECHARM_3vec*,ECHARM_3vec*);
};
#endif