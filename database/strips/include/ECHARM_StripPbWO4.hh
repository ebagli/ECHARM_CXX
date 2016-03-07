//
//  ECHARM_StripPbWO4.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_StripPbWO4
//

#ifndef _ECHARM_StripPbWO4_h
#define _ECHARM_StripPbWO4_h
#include "ECHARM_strip.hh"

class ECHARM_StripPbWO4 : public ECHARM_strip {
public:
    ECHARM_StripPbWO4(int,int,int);
    virtual ~ECHARM_StripPbWO4();
};
#endif
