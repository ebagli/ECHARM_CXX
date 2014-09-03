//
//  ECHARM_defect_screw.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_defect_screw_h
#define _ECHARM_defect_screw_h

#include "ECHARM_process.hh"
#include "ECHARM_distribution_box.hh"

class ECHARM_defect_screw: public ECHARM_defect
{
public:
    ECHARM_defect_screw(double,bool);
    virtual ~ECHARM_defect_screw();

    void CompDispl(ECHARM_3vec*,ECHARM_3vec*);
    void ComputeBR(ECHARM_3vec*,ECHARM_3vec*);
};
#endif