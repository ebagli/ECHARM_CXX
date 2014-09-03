//
//  ECHARM_intrp.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_intrp_h
#define _ECHARM_intrp_h

class ECHARM_intrp{
public:

    ECHARM_intrp();
    virtual ~ECHARM_intrp();
    
    virtual double Get1d(double &x, double &p0,double &p1, double &p2,double &p3);
    virtual double Get2d(double &x,double &y, double &p00,double &p01, double &p02,double &p03,double &p10,double &p11, double &p12,double &p13,double &p20,double &p21, double &p22,double &p23,double &p30,double &p31, double &p32,double &p33);

    double GetXinUnitPeriod(double,double&);
    double GetXinUnitOne(double,double&);
    void GetIndexes(int*,int&);
};

#endif
