//
//  ECHARM_defect_edge.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_defect_edge_h
#define _ECHARM_defect_edge_h

#include "ECHARM_defect.hh"

class ECHARM_defect_edge: public ECHARM_defect
{
public:
    ECHARM_defect_edge(double,double,bool);
    virtual ~ECHARM_defect_edge();
    double GetBurgerEdge() {return fBurger->GetModule();};
    double GetBurgerScrew() {return 0.;};	
};
#endif
